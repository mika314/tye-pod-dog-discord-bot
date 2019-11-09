#pragma once
#include "base_redis.hpp"

class Hero : public BaseRedis
{
public:
  Hero(RedisCon &, const std::string &id);
  std::string getName() const;
  void setName(const std::string &);
  int getX() const;
  int incX(int) const;
  void setX(int);
  int getY() const;
  int incY(int) const;
  void setY(int);
  int getZ() const;
  int incZ(int) const;
  void setZ(int);
};