#pragma once
#include <chrono>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_set>

namespace Internal
{
  class Bot;
  struct Timer;
} // namespace Internal

enum class Handler {
  ChannelCreate,
  ChannelUpdate,
  GuildCreate,
  GuildMemberAdd,
  GuildMemberRemove,
  GuildMemberUpdate,
  GuildRoleCreate,
  MessageCreate,
  MessageReactionAdd,
  MessageUpdate,
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
  bool operator==(const InvokeToken &token) const;

  class Hash
  {
  public:
    size_t operator()(const InvokeToken &p) const
    {
      return std::hash<Internal::Timer *>{}(p.timer.get());
    }
  };

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
  const nlohmann::json &self() const;
  void message(const std::string &channelId, const std::string &message);
  InvokeToken invokeAt(std::chrono::system_clock::time_point, std::function<void(Bot &)>);
  InvokeToken invokeFromNow(std::chrono::milliseconds, std::function<void(Bot &)>);

private:
  std::unique_ptr<Internal::Bot> bot;
  std::unordered_set<InvokeToken, InvokeToken::Hash> tokens;
};