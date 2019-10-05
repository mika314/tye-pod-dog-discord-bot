#include "guild.hpp"
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <discordpp/bot.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-beast.hh>
#include <fstream>
#include <iostream>
#include <locale>

namespace asio = boost::asio;
using json = nlohmann::json;
namespace dpp = discordpp;
using DppBot = dpp::WebsocketBeast<dpp::RestBeast<dpp::Bot>>;

std::string readTokenFile(const std::string &tokenFilePath);

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

int main()
{
  std::cout << "Starting bot...\n\n";

  /*/
   * Read token from token file.
   * Tokens are required to communicate with Discord, and hardcoding tokens is a bad idea.
   * If your bot is open source, make sure it's ignore by git in your .gitignore file.
  /*/
  std::string token;
  if (boost::filesystem::exists("token.dat"))
  {
    token = readTokenFile("token.dat");
  }
  else
  {
    std::cerr << "CRITICAL: There is no valid way for Discord++ to obtain a token! Copy the "
                 "example login.dat or token.dat to make one.\n";
    exit(1);
  }

  // Create Bot object
  DppBot bot;

  std::unordered_map<std::string, Guild> guilds;

  /*/
   * Create handler for the READY payload, this may be handled by the bot in the future.
   * The `self` object contains all information about the 'bot' user.
  /*/
  json self;
  bot.handlers.insert({"READY", [&bot, &self](json data) { self = data["user"]; }});

  // Create handler for the MESSAGE_CREATE payload, this recieves all messages sent that the bot can
  // see.
  bot.handlers.insert(
    {"MESSAGE_CREATE", [&bot, &self, &guilds](json msg) {
       // std::cout << "MESSAGE_CREATE: " << msg.dump(4) << std::endl;
       if (rand() % 10 == 0)
       {
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
         bot.call("POST",
                  "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                  {{"content", words[rand() % sizeof(words) / sizeof(*words)]}});
       }

       if (msg["type"] == 7)
       {
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
         std::string guildId = msg["guild_id"].get<std::string>();
         const auto &guild = guilds[guildId];
         std::string message =
           welcomeMessages[rand() % sizeof(welcomeMessages) / sizeof(*welcomeMessages)];
         replace(message, "user", msg["author"]["id"].get<std::string>());
         replace(message, "rules", guild.rulesChannelId);
         bot.call("POST",
                  "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                  {{"content", message}});
       }

       auto content = msg["content"].get<std::string>();
       std::transform(std::begin(content), std::end(content), std::begin(content), ::tolower);
       if (content.find("housekeeping") != std::string::npos)
       {
         bot.call("POST",
                  "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                  {{"content", "FBI!"}});
       }
     }});
  bot.handlers.insert({"GUILD_MEMBER_REMOVE", [&bot, &self, &guilds](json msg) {
                         // std::cout << "GUILD_MEMBER_REMOVE: " << msg.dump(4) << std::endl;

                         std::ostringstream content;
                         std::string guildId = msg["guild_id"].get<std::string>();
                         const auto &guild = guilds[guildId];
                         content << "goodbye <@" << msg["user"]["id"].get<std::string>() << ">";
                         bot.call("POST",
                                  "/channels/" + guild.systemChannelId + "/messages",
                                  {{"content", content.str()}});
                       }});
  bot.handlers.insert({"GUILD_MEMBER_ADD", [&bot, &self, &guilds](json msg) {
                         // std::cout << "GUILD_MEMBER_ADD: " << msg.dump(4) << std::endl;
                       }});

  // These handlers silence the GUILD_CREATE, PRESENCE_UPDATE, and TYPING_START payloads, as
  // they're some that you see a lot.
  bot.handlers.insert({"GUILD_CREATE", [&guilds](json msg) {
                         // std::cout << "GUILD_CREATE: " << msg.dump(4) << std::endl;
                         auto &guild = guilds[msg["id"].get<std::string>()];
                         guild.systemChannelId = msg["system_channel_id"].get<std::string>();
                         for (const auto &ch : msg["channels"])
                         {
                           auto name = ch["name"].get<std::string>();
                           std::transform(
                             std::begin(name), std::end(name), std::begin(name), ::tolower);
                           if (name.find("rules") != std::string::npos)
                           {
                             guild.rulesChannelId = ch["id"].get<std::string>();
                             break;
                           }
                         }
                       }});
  bot.handlers.insert({"PRESENCE_UPDATE", [](json) {}}); // Ignoring
  bot.handlers.insert({"TYPING_START", [](json) {}});    // Ignoring

  // Create Asio context, this handles async stuff.
  auto aioc = std::make_shared<asio::io_context>();

  // Set the bot up
  bot.initBot(6, token, aioc);

  // Run the bot!
  bot.run();

  return 0;
}

std::string readTokenFile(const std::string &tokenFilePath)
{
  std::ifstream tokenFile;
  tokenFile.open(tokenFilePath);

  std::string token;

  if (tokenFile.is_open())
  {
    std::getline(tokenFile, token);
  }
  else
  {
    std::cerr << "CRITICAL: There is no such file as " + tokenFilePath +
                   "! Copy the example login.dat to make one.\n";
    exit(1);
  }
  tokenFile.close();
  std::cout << "Retrieved token.\n\n";

  return token;
}