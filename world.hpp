#pragma once
#include "base_redis.hpp"
#include "pos.hpp"
#include "room.hpp"
#include <ostream>
#include <string>
#include <unordered_map>

class Bot;
class Hero;

class World : public BaseRedis
{
public:
  World(RedisCon &, const std::string &guilId);
  Room *getRoom(Pos);
  const Room *getRoom(Pos) const;
  void reloadMap(std::ostream &, const std::string &git = "", const std::string &version = "");
  void describeRoom(std::ostream &, const Hero &hero) const;
  void addHeroToRoom(Hero &);
  void rmHeroFromRoom(const Hero &);
  std::vector<Hero> getAllHeroes();

private:
  std::unordered_map<Pos, Room, PosHash> map;
  std::string guildId;
};
