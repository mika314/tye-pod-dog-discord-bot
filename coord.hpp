#pragma once
#include <functional>

struct Coord
{
  int x;
  int y;
  int z;
  bool operator==(const Coord &other) const { return x == other.x && y == other.y && z == other.z; }
};

struct CoordHash
{
  size_t operator()(const Coord &p) const
  {
    size_t res = 17;
    res = res * 31 + std::hash<int>{}(p.x);
    res = res * 31 + std::hash<int>{}(p.y);
    res = res * 31 + std::hash<int>{}(p.z);
    return res;
  }
};
