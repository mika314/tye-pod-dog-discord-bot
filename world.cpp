#include "world.hpp"
#include "cpptoml/cpptoml.h"
#include "hero.hpp"
#include "redis_con.hpp"
#include "world_desc_error.hpp"
#include <iostream>

World::World(RedisCon &redisCon, const std::string &guildId)
  : BaseRedis(redisCon, "world/" + guildId), guildId(guildId)
{
  reloadMap(std::cerr);
}

void World::reloadMap(std::ostream &strm, const std::string &git, const std::string &version)
{
  if (!git.empty())
  {
    redisCon->cmd<int>("HSET %s git %s", getId(), git.c_str());
    redisCon->cmd<int>("HSET %s version %s", getId(), version.c_str());
  }
  auto lGit = redisCon->cmd<std::optional<std::string>>("HGET %s git", getId());
  auto lVersion = redisCon->cmd<std::optional<std::string>>("HGET %s version", getId());
  if (!lGit)
  {
    lGit = "https://github.com/mika314/mikas-world.git";
    lVersion = "dev";
  }
  system(("git clone --depth 1 " + *lGit + " -b " + *lVersion + " world").c_str());
  std::unordered_map<Pos, Room, PosHash> lMap;
  try
  {
    auto &&toml = cpptoml::parse_file("world/world.toml");
    system("rm -rf world");
    auto &&rooms = toml->get_table_array("room");
    if (!rooms)
    {
      strm << "no rooms\n";
      return;
    }
    for (auto &&tomlRoom : *rooms)
    {
      // std::cout << "room\n";
      // pos="0,1,0"
      // description="the room"
      // north="you have mirror"
      // west="a PC with two screens"
      // south="a couch"
      // exits="ns"
      Room room{*tomlRoom};
      const auto pos = room.getPos();
      lMap.emplace(pos, std::move(room));
    }
  }
  catch (const cpptoml::parse_exception &err)
  {
    strm << err.what() << "\n";
    system("rm -rf world");
    return;
  }
  catch (const WorldDescError &err)
  {
    strm << err.what() << "\n";
    return;
  }
  map = std::move(lMap);
  for (auto &hero : getAllHeroes())
    addHeroToRoom(hero);

  strm << "Map is reloaded.\n";
}

Room *World::getRoom(Pos pos)
{
  auto it = map.find(pos);
  if (it == std::end(map))
    return nullptr;
  return &it->second;
}

const Room *World::getRoom(Pos pos) const
{
  auto it = map.find(pos);
  if (it == std::end(map))
    return nullptr;
  return &it->second;
}

void World::describeRoom(std::ostream& strm, const Hero &hero) const
{
  Pos pos{hero.getPos()};
  switch (hero.getFacing())
  {
  case Direction::North: strm << ":arrow_up:\n"; break;
  case Direction::East: strm << ":arrow_right:\n"; break;
  case Direction::South: strm << ":arrow_down:\n"; break;
  case Direction::West: strm << ":arrow_left:\n"; break;
  }
  auto room = getRoom(pos);
  if (!room)
  {
    strm << "You are standing in the void.\n"
            "Your position: "
         << pos.x << "," << pos.y << "," << pos.z << "\n";
    return;
  }
  room->describe(strm, *this, hero);
}

void World::addHeroToRoom(Hero &hero)
{
  auto room = getRoom(hero.getPos());
  if (!room)
  {
    std::cerr << "Room " << hero.getPos().x << "," << hero.getPos().y << "," << hero.getPos().z
              << " does not exist.\n";
    return;
  }
  room->addHero(hero);
}

void World::rmHeroFromRoom(const Hero &hero)
{
  auto room = getRoom(hero.getPos());
  if (!room)
    return;
  room->rmHero(hero);
}

std::vector<Hero> World::getAllHeroes()
{
  std::vector<Hero> ret;
  auto ids = redisCon->cmd<std::vector<std::string>>("KEYS hero/%s/*", guildId.c_str());
  // std::clog << "Heroes in the world:\n";
  for (auto id : ids)
  {
    // std::clog << id << std::endl;
    std::istringstream strm(id);
    std::string tmp;
    std::getline(strm, tmp, '/');
    assert(tmp == "hero");
    std::getline(strm, tmp, '/');
    assert(tmp == guildId);
    std::string memberId;
    std::getline(strm, memberId, '/');
    std::string heroId;
    std::getline(strm, heroId, '/');
    ret.emplace_back(*redisCon, guildId, memberId, heroId);
  }
  return ret;
}

bool World::processCmd(std::ostream &strm, Hero &hero, const std::string &cmd)
{
  auto room = getRoom(hero.getPos());
  if (!room)
    return false;
  return room->processCmd(strm, hero, cmd);
}
