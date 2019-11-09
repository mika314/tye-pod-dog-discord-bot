#include "hero.hpp"
#include "redis_con.hpp"
#include <sstream>

Hero::Hero(RedisCon &redisCon, const std::string &id) : BaseRedis(redisCon, id) {}

std::string Hero::getName() const
{
  return redisCon->cmd<std::string>("HGET %s name", getId());
}

void Hero::setName(const std::string &value)
{
  redisCon->cmd<int>("HSET %s name %s", getId(), value.c_str());
}

int Hero::getX() const
{
  return redisCon->cmd<int>("HINCRBY %s x 0", getId());
}

int Hero::incX(int value) const
{
  std::ostringstream strm;
  strm << value;
  return redisCon->cmd<int>("HINCRBY %s x %s", getId(), strm.str().c_str());
}

void Hero::setX(int value)
{
  std::ostringstream strm;
  strm << value;
  redisCon->cmd<int>("HSET %s x %s", getId(), strm.str().c_str());
}

int Hero::getY() const
{
  return redisCon->cmd<int>("HINCRBY %s x 0", getId());
}

int Hero::incY(int value) const
{
  std::ostringstream strm;
  strm << value;
  return redisCon->cmd<int>("HINCRBY %s y %s", getId(), strm.str().c_str());
}

void Hero::setY(int value)
{
  std::ostringstream strm;
  strm << value;
  redisCon->cmd<int>("HSET %s y %s", getId(), strm.str().c_str());
}

int Hero::getZ() const
{
  return redisCon->cmd<int>("HINCRBY %s z 0", getId());
}

int Hero::incZ(int value) const
{
  std::ostringstream strm;
  strm << value;
  return redisCon->cmd<int>("HINCRBY %s z %s", getId(), strm.str().c_str());
}

void Hero::setZ(int value)
{
  std::ostringstream strm;
  strm << value;
  redisCon->cmd<int>("HSET %s y %s", getId(), strm.str().c_str());
}
