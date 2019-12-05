#pragma once
#include "enum_meta.hpp"
#include "pos.hpp"
#include <string>

ENUM(Direction, North, East, South, West, Unknown);

std::string toString(Direction);
std::string toShortString(Direction);
Direction toDirection(const std::string &);

constexpr Pos getDelta(Direction value)
{
  constexpr std::array<Pos, Direction_META.size()> delta = {
    Pos{0, 1, 0}, Pos{1, 0, 0}, Pos{0, -1, 0}, Pos{-1, 0, 0}};
  return delta[static_cast<int>(value)];
}
