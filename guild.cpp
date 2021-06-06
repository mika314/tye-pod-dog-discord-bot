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

static std::string getLastChannelId(RedisCon &redisCon,
                                    const std::string &id,
                                    const std::string &systemChannelId)
{
  try
  {
    return redisCon.cmd<std::string>("GET guild/%s/lastChannelId", id.c_str());
  }
  catch (...)
  {
    redisCon.cmd<std::string>("SET guild/%s/lastChannelId %s", id.c_str(), systemChannelId.c_str());
    return systemChannelId;
  }
}

Guild::Guild(const json &msg, RedisCon &redisCon)
  : redisCon(&redisCon),
    id(msg["id"].get<std::string>()),
    name(msg["name"].get<std::string>()),
    systemChannelId(msg["system_channel_id"].get<std::string>()),
    lastChannelId(getLastChannelId(redisCon, id, systemChannelId)),
    rulesChannelId(systemChannelId),
    announsChannelId(systemChannelId),
    world(redisCon, id)
{
  std::cout << "Guild: " << name << std::endl;
  for (const auto &ch : msg["channels"])
  {
    auto name = ch["name"].get<std::string>();
    std::transform(std::begin(name), std::end(name), std::begin(name), ::tolower);
    if (name.find("rules") != std::string::npos)
      rulesChannelId = ch["id"].get<std::string>();
    if (name.find("announcements") != std::string::npos)
      announsChannelId = ch["id"].get<std::string>();
  }
}

