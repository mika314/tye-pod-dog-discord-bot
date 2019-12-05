#include "item.hpp"
#include "cpptoml/cpptoml.h"
#include "world_desc_error.hpp"

Item::Item(const cpptoml::table &desc)
  : name{[&desc]() {
      if (auto &&tomlName = desc.get_as<std::string>("name"))
        return *tomlName;
      throw WorldDescError{"name is expected"};
    }()}
{
}

const std::string &Item::getName() const
{
  return name;
}
