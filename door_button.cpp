#include "door_button.hpp"
#include "cpptoml/cpptoml.h"
#include "room.hpp"
#include "world_desc_error.hpp"

DoorButton::DoorButton(const cpptoml::table &desc)
  : Item(desc), direction{[&desc]() {
      auto &&tomlDirection = desc.get_as<std::string>("direction");
      if (!tomlDirection)
        throw WorldDescError{"Direction e xpected error"};
      auto ret = toDirection(*tomlDirection);
      if (ret == Direction::Last)
        throw WorldDescError{"Invalid direction error: " + *tomlDirection};
      return ret;
    }()}
{
}

std::vector<std::string> DoorButton::getActionsList() const
{
  return {{"push"}};
}

void DoorButton::invoke(const SendMsgCb &sendMsg, Room &room, const std::string &action)
{
  if (action == "push")
  {
    room.setExit(direction, !room.hasExit(direction));
    sendMsg("Door on " + toString(direction) + " is " + (room.hasExit(direction) ? "opening" : "closing") +
            ".");
  }
  else
    sendMsg("Unknown action: " + action);
}