static std::string trim(const std::string &str)
{
  size_t first = str.find_first_not_of(' ');
  if (std::string::npos == first)
  {
    return str;
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

void Guild::onMessageCreate(Bot &bot, const json &msg)
{
  // std::cout << msg.dump() << std::endl;
  lastChannelId = msg["channel_id"].get<std::string>();
  redisCon->cmd<std::string>("SET guild/%s/lastChannelId %s", id.c_str(), lastChannelId.c_str());
  auto sendMsg = [this, &bot](const std::string &msg) {
    if (msg.empty())
      return;
    bot.message(lastChannelId, msg);
  };
  {
    /*
      {
        "attachments" : [

        ],
        "author" : {
          "avatar" : "3048c354e5cbc1bb94da0339e8540935",
          "discriminator" : "1415",
          "id" : "466816161309523969",
          "public_flags" : 0,
          "username" : "Mika3"
        },
        "channel_id" : "641721960052555776",
        "components" : [

        ],
        "content" : "test <@!640973029366693920> ?",
        "edited_timestamp" : null,
        "embeds" : [

        ],
        "flags" : 0,
        "guild_id" : "640993083399471134",
        "id" : "851204404862124062",
        "member" : {
          "deaf" : false,
          "hoisted_role" : null,
          "joined_at" : "2019-11-04T19:17:40.161000+00:00",
          "mute" : false,
          "roles" : [

          ]
        },
        "mention_everyone" : false,
        "mention_roles" : [

        ],
        "mentions" : [ {
          "avatar" : null,
          "bot" : true,
          "discriminator" : "7540",
          "id" : "640973029366693920",
          "member" : {
            "deaf" : false,
            "hoisted_role" : null,
            "joined_at" : "2019-11-04T19:20:43.226000+00:00",
            "mute" : false,
            "roles" : ["640993851276001340"]
          },
          "public_flags" : 0,
          "username" : "tye-pod-dog-dev"
        } ],
        "nonce" : "851204393612083200",
        "pinned" : false,
        "referenced_message" : null,
        "timestamp" : "2021-06-06T21:02:24.732000+00:00",
        "tts" : false,
        "type" : 0
      }
    */

    auto content = msg["content"].get<std::string>();
    for (const json &mention : msg["mentions"])
    {
      auto str2 = "<@!" + mention["id"].get<std::string>() + ">";
      for (auto p = content.find(str2); p != std::string::npos; p = content.find(str2))
        content.replace(p, str2.size(), mention["username"].get<std::string>());
    }
    std::ostringstream ss;
    ss << msg["author"]["username"].get<std::string>() << ": " << content;
    std::cout << ss.str() << std::endl;
    gpt3Bot.addMsg(lastChannelId, ss.str());
  }
  Player player{
    *redisCon, msg["guild_id"].get<std::string>(), msg["author"]["id"].get<std::string>()};
  if (player.getChannelId() == lastChannelId)
  {
    std::ostringstream strm;
    player.processCmd(strm, world, msg["content"].get<std::string>());
    sendMsg(strm.str());
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
      std::ostringstream strm;
      player.startTheGame(strm, world, lastChannelId);
      sendMsg(strm.str());
    }
    if (isMentioned(msg) && content.find("> list") == content.size() - strlen("> list"))
    {
      auto channels = getTwitchChannelsToMonitor();
      if (channels.empty())
        sendMsg("Nothing is monitored");
      else
      {
        std::ostringstream strm;
        for (const auto &ch : channels)
          strm << ch << std::endl;
        sendMsg(strm.str());
      }
    }
    if (isMentioned(msg) && content.find("> monitor") != std::string::npos)
    {
      auto login = trim(content.substr(content.find("> monitor") + strlen("> monitor")));
      redisCon->cmd<std::string>("SET twitch/%s/%s offline", id.c_str(), login.c_str());
      sendMsg(login + " is monitored now");
    }
    if (isMentioned(msg) && content.find("> unmonitor") != std::string::npos)
    {
      auto login = trim(content.substr(content.find("> unmonitor") + strlen("> unmonitor")));
      redisCon->cmd<int>("DEL twitch/%s/%s", id.c_str(), login.c_str());
      sendMsg(login + " is unmonitored now");
    }
    if (isMentioned(msg))
    {
      otherToken = bot.invokeFromNow(
        2s, [sendMsg, msg = gpt3Bot.getMsg(lastChannelId)](Bot &bot) { sendMsg(msg); });
      return;
    }
  }
  {
    auto content = msg["content"].get<std::string>();
    std::transform(std::begin(content), std::end(content), std::begin(content), ::tolower);
    if (content.find("housekeeping") != std::string::npos)
    {
      sendMsg("FBI!");
      return;
    }
  }
  if (rand() % 10 == 0)
  {
    otherToken = bot.invokeFromNow(
      10s, [sendMsg, msg = gpt3Bot.getMsg(lastChannelId)](Bot &bot) { sendMsg(msg); });
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

std::vector<std::string> Guild::getTwitchChannelsToMonitor() const
{
  std::vector<std::string> ret;
  auto twitchNames = redisCon->cmd<std::vector<std::string>>("KEYS twitch/%s/*", id.c_str());
  for (const auto &name : twitchNames)
  {
    std::istringstream strm(name);
    std::string tmp;
    std::getline(strm, tmp, '/');
    assert(tmp == "twitch");
    std::getline(strm, tmp, '/');
    assert(tmp == id);
    std::string login;
    std::getline(strm, login, '/');
    ret.emplace_back(login);
  }
  return ret;
}

void Guild::setLiveChannels(Bot &bot, const std::vector<std::string> &liveChannels)
{
  std::array streamMessages = {
    "STRRRRRRREAMIIIIIIING",
    "HEY it'z TIME <3",
    "WE LIVE BOIS",
    "WE LIVE MY DUDES :heart:",
    "LIVE MY DUDEDS",
    "WE STARTINGING!",
    "STREAMIN LIKE A VILLAN",
    "Stream is starting!",
    "WE ARE LIVE",
  };

  auto channels = getTwitchChannelsToMonitor();
  for (const auto &ch : channels)
  {
    auto oldIsLive = redisCon->cmd<std::string>("GET twitch/%s/%s", id.c_str(), ch.c_str());
    auto isLive =
      ((std::find(std::begin(liveChannels), std::end(liveChannels), ch) != std::end(liveChannels))
         ? "online"
         : "offline");
    if (oldIsLive != isLive)
    {
      redisCon->cmd<std::string>("SET twitch/%s/%s %s", id.c_str(), ch.c_str(), isLive);
      if (isLive == "online")
      {
        std::ostringstream content;
        content << "@everyone " << streamMessages[rand() % streamMessages.size()]
                << "\n"
                   "https://www.twitch.tv/"
                << ch;
        bot.message(announsChannelId, content.str());
      }
    }
  }
}

std::string Guild::getName() const
{
  return name;
}
