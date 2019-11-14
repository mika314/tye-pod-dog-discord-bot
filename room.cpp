#include "room.hpp"

Pos Room::getPos() const
{
  return pos;
}

void Room::setPos(Pos value)
{
  pos = value;
}

bool Room::hasExit(Direction dir) const
{
  return exits[static_cast<int>(dir)];
}

void Room::setExit(Direction dir, bool value)
{
  exits[static_cast<int>(dir)] = value;
}

std::string Room::getDescription() const
{
  return description;
}

void Room::setDescription(const std::string &value)
{
  description = value;
}

std::string Room::getDescription(Direction dir) const
{
  return dirDescription[static_cast<int>(dir)];
}

void Room::setDescription(Direction dir, const std::string &value)
{
  dirDescription[static_cast<int>(dir)] = value;
}

void Room::addHero(Hero &)
{
  // TODO
}

void Room::rmHero(const Hero &)
{
  // TODO
}