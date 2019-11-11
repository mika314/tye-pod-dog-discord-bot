#include "guild.hpp"
#include "gen_uuid.hpp"
#include "player.hpp"
#include <sstream>

using json = nlohmann::json;
using namespace std::literals::chrono_literals;

namespace
{
  bool replace(std::string &str, const std::string &from, const std::string &to)
  {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
      return false;
    str.replace(start_pos, from.length(), to);
    return true;
  }

  std::string getPlayerId(const json &msg)
  {
    return "player/" + msg["guild_id"].get<std::string>() + "/" +
           msg["author"]["id"].get<std::string>();
  }

  std::string getWorldId(const json &msg) { return "world/" + msg["id"].get<std::string>(); }

  void checkError(RedisCon *redisCon, redisReply *reply)
  {
    if (!reply)
    {
      std::cerr << "Error: " << redisCon->con->errstr << std::endl;
      exit(1);
    }
    if (reply->type == REDIS_REPLY_ERROR)
      std::cerr << "Error: " << std::string{reply->str, reply->str + reply->len} << std::endl;
  }
} // namespace

Guild::Guild(const json &msg, RedisCon &redisCon)
  : systemChannelId(msg["system_channel_id"].get<std::string>()),
    lastChannelId(systemChannelId),
    rulesChannelId(systemChannelId),
    redisCon(&redisCon),
    world(redisCon, getWorldId(msg))
{
  for (const auto &ch : msg["channels"])
  {
    auto name = ch["name"].get<std::string>();
    std::transform(std::begin(name), std::end(name), std::begin(name), ::tolower);
    if (name.find("rules") != std::string::npos)
    {
      rulesChannelId = ch["id"].get<std::string>();
      break;
    }
  }
}

