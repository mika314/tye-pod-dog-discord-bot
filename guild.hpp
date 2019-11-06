#pragma once
#include <string>
#include "bot.hpp"

class Guild
{
public:
  std::string systemChannelId;
  std::string rulesChannelId;
  std::string lastChannelId;
  InvokeToken otherToken;
  InvokeToken welcomeToken;
  InvokeToken token8ball;
  InvokeToken token5min;
};
