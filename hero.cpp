#include "hero.hpp"
#include "redis_con.hpp"
#include <sstream>

Hero::Hero(RedisCon &redisCon,
           const std::string &guildId,
           const std::string &memberId,
           const std::string &heroId)
  : BaseRedis(redisCon, "hero/" + guildId + "/" + memberId + "/" + heroId),
    guildId(guildId),
    memberId(memberId),
    heroId(heroId)
{
}

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
  return redisCon->cmd<int>("HINCRBY %s y 0", getId());
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

Direction Hero::getFacing() const
{
  std::optional<std::string> value =
    redisCon->cmd<std::optional<std::string>>("HGET %s facing", getId());
  if (!value || *value == "north")
    return Direction::North;
  else if (*value == "east")
    return Direction::East;
  else if (*value == "south")
    return Direction::South;
  else if (*value == "west")
    return Direction::West;
}

void Hero::setFacing(Direction value)
{
  switch (value)
  {
  case Direction::North: redisCon->cmd<int>("HSET %s facing %s", getId(), "north"); break;
  case Direction::East: redisCon->cmd<int>("HSET %s facing %s", getId(), "east"); break;
  case Direction::South: redisCon->cmd<int>("HSET %s facing %s", getId(), "south"); break;
  case Direction::West: redisCon->cmd<int>("HSET %s facing %s", getId(), "west"); break;
  }
}

void Hero::respawn()
{
  setPos(Pos{0, 0, 0});
  setFacing(Direction::North);
}

Pos Hero::getPos() const
{
  return Pos{getX(), getY(), getZ()};
}

void Hero::setPos(Pos value)
{
  setX(value.x);
  setY(value.y);
  setZ(value.z);
}

void Hero::walk(Direction value)
{
  setFacing(value);
  incX(getDelta(value).x);
  incY(getDelta(value).y);
  incZ(getDelta(value).z);
}

const char *Hero::getHeroId() const
{
  return heroId.c_str();
}
