#pragma once
#include <memory>

namespace Internal
{
  class Bot;
}

class Bot
{
public:
  Bot();
  void run();
  ~Bot();

private:
  std::unique_ptr<Internal::Bot> bot;
};