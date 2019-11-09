#pragma once
#include <string>
#include "bot.hpp"
#include "redis_con.hpp"

class Guild
{
public:
  Guild(const nlohmann::json &msg, RedisCon &redisCon);

  void messageOnLastChannel(Bot &, const std::string &msg);
  void onChannelCreate(Bot &, const nlohmann::json &msg);
  void onMemberRemove(Bot &, const nlohmann::json &msg);
  void onMessageCreate(Bot &, const nlohmann::json &msg);

private:
  InvokeToken otherToken;
  InvokeToken token8ball;
  InvokeToken welcomeToken;

  std::string systemChannelId;
  std::string lastChannelId;
  std::string rulesChannelId;

  RedisCon *redisCon;
};
