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
}
