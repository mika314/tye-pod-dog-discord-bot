#include "bot.hpp"
#include "guild.hpp"
#include "redis_con.hpp"
#include "twitch.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

using json = nlohmann::json;
using system_clock = std::chrono::system_clock;

namespace
{
  auto get420Time()
  {
    auto now = system_clock::to_time_t(system_clock::now());
    std::tm tm;
    localtime_r(&now, &tm);
    tm.tm_sec = 30;
    tm.tm_min = 20;
    tm.tm_hour = 16;

    auto newTime = mktime(&tm);
    while (newTime <= now)
      newTime += 24 * 60 * 60;
    return system_clock::from_time_t(newTime);
  }

  std::unordered_map<std::string, Guild> guilds;
  RedisCon redisCon;

  Guild *getGuild(const json &msg)
  {
    auto jsIt = msg.find("guild_id");
    if (jsIt == std::end(msg))
      return nullptr;
    std::string guildId = jsIt->get<std::string>();
    auto it = guilds.find(guildId);
    if (it == std::end(guilds))
      return nullptr;
    return &it->second;
  }
} // namespace

int main()
{
  std::cout << "Starting bot...\n\n";
  srand(time(nullptr));
  Twitch twitch;
  Bot bot;
  bot.reg(Handler::MessageCreate, [](Bot &bot, const json &msg) {
    // std::cout << "MESSAGE_CREATE: " << msg.dump(4) << std::endl;
    if (auto guild = getGuild(msg))
      guild->onMessageCreate(bot, msg);
    else
    {
      if (msg["author"]["id"] == bot.self()["id"])
        return;
      // std::cout << "MESSAGE_CREATE: " << msg.dump(4) << std::endl;
      auto author = msg["author"]["username"].get<std::string>();
      std::transform(std::begin(author), std::end(author), std::begin(author), ::tolower);
      if (author.find("mohjii") != std::string::npos)
      {
        auto it = std::find_if(std::begin(guilds),
                               std::end(guilds),
                               [](const std::pair<const std::string, Guild> &value) {
                                 auto guildName = value.second.getName();
                                 std::transform(std::begin(guildName),
                                                std::end(guildName),
                                                std::begin(guildName),
                                                ::tolower);
                                 return guildName.find("shit artists do") != std::string::npos;
                               });
        if (it != std::end(guilds))
          it->second.messageOnLastChannel(bot, msg["content"].get<std::string>());
        else
          std::cout << "guild \"shit artists do\" not found\n";
      }
      else
        bot.message(msg["channel_id"].get<std::string>(), "You want to have fun alone?");
    }
  });

  bot.reg(Handler::GuildMemberRemove, [](Bot &bot, const json &msg) {
    // std::cout << "GUILD_MEMBER_REMOVE: " << msg.dump(4) << std::endl;
    if (auto guild = getGuild(msg))
      guild->onMemberRemove(bot, msg);
  });

  bot.reg(Handler::GuildMemberAdd, [](Bot &bot, const json &msg) {
    // std::cout << "GUILD_MEMBER_ADD: " << msg.dump(4) << std::endl;
  });

  bot.reg(Handler::GuildCreate, [](Bot &bot, const json &msg) {
    // std::cout << "GUILD_CREATE: " << msg.dump(4) << std::endl;
    guilds.emplace(msg["id"].get<std::string>(), Guild{msg, redisCon});
  });

  bot.reg(Handler::PresenceUpdate, [](Bot &bot, const json &msg) {});

  bot.reg(Handler::TypingStart, [](Bot &bot, const json &msg) {});

  bot.reg(Handler::ChannelCreate, [](Bot &bot, const json &msg) {
    // std::cout << "CHANNEL_CREATE: " << msg.dump(4) << std::endl;
    if (auto guild = getGuild(msg))
      guild->onChannelCreate(bot, msg);
  });

  InvokeToken token;
  std::function<void(Bot &)> invoke = [&token, &invoke](Bot &bot) {
    for (auto &guild : guilds)
      guild.second.messageOnLastChannel(bot, "420");
    token = bot.invokeAt(get420Time(), invoke);
  };
  token = bot.invokeAt(get420Time(), invoke);

  InvokeToken twitchToken;
  std::function<void(Bot &)> twitchInvoke = [&twitchToken, &twitchInvoke, &twitch](Bot &bot) {
    try
    {
      std::vector<std::string> channels;
      for (auto &guild : guilds)
      {
        auto tmp = guild.second.getTwitchChannelsToMonitor();
        channels.insert(std::end(channels), std::begin(tmp), std::end(tmp));
      }

      std::sort(std::begin(channels), std::end(channels));
      channels.erase(std::unique(std::begin(channels), std::end(channels)), std::end(channels));

      twitch.queryLiveChannels(channels, [&bot](const std::vector<std::string> &live) {
        for (auto &guild : guilds)
          guild.second.setLiveChannels(bot, live);
      });
    }
    catch (std::runtime_error &e)
    {
      std::cerr << e.what() << std::endl;
    }
    using namespace std::literals::chrono_literals;
    twitchToken = bot.invokeFromNow(1min, twitchInvoke);
  };

  twitchInvoke(bot);

  bot.run();
  return 0;
}
