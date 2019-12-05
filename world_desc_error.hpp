#pragma once
#include <stdexcept>
#include <string>

class WorldDescError : public std::runtime_error
{
public:
  WorldDescError(const std::string &str) : std::runtime_error(str) {}
};