void Guild::onMessageCreate(Bot &bot, const json &msg)
{
  lastChannelId = msg["channel_id"].get<std::string>();
  Player player(*redisCon, getPlayerId(msg));
  if (msg["content"].get<std::string>() == "quit")
  {
    bot.message(lastChannelId, "It was fun to play with you");
    player.setState(Player::State::Null);
    return;
  }
  switch (player.getState())
  {
  default:
  case Player::State::Null: break;
  case Player::State::HeroName:
  {
    auto name = msg["content"].get<std::string>();
    bot.message(lastChannelId, "Your name is " + name);
    bot.message(lastChannelId, "Type \"help\" if you need to learn how to play.");
    player.getActiveHero().setName(name);
    player.setState(Player::State::Playing);
    return;
  }
  case Player::State::Playing:
  {
    auto hero = player.getActiveHero();
    Pos pos{hero.getX(), hero.getY(), hero.getZ()};
    auto room = world.getRoom(pos);
    auto cmd = msg["content"].get<std::string>();
    if (cmd == "help")
    {
      bot.message(lastChannelId,
                  "describe or desc - describe place where hero is standing\n"
                  "east or e - walk east\n"
                  "north or n - walk north\n"
                  "quit - quit the game\n"
                  "respawn or rspw - respawn in the origin on the world\n"
                  "south or s - walk south\n"
                  "west or w - walk west\n\n"
                  "help - this help\n");
    }
    else if (cmd == "reload")
    {
      std::string errLog;
      world.reloadMap(errLog);
      if (!errLog.empty())
        bot.message(lastChannelId, errLog);
      else
        bot.message(lastChannelId, "Map is reloaded");
    }
    else if (cmd == "respawn" || cmd == "rspw")
    {
      hero.respawn();
      bot.message(lastChannelId, world.describeRoom(hero));
    }
    else if ([&]() {
               for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
               {
                 auto d = static_cast<Direction>(i);
                 if ((cmd == toShortString(d) || cmd == toString(d)))
                 {
                   if (!room || room->hasExit(d))
                   {
                     hero.walk(d);
                     bot.message(lastChannelId, world.describeRoom(hero));
                   }
                   else
                     bot.message(lastChannelId, "You cannot walk this way...");
                   return true;
                 }
               }
               return false;
             }())
    {
    }
    else if (cmd == "desc" || cmd == "describe")
      bot.message(lastChannelId, world.describeRoom(hero));
    break;
  }
  }

  if (msg["type"] == 7)
  {
    welcomeToken = bot.invokeFromNow(5s, [this, msg](Bot &bot) {
      const char *welcomeMessages[] = {
        "welcome <@user> go read dem <#rules> and go have fun",
        "whalecum <@user>  dont forget to read the <#rules>",
        "welcome <@user> wHy not go rEad the <#rules> and join our chaos Pwp",
        "Welcome <@user>  please read the <#rules> and enjoy our lord and savior tide pod dog",
        "welsome <@user> dont forget to read the <#rules>!",
        "whalecum <@user> dont forget to read the <#rules>",
        "<@user> welcome to the tyde pod dog legion <#rules>",
        "<43 whalecume <@user> dont forget to read the <#rules>",
      };
      std::string m = welcomeMessages[rand() % sizeof(welcomeMessages) / sizeof(*welcomeMessages)];
      replace(m, "user", msg["author"]["id"].get<std::string>());
      replace(m, "rules", rulesChannelId);
      bot.message(systemChannelId, m);
    });
    return;
  }
  {
    // Scan through mentions in the message for self
    auto isMentioned = [&bot](const json &msg) {
      for (const json &mention : msg["mentions"])
        if (mention["id"] == bot.self()["id"])
          return true;
      return false;
    };
    auto content = msg["content"].get<std::string>();
    if (isMentioned(msg) && content.find("> play") == content.size() - strlen("> play"))
    {
      bot.message(lastChannelId, "You started a game");
      Player player(*redisCon, getPlayerId(msg));
      auto heroesList = player.getHeroesList();
      switch (heroesList.size())
      {
      case 0:
        bot.message(lastChannelId, "What is your name?");
        player.setState(Player::State::HeroName);
        break;
      case 1:
      {
        auto hero = player.getActiveHero();
        player.setState(Player::State::Playing);
        bot.message(lastChannelId, "You are " + hero.getName());
        bot.message(lastChannelId, "Type \"help\" if you need to learn how to play.");
        bot.message(lastChannelId, world.describeRoom(hero));
        break;
      }
      default:
        bot.message(lastChannelId, "// TODO handle more than one hero");
        bot.message(lastChannelId, "You are " + player.getActiveHero().getName());
        player.setState(Player::State::Playing);
        break;
      }
    }
    if (isMentioned(msg) && content.find("?") != std::string::npos)
    {
      token8ball = bot.invokeFromNow(2s, [this](Bot &bot) {
        const char *eightBallAnswers[] = {
          "It is certain.",
          "It is decidedly so.",
          "Without a doubt.",
          "Yes - definitely.",
          "You may rely on it.",
          "As I see it, yes.",
          "Most likely.",
          "Outlook good.",
          "Yes.",
          "Signs point to yes.",
          "Reply hazy, try again.",
          "Ask again later.",
          "Better not tell you now.",
          "Cannot predict now.",
          "Concentrate and ask again.",
          "Don't count on it.",
          "My reply is no.",
          "My sources say no.",
          "Outlook not so good.",
          "Very doubtful.",

          "IT IS CERTAIN!!",
          "IT IS DECIDEDLY SO!!!",
          "WITHOUT A DOUBT!",
          "YES - DEFINITELY",
          "YOU MAY RELY ON IT...",
          "AS I SEE IT, YAS.....",
          "MOST LIKELY",
          "OUTLOOK GOOD",
          "YIS.",
          "SIGNS POINT TO YAS...",
          "REPLY HAZY, TRY AGAIN!!",
          "ASK AGAIN LATER!!!",
          "BETTER NOT TELL YOU NOW",
          "CANNOT PREDICT NOW",
          "CONCENTRATE AND ASK AGAIN",
          "DONT COUNT ON IT",
          "MY REPLY IS NO",
          "MY SOURCES SAY NO",
          "OUTLOOK NOT SO GOOD!",
          "VERY DOUBTFUL...",

          "it is certain...",
          "it is decidedly so...",
          "without a doubt",
          "yIs - definitely",
          "you may rely on it",
          "as i see it, yes",
          "most likely",
          "outlook good",
          "yaaassss...",
          "signs point to yes",
          "reply hazy, try again",
          "ask again later...",
          "better not tell you now.....",
          "cannot predict now",
          "concentrate and ask again",
          "don't count on it",
          "my reply is nu.",
          "my sources say nu.",
          "outlook not so good",
          "very doubtful.",

          "itiscertain...",
          "itisdecidedly so...",
          "without-a-doubt",
          "yIs-definitely",
          "you may rely on it",
          "asiseeit, yes",
          "mostlikely",
          "outlookgood",
          "yes",
          "signspointtoyes",
          "replyhazytryagain",
          "askagainlater...",
          "betternottellyou now.....",
          "cannotpredictnow",
          "concentrateandaskagain",
          "dontcountonit",
          "myreplyisnu.",
          "mysourcessaynu",
          "outlooknotsogood",
          "verydoubtful",

          "ITISCERTAIN...",
          "ITISDECIDEDLY SO...",
          "WITHOUT-A-DOUBT",
          "YIS-DEFINITELY",
          "YOU MAY RELY ON IT",
          "ASISEEIT, YIS",
          "MOSTLIKELY",
          "OUTLOOKGOOD",
          "YAAAsS",
          "SIGNSpOINTtOyES",
          "REPLYhAZYtRYaGAIN",
          "ASKaGAINlATER...",
          "BETTERNOTTELLYOU NOW.....",
          "CANNOTPREDICTNOW",
          "CONCENTRATEANDASKAGAIN",
          "DONTCOUNTONIT",
          "MYREPLYISNuuuU.",
          "MYSOURCESSAYNUuu",
          "OUTLOOKNOTSOGOOD",
          "VERYDOUBTFUL",
        };
        bot.message(
          lastChannelId,
          eightBallAnswers[rand() % sizeof(eightBallAnswers) / sizeof(*eightBallAnswers)]);
      });
      return;
    }
  }
  {
    auto content = msg["content"].get<std::string>();
    std::transform(std::begin(content), std::end(content), std::begin(content), ::tolower);
    if (content.find("housekeeping") != std::string::npos)
    {
      bot.message(lastChannelId, "FBI!");
      return;
    }
  }
  if (rand() % 10 == 0)
  {
    otherToken = bot.invokeFromNow(10s, [this](Bot &bot) {
      const char *words[] = {
        "420",          "<33",     "AAAAAAH",   "AWWWW",     "BOI",          "BOIOOO",
        "BOIU",         "Booooii", "Dab",       "HNNNNNNNG", "HNNNNNNNNNNG", "HNNNNNNNNNNNNNNNG",
        "Jdjdjjdjsiud", "LMAO",    "LOL",       "LOLL",      "LOLOL",        "Lololol",
        "REEEEEEE",     "Uhoh",    "YAAAAAAS",  "YAS",       "YE",           "YEEES CUTE",
        "YIS",          "YUP",     "delicious", "hnnng",     "hohHHHH",      "imcryingggg",
        "lol",          "nOH",     "omg",       "wooot",     "yAAAAAS",      "yaaaay",
        "yay",          "ye",      "yeet",
      };
      bot.message(lastChannelId, words[rand() % sizeof(words) / sizeof(*words)]);
    });
    return;
  }
}

void Guild::messageOnLastChannel(Bot &bot, const std::string &msg)
{
  bot.message(lastChannelId, msg);
}

void Guild::onMemberRemove(Bot &bot, const json &msg)
{
  std::ostringstream content;
  content << "goodbye " << msg["user"]["username"].get<std::string>() << "...";
  bot.message(systemChannelId, content.str());
}

void Guild::onChannelCreate(Bot &, const json &msg)
{
  auto name = msg["name"].get<std::string>();
  std::transform(std::begin(name), std::end(name), std::begin(name), ::tolower);
  if (name.find("rules") != std::string::npos)
    rulesChannelId = msg["id"].get<std::string>();
}
