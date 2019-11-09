#pragma once
#include "base_redis.hpp"
#include "hero.hpp"

class HeroesList : public BaseRedis
{
public:
  HeroesList(RedisCon &, const std::string &id);
  size_t size() const;
  bool isEmpty() const;
  Hero pushBack();
  Hero front() const;
};