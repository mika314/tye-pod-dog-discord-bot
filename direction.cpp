#include "direction.hpp"
#include <algorithm>

std::string toString(Direction value)
{
  switch (value)
  {
  case Direction::North: return "north";
  case Direction::East: return "east";
  case Direction::South: return "south";
  case Direction::West: return "west";
  }
  return "last";
}

std::string toShortString(Direction value)
{
  return toString(value).substr(0, 1);
}

Direction toDirection(const std::string &str)
{
  for (auto d : Direction_META)
    if (toString(d) == str)
      return d;
  return Direction::Unknown;
}
