#include "gpt3_bot.hpp"
#include "curl_glob_init.hpp"
#include "read_token.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>

Gpt3Bot::Gpt3Bot() : token(readTokenFile("gpt3_token.dat")) {}

void Gpt3Bot::addMsg(const std::string &channel, std::string msg)
{
  msgs[channel].push_back(msg);
  while (msgs[channel].size() > 5)
    msgs[channel].pop_front();
}

static size_t curlWrite(void *buffer, size_t size, size_t nmemb, void *userp)
{
  ((std::ostringstream *)userp)->write((char *)buffer, size * nmemb);
  return size * nmemb;
}

static size_t read_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
  auto ss = ((std::istringstream *)userp);
  ss->read((char *)buffer, size * nmemb);
  return ss->gcount();
}

std::string Gpt3Bot::getMsg(const std::string &channel) const
{
  curlGlobInit();

  std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> tmp(curl_easy_init(), curl_easy_cleanup);
  if (!tmp)
    throw std::runtime_error("Failed to init curl");

  auto handle = tmp.get();

  std::ostringstream strm;

  auto jsonOut = R"({
    "prompt" : "",
    "temperature" : 0.9,
    "max_tokens" : 150,
    "top_p" : 1,
    "frequency_penalty" : 0,
    "presence_penalty" : 0.6,
    "stop" : [ "\n", "Tye-Pod Dog:" ]
  })"_json;

  std::ostringstream msgsStrm;
  msgsStrm << R"(TheToeBeanLord: some.... expressions XD
Tye-Pod Dog: THE BOI
Ms. Patatas: My back hurts x o x
Tye-Pod Dog: Same
wanderin wombi: Speaking of god, if I sleep next to jesus then dont wake up and say no homo does he lose his religious power? Tye-Pod Dog
wanderin wombi: I swear I cant have a normal conversation without my brain coming up with shit like this
Tye-Pod Dog: WAT
Tye-Pod Dog: LMAO I AM SO CONFUSED
wanderin wombi: Thats how the wombi do
wanderin wombi: 0 context at most times
Tye-Pod Dog: Amg lmao
Ms. Patatas: I am alive x u x sorta
Ms. Patatas: Tye-Pod Dog  heeey ewe
Tye-Pod Dog: eyyy welcome to being alive
Ms. Patatas: I missed you guys ; 3 ;
-Mohjii's Waifu🌸: wb @Ms. Patatas 
Ms. Patatas: -Mohjii's Waifu🌸  thank you owo
@Ms. Patatas: owo
-Mohjii's Waifu🌸: UwU
Ms. Patatas: Lol
Ms. Patatas: And now I am in pain x o x dang stomach pains
Tye-Pod Dog: Srry I hkadda sleep qww
Tye-Pod Dog: PAadaaain
Morbid: Tye-Pod Dog MOhjiis_mating_call.mp4
Tye-Pod Dog: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Morbid: XD gladd you like it Morbid Tye-Pod Dog
Tye-Pod Dog: FUCKIN LOVE IT
)";
  auto it = msgs.find(channel);
  if (it != std::end(msgs))
    for (const auto &msg : it->second)
      msgsStrm << msg << std::endl;
  msgsStrm << "Tye-Pod Dog: ";
  jsonOut["prompt"] = msgsStrm.str();
  std::istringstream jsonStrm(jsonOut.dump());

  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, curlWrite);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &strm);
  curl_easy_setopt(handle, CURLOPT_POST, 1L);
  curl_easy_setopt(handle, CURLOPT_READFUNCTION, read_callback);
  curl_easy_setopt(handle, CURLOPT_READDATA, &jsonStrm);

  std::string url;
  curl_easy_setopt(handle, CURLOPT_URL, "https://api.openai.com/v1/engines/davinci/completions");

  const auto tkn = "Authorization: Bearer " + token;
  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "Content-Type: application/json");
  chunk = curl_slist_append(chunk, tkn.c_str());
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

  auto json = nlohmann::json::parse(strm.str());
  for (auto &choice : json["choices"])
    return choice["text"].get<std::string>();

  return "";
}
