#include "bot.hpp"
#include "guild.hpp"
#include <iostream>
#include <unordered_map>
#include <hiredis/hiredis.h>

using json = nlohmann::json;
using system_clock = std::chrono::system_clock;

namespace
{
  auto get420Time()
  {
    auto now = system_clock::to_time_t(system_clock::now());
    std::tm tm;
    gmtime_r(&now, &tm);
    tm.tm_sec = 30;
    tm.tm_min = 20;
    tm.tm_hour = 0; // 4pm Pasific Time
    auto newTime = timegm(&tm);
    while (newTime <= now)
      newTime += 24 * 60 * 60;
    return system_clock::from_time_t(newTime);
  }

  std::unordered_map<std::string, Guild> guilds;
  enum class GuildNotFoundError;

  Guild &getGuild(const json &msg)
  {
    std::string guildId = msg["guild_id"].get<std::string>();
    auto it = guilds.find(guildId);
    if (it == std::end(guilds))
    {
      std::cerr << "Guild " << guildId << " is not found\n";
      throw GuildNotFoundError{};
    }
    return it->second;
  }
} // namespace

int main()
{
  std::cout << "Starting bot...\n\n";
  srand(time(nullptr));

  auto redisCon = redisConnect("127.0.0.1", 6379);
  if (!redisCon)
  {
    std::cerr << "Could not allocate redis context\n";
    return -1;
  }

  if (redisCon->err)
  {
    std::cerr << "Error: " << redisCon->errstr << std::endl;
    return -1;
  }

  Bot bot;
  bot.reg(Handler::MessageCreate, [](Bot &bot, const json &msg) {
    try
    {
      // std::cout << "MESSAGE_CREATE: " << msg.dump(4) << std::endl;
      getGuild(msg).onMessageCreate(bot, msg);
    }
    catch (GuildNotFoundError)
    {
    }
  });

  bot.reg(Handler::GuildMemberRemove, [](Bot &bot, const json &msg) {
    try
    {
      // std::cout << "GUILD_MEMBER_REMOVE: " << msg.dump(4) << std::endl;
      getGuild(msg).onMemberRemove(bot, msg);
    }
    catch (GuildNotFoundError)
    {
    }
  });

  bot.reg(Handler::GuildMemberAdd, [](Bot &bot, const json &msg) {
    // std::cout << "GUILD_MEMBER_ADD: " << msg.dump(4) << std::endl;
  });

  bot.reg(Handler::GuildCreate, [](Bot &bot, const json &msg) {
    // std::cout << "GUILD_CREATE: " << msg.dump(4) << std::endl;
    std::cout << "Guild: " << msg["name"].get<std::string>() << std::endl;
    guilds.emplace(msg["id"].get<std::string>(), msg);
  });

  bot.reg(Handler::PresenceUpdate, [](Bot &bot, const json &msg) {});

  bot.reg(Handler::TypingStart, [](Bot &bot, const json &msg) {});

  bot.reg(Handler::ChannelCreate, [](Bot &bot, const json &msg) {
    try
    {
      // std::cout << "CHANNEL_CREATE: " << msg.dump(4) << std::endl;
      getGuild(msg).onChannelCreate(bot, msg);
    }
    catch (GuildNotFoundError)
    {
    }
  });

  InvokeToken token;
  std::function<void(Bot &)> invoke = [&token, &invoke](Bot &bot) {
    for (auto &guild : guilds)
      guild.second.messageOnLastChannel(bot, "420");
    token = bot.invokeAt(get420Time(), invoke);
  };
  token = bot.invokeAt(get420Time(), invoke);

  bot.run();
  return 0;
}
