#pragma once
#include "base_redis.hpp"
#include "hero.hpp"
#include "heroes_list.hpp"
#include <optional>
#include <string>

class RedisCon;

class Player : public BaseRedis
{
public:
  enum class State { Null, HeroName, Playing };
  Player(RedisCon &, const std::string &playerId);
  State getState() const;
  void setState(State);
  HeroesList getHeroesList() const;
  Hero getActiveHero() const;
  void setActiveHero(Hero);
};
