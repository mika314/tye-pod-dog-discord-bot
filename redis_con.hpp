#pragma once
#include <hiredis/hiredis.h>
#include <string>
#include <utility>
#include <optional>
#include <vector>

enum class RedisInitError;
enum class RedisUnexpectedReplyError;

namespace Internal
{
  template <typename Return>
  Return get(redisReply *);

  template <>
  std::string get<std::string>(redisReply *);

  template <>
  std::optional<std::string> get<std::optional<std::string>>(redisReply *);

  template <>
  std::vector<std::string> get<std::vector<std::string>>(redisReply *);

  template <>
  int get<int>(redisReply *);

  template <>
  std::optional<int> get<std::optional<int>>(redisReply *);
} // namespace Internal

class RedisCon
{
public:
  RedisCon();
  ~RedisCon();
  redisContext *con{nullptr};

  template <typename Return, typename... Args>
  Return cmd(Args &&... args)
  {
    auto reply = static_cast<redisReply *>(::redisCommand(con, std::forward<Args>(args)...));
    checkError(reply);
    Return ret = Internal::get<Return>(reply);
    freeReplyObject(reply);
    return ret;
  }

private:
  void checkError(redisReply *reply);
};