#include "base_redis.hpp"

BaseRedis::BaseRedis(RedisCon &redisCon, const std::string &id) : redisCon(&redisCon), id(id) {}
BaseRedis::~BaseRedis() = default;
const char *BaseRedis::getId() const
{
  return id.c_str();
}