#pragma once
#include "base_redis.hpp"
#include "pos.hpp"
#include "direction.hpp"

class Hero;

class Room
{
public:
  Pos getPos() const;
  void setPos(Pos);
  bool hasExit(Direction) const;
  void setExit(Direction, bool);
  std::string getDescription() const;
  void setDescription(const std::string &);
  std::string getDescription(Direction) const;
  void setDescription(Direction, const std::string &);
  void addHero(Hero &);
  void rmHero(const Hero &);

private:
  Pos pos;
  std::string description;
  std::array<std::string, static_cast<int>(Direction::Last)> dirDescription;
  std::array<bool, static_cast<int>(Direction::Last)> exits{};
};