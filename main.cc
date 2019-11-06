#include "bot.hpp"
#include "guild.hpp"
#include <iostream>
#include <unordered_map>

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

  auto get420time()
  {
    using namespace std::chrono;
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

} // namespace

int main()
{
  using json = nlohmann::json;
  using namespace std::literals::chrono_literals;
  std::cout << "Starting bot...\n\n";
  srand(time(nullptr));
  std::unordered_map<std::string, Guild> guilds;

  Bot bot;
  bot.reg(Handler::MessageCreate, [&guilds](Bot &bot, const json &msg) {
    // std::cout << "MESSAGE_CREATE: " << msg.dump(4) << std::endl;
    std::string guildId = msg["guild_id"].get<std::string>();
    auto &guild = guilds[guildId];
    guild.lastChannelId = msg["channel_id"].get<std::string>();
    if (msg["type"] == 7)
    {
      guild.welcomeToken = bot.invokeFromNow(5s, [&guild, msg](Bot &bot) {
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
        std::string m =
          welcomeMessages[rand() % sizeof(welcomeMessages) / sizeof(*welcomeMessages)];
        replace(m, "user", msg["author"]["id"].get<std::string>());
        replace(m, "rules", guild.rulesChannelId);
        bot.message(guild.systemChannelId, m);
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
        guild.token8ball = bot.invokeFromNow(2s, [&guild](Bot &bot) {
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
            guild.lastChannelId,
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
        bot.message(guild.lastChannelId, "FBI!");
        return;
      }
    }
    if (rand() % 10 == 0)
    {
      guild.otherToken = bot.invokeFromNow(10s, [&guild](Bot &bot) {
        const char *words[] = {
          "yeet",
          "420",
          "YAS",
          "YIS",
          "Lololol",
          "LMAO",
          "AWWWW",
          "REEEEEEE",
          "YAAAAAAS",
          "LOLOL",
          "YE",
          "HNNNNNNNG",
          "HNNNNNNNNNNG",
          "HNNNNNNNNNNNNNNNG",
          "BOI",
          "BOIOOO",
          "Dab",
        };
        bot.message(guild.lastChannelId, words[rand() % sizeof(words) / sizeof(*words)]);
      });
      return;
    }
    if (msg["author"]["id"] != bot.self()["id"])
    {
      guild.token5min =
        bot.invokeFromNow(5min, [&guild](Bot &bot) { bot.message(guild.lastChannelId, "yeet"); });
      return;
    }
  });
  bot.reg(Handler::GuildMemberRemove, [&guilds](Bot &bot, const json &msg) {
    // std::cout << "GUILD_MEMBER_REMOVE: " << msg.dump(4) << std::endl;

    std::ostringstream content;
    std::string guildId = msg["guild_id"].get<std::string>();
    const auto &guild = guilds[guildId];
    content << "goodbye " << msg["user"]["username"].get<std::string>() << "...";
    bot.message(guild.systemChannelId, content.str());

  });
  bot.reg(Handler::GuildMemberAdd, [&guilds](Bot &bot, const json &msg) {
    // std::cout << "GUILD_MEMBER_ADD: " << msg.dump(4) << std::endl;

  });
  bot.reg(Handler::GuildCreate, [&guilds](Bot &bot, const json &msg) {
    // std::cout << "GUILD_CREATE: " << msg.dump(4) << std::endl;
    auto &guild = guilds[msg["id"].get<std::string>()];
    guild.systemChannelId = msg["system_channel_id"].get<std::string>();
    guild.lastChannelId = guild.systemChannelId;
    for (const auto &ch : msg["channels"])
    {
      auto name = ch["name"].get<std::string>();
      std::transform(std::begin(name), std::end(name), std::begin(name), ::tolower);
      if (name.find("rules") != std::string::npos)
      {
        guild.rulesChannelId = ch["id"].get<std::string>();
        break;
      }
    }
  });
  bot.reg(Handler::PresenceUpdate, [](Bot &bot, const json &msg) {});
  bot.reg(Handler::TypingStart, [](Bot &bot, const json &msg) {});
  InvokeToken token;

  std::function<void(Bot &)> invoke = [&token, &invoke, &guilds](Bot &bot) {
    for (auto &guild : guilds)
      bot.message(guild.second.lastChannelId, "420");
    token = bot.invokeAt(get420time(), invoke);
  };
  token = bot.invokeAt(get420time(), invoke);

  bot.run();
  return 0;
}
