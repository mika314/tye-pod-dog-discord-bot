#pragma once
#include <boost/asio.hpp>
#include <curl/curl.h>
#include <functional>
#include <vector>

class Twitch
{
public:
  Twitch();
  ~Twitch();
  void queryLiveChannels(const std::vector<std::string> &channels,
                         std::function<void(const std::vector<std::string> &)> &&);
};
