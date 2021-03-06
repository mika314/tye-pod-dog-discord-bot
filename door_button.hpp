#pragma once
#include "item.hpp"
#include "direction.hpp"

class DoorButton : public Item
{
public:
  DoorButton(const cpptoml::table &desc);
  std::vector<std::string> getActionsList() const override;
  bool invoke(std::ostream &, Room &, const std::string &action) override;
private:
  Direction direction;
};