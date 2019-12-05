#pragma once
#include <string>
#include <vector>
#include <ostream>

namespace cpptoml
{
  class table;
};

class Room;

class Item
{
public:
  Item(const cpptoml::table &desc);
  virtual ~Item() = default;
  const std::string &getName() const;
  virtual std::vector<std::string> getActionsList() const = 0;
  virtual bool invoke(std::ostream &, Room &, const std::string &action) = 0;

private:
  std::string name;
};
