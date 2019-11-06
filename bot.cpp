#include "bot.hpp"

#include "read_token.hpp"
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <discordpp/bot.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-beast.hh>
#include <fstream>
#include <iostream>
#include <locale>

namespace
{
  std::string toString(Handler handler)
  {
    switch (handler)
    {
    case Handler::MessageCreate: return "MESSAGE_CREATE";
    case Handler::GuildMemberRemove: return "GUILD_MEMBER_REMOVE";
    case Handler::GuildMemberAdd: return "GUILD_MEMBER_ADD";
    case Handler::GuildCreate: return "GUILD_CREATE";
    case Handler::PresenceUpdate: return "PRESENCE_UPDATE";
    case Handler::TypingStart: return "TYPING_START";
    };
  }
} // namespace



namespace Internal
{
  namespace asio = boost::asio;
  using json = nlohmann::json;
  namespace dpp = discordpp;
  using DppBot = dpp::WebsocketBeast<dpp::RestBeast<dpp::Bot>>;

  class Bot
  {
  public:
    Bot(::Bot &external);
    void run();
    void message(const std::string &channelId, const std::string &message);
    void reg(Handler, std::function<void(::Bot &, const nlohmann::json &)>);
    InvokeToken invokeAt(std::chrono::system_clock::time_point, std::function<void(::Bot &)>);
    InvokeToken invokeFromNow(std::chrono::milliseconds, std::function<void(::Bot &)>);
    json self;

  private:
    ::Bot &external;
    DppBot bot;
    std::shared_ptr<asio::io_context> aioc;
  };

  struct Timer
  {
    Timer(boost::asio::system_timer &&timer) : timer(std::move(timer)) {}
    boost::asio::system_timer timer;
  };

  Bot::Bot(::Bot &external) : external(external), aioc(std::make_shared<asio::io_context>())
  {
    /*/
     * Create handler for the READY payload, this may be handled by the bot in the future.
     * The `self` object contains all information about the 'bot' user.
    /*/
    bot.handlers.insert({"READY", [this](json data) { self = data["user"]; }});

    // Set the bot up
    bot.initBot(6, readTokenFile("token.dat"), aioc);
  }

  void Bot::run() { bot.run(); }
  void Bot::message(const std::string &channelId, const std::string &message)
  {
    bot.call("POST", "/channels/" + channelId + "/messages", {{"content", message}});
  }

  void Bot::reg(Handler h, std::function<void(::Bot &, const nlohmann::json &)> cb)
  {
    bot.handlers.insert({toString(h), [this, cb{std::move(cb)}](json msg) { cb(external, msg); }});
  }

  InvokeToken Bot::invokeAt(std::chrono::system_clock::time_point timePoint,
                              std::function<void(::Bot &)> invoke)
  {
    auto timer{boost::asio::system_timer(*aioc)};
    timer.expires_at(timePoint);
    timer.async_wait([this, invoke{std::move(invoke)}](boost::system::error_code err) {
      if (err == boost::asio::error::operation_aborted)
      {
        std::cerr << "timer is canceled\n";
        return;
      }
      if (err != boost::system::errc::success)
      {
        std::cerr << "error code: " << err << std::endl;
        return;
      }
      invoke(external);
    });
    return InvokeToken{Timer{std::move(timer)}};
  }
  InvokeToken Bot::invokeFromNow(std::chrono::milliseconds duration,
                                   std::function<void(::Bot &)> invoke)
  {
    auto timer{boost::asio::system_timer(*aioc)};
    timer.expires_from_now(duration);
    timer.async_wait([this, invoke](boost::system::error_code err) {
      if (err == boost::asio::error::operation_aborted)
      {
        std::cerr << "timer is canceled\n";
        return;
      }
      if (err != boost::system::errc::success)
      {
        std::cerr << "error code: " << err << std::endl;
        return;
      }
      invoke(external);
    });
    return InvokeToken{Timer{std::move(timer)}};
  }
} // namespace Internal

Bot::Bot() : bot(std::make_unique<Internal::Bot>(*this)) {}

void Bot::run()
{
  bot->run();
}

Bot::~Bot() {}

void Bot::reg(Handler h, std::function<void(Bot &, const nlohmann::json &)> cb)
{
  bot->reg(h, std::move(cb));
}

const nlohmann::json &Bot::self() const
{
  return bot->self;
}

void Bot::message(const std::string &channelId, const std::string &message)
{
  bot->message(channelId, message);
}

InvokeToken Bot::invokeAt(std::chrono::system_clock::time_point timePoint,
                            std::function<void(Bot &)> invoke)
{
  return bot->invokeAt(timePoint, std::move(invoke));
}

InvokeToken Bot::invokeFromNow(std::chrono::milliseconds duration,
                                 std::function<void(Bot &)> invoke)
{
  return bot->invokeFromNow(duration, std::move(invoke));
}

InvokeToken::InvokeToken() = default;

InvokeToken::~InvokeToken() = default;

InvokeToken::InvokeToken(InvokeToken &&) = default;

InvokeToken &InvokeToken::operator=(InvokeToken &&) = default;

InvokeToken::InvokeToken(Internal::Timer &&timer)
  : timer(std::make_unique<Internal::Timer>(std::move(timer)))
{
}

