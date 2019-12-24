#include "redis_con.hpp"
#include <iostream>

namespace Internal
{
  template <>
  std::string get<std::string>(redisReply *reply)
  {
    if (reply->type != REDIS_REPLY_STRING && reply->type != REDIS_REPLY_STATUS)
    {
      std::cerr << "Unexpected redis reply: " << reply->type << std::endl;
      throw RedisUnexpectedReplyError{};
    }
    return std::string{reply->str, reply->str + reply->len};
  }

  template <>
  std::optional<std::string> get<std::optional<std::string>>(redisReply *reply)
  {
    switch (reply->type)
    {
    default:
      std::cerr << "Unexpected redis reply: " << reply->type << std::endl;
      throw RedisUnexpectedReplyError{};
    case REDIS_REPLY_STRING:
    case REDIS_REPLY_STATUS: return std::string{reply->str, reply->str + reply->len};
    case REDIS_REPLY_NIL: return std::nullopt;
    }
  }

  template <>
  std::vector<std::string> get<std::vector<std::string>>(redisReply *reply)
  {
    switch (reply->type)
    {
    default:
      std::cerr << "Unexpected redis reply: " << reply->type << std::endl;
      throw RedisUnexpectedReplyError{};
    case REDIS_REPLY_ARRAY:
    {
      std::vector<std::string> ret;
      for (auto elem = reply->element; elem != reply->element + reply->elements; ++elem)
      {
        if ((*elem)->type != REDIS_REPLY_STRING)
        {
          std::cerr << "Unexpected redis type in the array: " << reply->type << std::endl;
          throw RedisUnexpectedReplyError{};
        }
        ret.emplace_back((*elem)->str, (*elem)->len);
      }
      return ret;
    }
    }
  }

  template <>
  int get<int>(redisReply *reply)
  {
    if (reply->type != REDIS_REPLY_INTEGER)
    {
      std::cerr << "Unexpected redis reply: " << reply->type << std::endl;
      throw RedisUnexpectedReplyError{};
    }
    return reply->integer;
  }

  template <>
  std::optional<int> get<std::optional<int>>(redisReply *reply)
  {
    switch (reply->type)
    {
    default:
      std::cerr << "Unexpected redis reply: " << reply->type << std::endl;
      throw RedisUnexpectedReplyError{};
    case REDIS_REPLY_INTEGER: return reply->integer;
    case REDIS_REPLY_NIL: return std::nullopt;
    }
  }
} // namespace Internal

RedisCon::RedisCon() : con(redisConnect("127.0.0.1", 6379))
{
  if (!con)
  {
    std::cerr << "Could not allocate redis context\n";
    throw RedisInitError{};
  }

  if (con->err)
  {
    std::cerr << "Error: " << con->errstr << std::endl;
    throw RedisInitError{};
  }
}

RedisCon::~RedisCon()
{
  redisFree(con);
}

void RedisCon::checkError(redisReply *reply)
{
  if (!reply)
  {
    std::cerr << "Error: " << con->errstr << std::endl;
    exit(1);
  }
  if (reply->type == REDIS_REPLY_ERROR)
    std::cerr << "Error: " << std::string{reply->str, reply->str + reply->len} << std::endl;
}
