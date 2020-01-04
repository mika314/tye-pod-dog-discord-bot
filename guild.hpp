#pragma once
#include "bot.hpp"
#include "redis_con.hpp"
#include "world.hpp"
#include <string>

class Guild
{
public:
  Guild(const nlohmann::json &msg, RedisCon &redisCon);

  void messageOnLastChannel(Bot &, const std::string &msg);
  void onChannelCreate(Bot &, const nlohmann::json &msg);
  void onMemberRemove(Bot &, const nlohmann::json &msg);
  void onMessageCreate(Bot &, const nlohmann::json &msg);
  std::vector<std::string> getTwitchChannelsToMonitor() const;
  void setLiveChannels(Bot &, const std::vector<std::string> &);

private:
  InvokeToken otherToken;
  InvokeToken token8ball;
  InvokeToken welcomeToken;

  RedisCon *redisCon;

  std::string id;

  std::string systemChannelId;
  std::string lastChannelId;
  std::string rulesChannelId;
  std::string announsChannelId;

  World world;
};
