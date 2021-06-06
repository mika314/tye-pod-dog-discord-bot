#include "curl_glob_init.hpp"
#include <curl/curl.h>
#include <stdexcept>

struct CurlGlobInit
{
  CurlGlobInit()
  {
    if (curl_global_init(CURL_GLOBAL_ALL))
      throw std::runtime_error("Unable to curl_global_init");
  }
  ~CurlGlobInit() { curl_global_cleanup(); }
};

auto curlGlobInit() -> void
{
  static CurlGlobInit ret;
}
