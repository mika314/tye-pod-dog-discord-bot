#pragma once
#include "base_redis.hpp"
#include "coord.hpp"
#include "room.hpp"
#include <unordered_map>

class World
{
public:
  World();
  Room *getRoom(Coord);

private:
  std::unordered_map<Coord, Room, CoordHash> map;
};
