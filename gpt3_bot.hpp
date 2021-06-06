#pragma once
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

class Gpt3Bot
{
public:
  Gpt3Bot();
  void addMsg(const std::string &channel, std::string msg);
  std::string getMsg(const std::string &channel) const;

private:
  std::unordered_map<std::string, std::deque<std::string>> msgs;
  std::string token;
};