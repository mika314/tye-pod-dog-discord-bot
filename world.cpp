#include "world.hpp"
#include "cpptoml/cpptoml.h"
#include "hero.hpp"
#include "redis_con.hpp"
#include <iostream>

World::World(RedisCon &redisCon, const std::string &guildId)
  : BaseRedis(redisCon, "world/" + guildId), guildId(guildId)
{
  reloadMap([](const std::string &errMsg) { std::cerr << errMsg; });
}

void World::reloadMap(const SendMsgCb &sendMsg, const std::string &git, const std::string &version)
{
  std::ostringstream errStrm;
  if (!git.empty())
  {
    redisCon->cmd<int>("HSET %s git %s", getId(), git.c_str());
    redisCon->cmd<int>("HSET %s version %s", getId(), version.c_str());
  }
  auto lGit = redisCon->cmd<std::optional<std::string>>("HGET %s git", getId());
  auto lVersion = redisCon->cmd<std::optional<std::string>>("HGET %s version", getId());
  if (!lGit)
  {
    lGit = "https://github.com/mika314/test-world.git";
    lVersion = "master";
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
      errStrm << "no rooms\n";
    }
    for (auto &&tomlRoom : *rooms)
    {
      std::cout << "room\n";
      // pos="0,1,0"
      // description="the room"
      // north="you have mirror"
      // west="a PC with two screens"
      // south="a couch"
      // exits="ns"
      Room room;
      if (auto &&tomlPos = tomlRoom->get_as<std::string>("pos"))
      {
        std::cout << "pos: " << *tomlPos << std::endl;
        std::istringstream strm(*tomlPos);
        Pos pos;
        char ch;
        strm >> pos.x >> ch >> pos.y >> ch >> pos.z;
        room.setPos(pos);
      }
      else
      {
        errStrm << "Room does not have pos specified\n";
        break;
      }

      if (auto &&desc = tomlRoom->get_as<std::string>("description"))
        room.setDescription(*desc);

      for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
      {
        auto d = static_cast<Direction>(i);
        if (auto &&desc = tomlRoom->get_as<std::string>(toString(d)))
          room.setDescription(d, *desc);
      }
      if (auto &&exits = tomlRoom->get_as<std::string>("exits"))
      {
        std::cout << "exits: " << *exits << std::endl;
        for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
        {
          auto d = static_cast<Direction>(i);
          if (exits->find(toShortString(d)) != std::string::npos)
            room.setExit(d, true);
        }
      }
      else
      {
        errStrm << "Exists for the room are not specified.\n";
        break;
      }

      lMap.emplace(room.getPos(), room);
    }
  }
  catch (const cpptoml::parse_exception &err)
  {
    errStrm << err.what() << std::endl;
    system("rm -rf world");
  }
  if (!errStrm.str().empty())
  {
    sendMsg(errStrm.str());
    return;
  }

  sendMsg("Map is reloaded.");
  map = lMap;
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

std::string World::describeRoom(const Hero &hero) const
{
  Pos pos{hero.getPos()};
  std::ostringstream strm;
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
         << pos.x << "," << pos.y << "," << pos.z;
    return strm.str();
  }
  strm << "You are standing in " << room->getDescription() << ".\n";
  std::array<const char *, static_cast<int>(Direction::Last)> relativeDirections = {
    "On front of you", "On right side", "Behind", "On left side"};
  auto facing = hero.getFacing();
  for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
  {
    auto desc = room->getDescription(facing);
    if (!desc.empty())
      strm << relativeDirections[i] << " " << desc << ".\n";
    facing =
      static_cast<Direction>((static_cast<int>(facing) + 1) % static_cast<int>(Direction::Last));
  }
  for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
  {
    auto d = static_cast<Direction>(i);
    if (room->hasExit(d))
    {
      auto newRoom = getRoom(pos + getDelta(d));
      strm << "You can go " << toString(d) << " to "
           << (newRoom ? newRoom->getDescription() : "the void") << ".\n";
    }
  }
  return strm.str();
}

void World::addHeroToRoom(Hero &hero)
{
  auto room = getRoom(hero.getPos());
  if (!room)
    return;
  room->addHero(hero);
}

void World::rmHeroFromRoom(const Hero &hero)
{
  auto room = getRoom(hero.getPos());
  if (!room)
    return;
  room->rmHero(hero);
}
