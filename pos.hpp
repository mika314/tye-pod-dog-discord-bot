#pragma once
#include <functional>

struct Pos
{
  int x;
  int y;
  int z;
  constexpr bool operator==(const Pos &other) const
  {
    return x == other.x && y == other.y && z == other.z;
  }
  constexpr Pos operator+(Pos other) const { return Pos{x + other.x, y + other.y, z + other.z}; }
};

struct PosHash
{
  size_t operator()(const Pos &p) const
  {
    size_t res = 17;
    res = res * 31 + std::hash<int>{}(p.x);
    res = res * 31 + std::hash<int>{}(p.y);
    res = res * 31 + std::hash<int>{}(p.z);
    return res;
  }
};
