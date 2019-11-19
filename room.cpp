#include "room.hpp"
#include "cpptoml/cpptoml.h"
#include "door_button.hpp"
#include "pos.hpp"
#include "world_desc_error.hpp"
#include <iostream>

Room::Room(const cpptoml::table &tomlRoom)
  : pos{[&tomlRoom]() {
      auto &&tomlPos = tomlRoom.get_as<std::string>("pos");
      if (!tomlPos)
        throw WorldDescError("Room does not have pos specified");
      Pos ret;
      // std::cout << "pos: " << *tomlPos << std::endl;
      std::istringstream strm(*tomlPos);
      char ch;
      strm >> ret.x >> ch >> ret.y >> ch >> ret.z;
      return ret;
    }()},

    description{[&tomlRoom]() {
      if (auto &&desc = tomlRoom.get_as<std::string>("description"))
        return *desc;
    }()},

    dirDescription{[&tomlRoom]() {
      std::array<std::string, static_cast<int>(Direction::Last)> ret;
      for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
      {
        auto d = static_cast<Direction>(i);
        if (auto &&desc = tomlRoom.get_as<std::string>(toString(d)))
          ret[i] = *desc;
      }
      return ret;
    }()},

    exits{[&tomlRoom]() {
      std::array<bool, static_cast<int>(Direction::Last)> ret{};
      if (auto &&exits = tomlRoom.get_as<std::string>("exits"))
      {
        // std::cout << "exits: " << *exits << std::endl;
        for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
        {
          auto d = static_cast<Direction>(i);
          if (exits->find(toShortString(d)) != std::string::npos)
            ret[i] = true;
        }
      }
      else
        throw WorldDescError{"Exists for the room are not specified."};
      return ret;
    }()},

    itemsList{[&tomlRoom]() {
      std::vector<std::unique_ptr<Item>> ret;
      if (auto &&items = tomlRoom.get_table_array("items"))
      {
        for (auto &&tomlItem : *items)
        {
          auto &&class_ = tomlItem->get_as<std::string>("class");
          if (!class_)
            throw WorldDescError{"class is expected"};
          if (*class_ == "door button")
            ret.emplace_back(std::make_unique<DoorButton>(*tomlItem));
          else
            throw WorldDescError{"unknown class: " + *class_};
        }
      }
      return ret;
    }()}
{
}

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

void Room::addHero(Hero &hero)
{
  // std::clog << __func__ << ": " << hero.getName() << " " << pos.x << "," << pos.y << std::endl;
  heroesList.insert(hero);
}

void Room::rmHero(const Hero &hero)
{
  heroesList.erase(hero);
}

const HeroesList &Room::getHeroesList() const
{
  return heroesList;
}
