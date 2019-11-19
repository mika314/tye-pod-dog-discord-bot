#pragma once
#include <string>
#include "pos.hpp"

enum class Direction { North = 0, East = 1, South = 2, West = 3, Last };

std::string toString(Direction);
std::string toShortString(Direction);
Direction toDirection(const std::string&);

constexpr Pos getDelta(Direction value)
{
  constexpr std::array<Pos, static_cast<int>(Direction::Last)> delta = {
    Pos{0, 1, 0}, Pos{1, 0, 0}, Pos{0, -1, 0}, Pos{-1, 0, 0}};
  return delta[static_cast<int>(value)];
}
