#pragma once
#include <string>
#include "bot.hpp"

class Guild
{
public:
  Guild(const nlohmann::json &msg);

  void messageOnLastChannel(Bot &, const std::string &msg);
  void onChannelCreate(Bot &, const nlohmann::json &msg);
  void onMemberRemove(Bot &, const nlohmann::json &msg);
  void onMessageCreate(Bot &, const nlohmann::json &msg);

private:
  InvokeToken otherToken;
  InvokeToken token5min;
  InvokeToken token8ball;
  InvokeToken welcomeToken;

  std::string systemChannelId;
  std::string lastChannelId;
  std::string rulesChannelId;
};
