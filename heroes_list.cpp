#include "heroes_list.hpp"
#include "gen_uuid.hpp"
#include "redis_con.hpp"

HeroesList::HeroesList(RedisCon &redisCon, const std::string &id) : BaseRedis(redisCon, id) {}

size_t HeroesList::size() const
{
  return redisCon->cmd<int>("LLEN %s", getId());
}

bool HeroesList::isEmpty() const
{
  return redisCon->cmd<int>("LLEN %s", getId()) == 0;
}

Hero HeroesList::pushBack()
{
  auto newHero = "hero/" + genUuid();
  redisCon->cmd<int>("RPUSH %s %s", getId(), newHero.c_str());
  return Hero{*redisCon, newHero};
}

Hero HeroesList::front() const
{
  return Hero{*redisCon, redisCon->cmd<std::string>("LINDEX %s 0", getId())};
}
