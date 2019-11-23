#pragma once
#include "base_redis.hpp"
#include "direction.hpp"
#include "hero.hpp"
#include "item.hpp"
#include "pos.hpp"
#include <memory>
#include <unordered_set>
#include <vector>

namespace cpptoml
{
  class table;
}

class World;

class Room
{
public:
  Room(const cpptoml::table &desc);
  Room(Room &&) = default;
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
  const HeroesList &getHeroesList() const;
  void describe(std::ostream &, const World &, const Hero &) const;
  bool processCmd(std::ostream &, Hero &, const std::string &cmd);

private:
  Pos pos;
  std::string description;
  std::array<std::string, Direction_META.size()> dirDescription;
  std::array<bool, Direction_META.size()> exits{};
  HeroesList heroesList;
  std::vector<std::unique_ptr<Item>> itemsList;
};
