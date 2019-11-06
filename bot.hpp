#pragma once
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>
#include <chrono>

namespace Internal
{
  class Bot;
  struct Timer;
}

enum class Handler {
  MessageCreate,
  GuildMemberRemove,
  GuildMemberAdd,
  GuildCreate,
  PresenceUpdate,
  TypingStart,
};

class [[nodiscard]] InvokeToken
{
  friend Internal::Bot;
public:
  InvokeToken();
  ~InvokeToken();
  InvokeToken(const InvokeToken &) = delete;
  InvokeToken(InvokeToken &&);
  InvokeToken &operator=(const InvokeToken &) = delete;
  InvokeToken &operator=(InvokeToken &&);

private:
  InvokeToken(Internal::Timer &&);
  std::unique_ptr<Internal::Timer> timer;
};

class Bot
{
public:
  Bot();
  ~Bot();
  void run();
  void reg(Handler, std::function<void(Bot &, const nlohmann::json &)>);
  const nlohmann::json& self() const;
  void message(const std::string &channelId, const std::string &message);
  InvokeToken invokeAt(std::chrono::system_clock::time_point, std::function<void(Bot &)>);
  InvokeToken invokeFromNow(std::chrono::milliseconds, std::function<void(Bot &)>);

private:
  std::unique_ptr<Internal::Bot> bot;
};