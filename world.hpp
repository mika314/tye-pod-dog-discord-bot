#pragma once
#include "base_redis.hpp"
#include "pos.hpp"
#include "room.hpp"
#include "send_msg_cb.hpp"
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
  void reloadMap(const SendMsgCb &, const std::string &git = "", const std::string &version = "");
  std::string describeRoom(const Hero &) const;
  void addHeroToRoom(Hero &);
  void rmHeroFromRoom(const Hero &);
  std::vector<Hero> getAllHeroes();

private:
  std::unordered_map<Pos, Room, PosHash> map;
  std::string guildId;
};
