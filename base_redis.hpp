#pragma once
#include <string>

class RedisCon;
class BaseRedis
{
public:
  BaseRedis(RedisCon &, const std::string &id);
  virtual ~BaseRedis();
  const char *getId() const;

protected:
  mutable RedisCon *redisCon;

private:
  std::string id;
};