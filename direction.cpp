#include "direction.hpp"

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
  switch (value)
  {
  case Direction::North: return "n";
  case Direction::East: return "e";
  case Direction::South: return "s";
  case Direction::West: return "w";
  }
  return "l";
}

Direction toDirection(const std::string &str)
{
  for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
  {
    auto d = static_cast<Direction>(i);
    if (toString(d) == str)
      return d;
  }
  return Direction::Last;
}
