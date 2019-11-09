#include "player.hpp"
#include "redis_con.hpp"
#include "gen_uuid.hpp"

Player::Player(RedisCon &redisCon, const std::string &playerId) : BaseRedis(redisCon, playerId) {}

Player::State Player::getState() const
{
  auto state = redisCon->cmd<std::optional<std::string>>("HGET %s state", getId());
  if (!state)
    return State::Null;
  if (*state == "hero name")
    return State::HeroName;
  if (*state == "playing")
    return State::Playing;
  return State::Null;
}

void Player::setState(State state)
{
  switch (state)
  {
  case State::Null: redisCon->cmd<int>("HDEL %s state", getId()); return;
  case State::HeroName:
    redisCon->cmd<int>("HSET %s state %s", getId(), "hero name");
    return;
  case State::Playing:
    redisCon->cmd<int>("HSET %s state %s", getId(), "playing");
    return;
  }
}

HeroesList Player::getHeroesList() const
{
  if (auto heroesList =
        redisCon->cmd<std::optional<std::string>>("HGET %s %s", getId(), "heroes list"))
    return HeroesList(*redisCon, *heroesList);
  else
  {
    auto newHeroesList = "heroes list/" + genUuid();
    redisCon->cmd<int>("HSET %s %s %s", getId(), "heroes list", newHeroesList.c_str());
    return HeroesList{*redisCon, newHeroesList};
  }
}

Hero Player::getActiveHero() const
{
  if (auto activeHero =
        redisCon->cmd<std::optional<std::string>>("HGET %s %s", getId(), "active hero"))
    return Hero(*redisCon, *activeHero);
  else
  {
    auto heroesList = getHeroesList();
    if (heroesList.isEmpty())
      return heroesList.pushBack();
    else
      return heroesList.front();
  }
}

void Player::setActiveHero(Hero hero)
{
  redisCon->cmd<int>("HSET %s %s %s", getId(), "active hero", hero.getId());
}
