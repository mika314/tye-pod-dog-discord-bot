#pragma once
#include "base_redis.hpp"
#include "direction.hpp"
#include "pos.hpp"
#include <unordered_set>

class Hero : public BaseRedis
{
public:
  Hero(RedisCon &,
       const std::string &guildId,
       const std::string &memberId,
       const std::string &heroId);
  std::string getName() const;
  void setName(const std::string &);
  int getX() const;
  int incX(int = 1) const;
  int getY() const;
  int incY(int = 1) const;
  int getZ() const;
  int incZ(int = 1) const;
  Pos getPos() const;
  void setPos(Pos);
  Direction getFacing() const;
  void setFacing(Direction);
  void respawn();
  void walk(Direction);
  const char *getHeroId() const;
  bool operator==(const Hero&) const;

private:
  void setX(int);
  void setY(int);
  void setZ(int);
  std::string guildId;
  std::string memberId;
  std::string heroId;
};

struct HeroHash
{
  size_t operator()(const Hero &hero) const { return std::hash<const char *>{}(hero.getId()); }
};

using HeroesList = std::unordered_set<Hero, HeroHash>;
