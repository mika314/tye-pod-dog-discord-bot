#pragma once
#include "base_redis.hpp"
#include "hero.hpp"
#include "send_msg_cb.hpp"
#include <optional>
#include <string>

class RedisCon;
class World;

class Player : public BaseRedis
{
public:
  enum class State { Null, HeroName, Playing };
  Player(RedisCon &, const std::string &guildId, const std::string &memberId);
  State getState() const;
  void setState(State);
  int getHeroesCount() const;
  Hero addNewHero();
  Hero getHero(int idx);
  Hero getActiveHero();
  void setActiveHero(Hero);
  std::string getChannelId() const;
  void setChannelId(const std::string &);
  void startTheGame(const SendMsgCb &, World &world, const std::string &channelId);
  void processCmd(const SendMsgCb &, World &world, const std::string &cmd);

private:
  std::string guildId;
  std::string memberId;
};
