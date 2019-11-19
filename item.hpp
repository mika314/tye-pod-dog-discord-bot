#pragma once
#include "send_msg_cb.hpp"
#include <string>
#include <vector>

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
  virtual void invoke(const SendMsgCb &, Room &, const std::string &action) = 0;

private:
  std::string name;
};
