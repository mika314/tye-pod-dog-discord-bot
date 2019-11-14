#include "player.hpp"
#include "gen_uuid.hpp"
#include "redis_con.hpp"
#include "world.hpp"
#include <cstring>

Player::Player(RedisCon &redisCon, const std::string &playerId) : BaseRedis(redisCon, playerId) {}

Player::State Player::getState() const
{
  auto state = redisCon->cmd<std::optional<std::string>>("HGET %s state", getId());
  if (!state)
    return State::Null;
  if (*state == "hero name")
    return State::HeroName;
  if (*state == "playing")
    return State::Playing;
  return State::Null;
}

void Player::setState(State state)
{
  switch (state)
  {
  case State::Null: redisCon->cmd<int>("HDEL %s state", getId()); return;
  case State::HeroName: redisCon->cmd<int>("HSET %s state %s", getId(), "hero name"); return;
  case State::Playing: redisCon->cmd<int>("HSET %s state %s", getId(), "playing"); return;
  }
}

HeroesList Player::getHeroesList() const
{
  if (auto heroesList =
        redisCon->cmd<std::optional<std::string>>("HGET %s %s", getId(), "heroes list"))
    return HeroesList(*redisCon, *heroesList);
  else
  {
    auto newHeroesList = "heroes list/" + genUuid();
    redisCon->cmd<int>("HSET %s %s %s", getId(), "heroes list", newHeroesList.c_str());
    return HeroesList{*redisCon, newHeroesList};
  }
}

Hero Player::getActiveHero() const
{
  if (auto activeHero =
        redisCon->cmd<std::optional<std::string>>("HGET %s %s", getId(), "active hero"))
    return Hero(*redisCon, *activeHero);
  else
  {
    auto heroesList = getHeroesList();
    if (heroesList.isEmpty())
      return heroesList.pushBack();
    else
      return heroesList.front();
  }
}

void Player::setActiveHero(Hero hero)
{
  redisCon->cmd<int>("HSET %s %s %s", getId(), "active hero", hero.getId());
}

std::string Player::getChannelId() const
{
  const auto ret = redisCon->cmd<std::optional<std::string>>("HGET %s %s", getId(), "channel ID");
  return ret ? *ret : "";
}

void Player::setChannelId(const std::string &value)
{
  redisCon->cmd<int>("HSET %s %s %s", getId(), "channel ID", value.c_str());
}

void Player::startTheGame(const SendMsgCb &sendMsg, World &world, const std::string &channelId)
{
  setChannelId(channelId);
  switch (getHeroesList().size())
  {
  case 0:
    sendMsg("What is your name?");
    setState(Player::State::HeroName);
    break;
  case 1:
  {
    auto hero = getActiveHero();
    sendMsg("You are " + hero.getName());
    sendMsg("Type \"help\" if you need to learn how to play.");
    sendMsg(world.describeRoom(hero));
    setState(Player::State::Playing);
    break;
  }
  default:
  {
    auto hero = getActiveHero();
    sendMsg("// TODO handle more than one hero");
    sendMsg("You are " + hero.getName());
    sendMsg("Type \"help\" if you need to learn how to play.");
    sendMsg(world.describeRoom(hero));
    setState(Player::State::Playing);
    break;
  }
  }
}

void Player::processCmd(const SendMsgCb &sendMsg, World &world, const std::string &cmd)
{
  if (cmd == "quit" || cmd == "q")
  {
    sendMsg("It was fun to play with you.");
    setState(Player::State::Null);
    return;
  }
  switch (getState())
  {
  default:
  case Player::State::Null: break;
  case Player::State::HeroName:
  {
    auto name = cmd;
    auto hero = getActiveHero();
    hero.setName(name);
    sendMsg("Your name is " + name);
    sendMsg("Type \"help\" if you need to learn how to play.");
    sendMsg(world.describeRoom(hero));
    setState(Player::State::Playing);
    return;
  }
  case Player::State::Playing:
  {
    auto hero = getActiveHero();
    auto room = world.getRoom(hero.getPos());
    if (cmd == "help" || cmd == "h")
    {
      sendMsg(R"(# Help
* _describe_ or _desc_ - describe place where hero is standing
* _respawn_ or _rspwn_ - respawn in the origin on the world
* _reload_ - reload map from git repository
* _quit_ or _q_ - quit the game
* _change name_ or _chname_ - change hero's name

## Walking
* _north_ or _n_ - walk north
* _east_ or _e_ - walk east
* _south_ or _s_ - walk south
* _west_ or _w_ - walk west

* _help_ or _h_ - this help)");
    }
    else if (cmd == "reload")
      world.reloadMap(sendMsg);
    else if (cmd == "respawn" || cmd == "rspwn")
    {
      hero.respawn();
      sendMsg(world.describeRoom(hero));
    }
    else if ([&]() {
               for (int i = 0; i < static_cast<int>(Direction::Last); ++i)
               {
                 auto d = static_cast<Direction>(i);
                 if ((cmd == toShortString(d) || cmd == toString(d)))
                 {
                   if (!room || room->hasExit(d))
                   {
                     hero.walk(d);
                     sendMsg(world.describeRoom(hero));
                   }
                   else
                     sendMsg("You cannot walk this way...");
                   return true;
                 }
               }
               return false;
             }())
    {
    }
    else if (cmd == "desc" || cmd == "describe")
      sendMsg(world.describeRoom(hero));
    else if (cmd.find("change name ") == 0 || cmd.find("chname ") == 0)
    {
      const auto newName = [&cmd]() {
        auto p = cmd.find("change name ");
        if (p == 0)
          return cmd.substr(strlen("change name "));
        return cmd.substr(strlen("chname "));
      }();
      hero.setName(newName);
      sendMsg("Your new name is " + newName);
    }
  }
  }
}