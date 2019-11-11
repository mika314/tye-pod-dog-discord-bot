#pragma once
#include "base_redis.hpp"
#include "direction.hpp"
#include "pos.hpp"

class Hero : public BaseRedis
{
public:
  Hero(RedisCon &, const std::string &id);
  std::string getName() const;
  void setName(const std::string &);
  int getX() const;
  int incX(int = 1) const;
  void setX(int);
  int getY() const;
  int incY(int = 1) const;
  void setY(int);
  int getZ() const;
  int incZ(int = 1) const;
  void setZ(int);
  Pos getPos() const;
  void setPos(Pos);
  Direction getFacing() const;
  void setFacing(Direction);
  void respawn();
  void walk(Direction);
};