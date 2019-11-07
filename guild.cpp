#include "guild.hpp"

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
} // namespace

Guild::Guild(const json &msg)
  : systemChannelId(msg["system_channel_id"].get<std::string>()),
    lastChannelId(systemChannelId),
    rulesChannelId(systemChannelId)
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
  if (msg["author"]["id"] != bot.self()["id"])
  {
    token5min = bot.invokeFromNow(5min, [this](Bot &bot) { bot.message(lastChannelId, "yeet"); });
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
  {
    rulesChannelId = msg["id"].get<std::string>();
  }
}
