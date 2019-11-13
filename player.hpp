#pragma once
#include "base_redis.hpp"
#include "hero.hpp"
#include "heroes_list.hpp"
#include "send_msg_cb.hpp"
#include <optional>
#include <string>

class RedisCon;
class World;

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
  std::string getChannelId() const;
  void setChannelId(const std::string &);
  void startTheGame(const SendMsgCb &, World &world, const std::string &channelId);
  void processCmd(const SendMsgCb &, World &world, const std::string &cmd);
};
