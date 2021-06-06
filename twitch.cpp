#include "twitch.hpp"
#include "curl_glob_init.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

Twitch::Twitch()
{
  curlGlobInit();
}

static size_t curlWrite(void *buffer, size_t size, size_t nmemb, void *userp)
{
  ((std::ostringstream *)userp)->write((char *)buffer, size * nmemb);
  return size * nmemb;
}

void Twitch::queryLiveChannels(const std::vector<std::string> &channels,
                               std::function<void(const std::vector<std::string> &)> &&cb)
{
  if (channels.empty())
  {
    cb({});
    return;
  }
  // run curl
  // make json
  std::ostringstream strm;
  std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> tmp(curl_easy_init(), curl_easy_cleanup);
  if (!tmp)
    throw std::runtime_error("Failed to init");
  auto handle = tmp.get();
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, curlWrite);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &strm);
  std::string url;
  url = "https://api.twitch.tv/helix/streams";
  bool first = true;
  for (const auto &ch : channels)
  {
    if (first)
    {
      url += "?";
      first = false;
    }
    else
      url += "&";
    url += "user_login=";
    url += ch;
  }
  curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "Client-ID: nrsbk40717wpyavud359mv02l66923");
  curl_easy_setopt(handle, CURLOPT_HTTPHEADER, chunk);
  long noSignal = 1;
  curl_easy_setopt(handle, CURLOPT_NOSIGNAL, noSignal);
  // curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
  // curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
  CURLcode code = curl_easy_perform(handle);
  strm.flush();
  if (code != CURLE_OK)
  {
    std::ostringstream strm;
    strm << "Could not download. CURL finished with error " << code << ": "
         << curl_easy_strerror(code);
    throw std::runtime_error(strm.str());
  }

  // {
  //    "data":[
  //       {
  //          "id":"36483589360",
  //          "user_id":"224389503",
  //          "user_name":"Mika314",
  //          "game_id":"509667",
  //          "type":"live",
  //          "title":"Cooking for Mohjii",
  //          "viewer_count":1,
  //          "started_at":"2019-12-24T04:11:15Z",
  //          "language":"en",
  //          "thumbnail_url":"https://static-cdn.jtvnw.net/previews-ttv/live_user_mika314-{width}x{height}.jpg",
  //          "tag_ids":null
  //       }
  //    ],
  //    "pagination":{
  //       "cursor":"IA"
  //    }
  // }

  auto json = nlohmann::json::parse(strm.str());
  std::vector<std::string> ret;
  for (const auto &user : json["data"])
  {
    std::string userName = user["user_name"];
    std::transform(std::begin(userName), std::end(userName), std::begin(userName), ::tolower);
    ret.push_back(userName);
  }
  cb(ret);
}
