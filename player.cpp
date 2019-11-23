#include "player.hpp"
#include "gen_uuid.hpp"
#include "redis_con.hpp"
#include "world.hpp"
#include <cstring>

Player::Player(RedisCon &redisCon, const std::string &guildId, const std::string &memberId)
  : BaseRedis(redisCon, "player/" + guildId + "/" + memberId), guildId(guildId), memberId(memberId)
{
}

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

int Player::getHeroesCount() const
{
  return redisCon->cmd<int>("HINCRBY %s %s 0", getId(), "heroes count");
}

Hero Player::addNewHero()
{
  auto newHero = redisCon->cmd<int>("HINCRBY %s %s 1", getId(), "heroes count") - 1;
  return Hero{*redisCon, guildId, memberId, std::to_string(newHero)};
}

Hero Player::getHero(int idx)
{
  return Hero{*redisCon, guildId, memberId, std::to_string(idx)};
}

Hero Player::getActiveHero()
{
  if (auto activeHero =
        redisCon->cmd<std::optional<std::string>>("HGET %s %s", getId(), "active hero"))
    return Hero(*redisCon, guildId, memberId, *activeHero);
  else
  {
    if (getHeroesCount() == 0)
      return addNewHero();
    else
      return getHero(0);
  }
}

void Player::setActiveHero(Hero hero)
{
  redisCon->cmd<int>("HSET %s %s %s", getId(), "active hero", hero.getHeroId());
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

void Player::startTheGame(std::ostream &strm, World &world, const std::string &channelId)
{
  setChannelId(channelId);
  switch (getHeroesCount())
  {
  case 0:
    strm << "What is your name?";
    setState(Player::State::HeroName);
    break;
  case 1:
  {
    auto hero = getActiveHero();
    strm << "You are " + hero.getName() << "\n";
    strm << "Type \"help\" if you need to learn how to play.\n";
    world.describeRoom(strm, hero);
    setState(Player::State::Playing);
    break;
  }
  default:
  {
    auto hero = getActiveHero();
    strm << "// TODO handle more than one hero\n";
    strm << "You are " << hero.getName() << "\n";
    strm << "Type \"help\" if you need to learn how to play.\n";
    world.describeRoom(strm, hero);
    setState(Player::State::Playing);
    break;
  }
  }
}

void Player::processCmd(std::ostream &strm, World &world, const std::string &cmd)
{
  if (cmd == "quit" || cmd == "q")
  {
    strm << "It was fun to play with you.\n";
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
    strm << "Your name is " << name << "\n";
    strm << "Type \"help\" if you need to learn how to play.\n";
    world.describeRoom(strm, hero);
    setState(Player::State::Playing);
    return;
  }
  case Player::State::Playing:
  {
    auto hero = getActiveHero();
    auto room = world.getRoom(hero.getPos());
    if (cmd == "help" || cmd == "h")
    {
      strm << R"(# Help
* _describe_ or _desc_ - describe place where hero is standing
* _respawn_ or _rspwn_ - respawn in the origin on the world
* _reload_ - reload map from git repository
* _quit_ or _q_ - quit the game
* _change name_ New Name or _chname_ New Name - change hero's name
* _look at_ item - look at the item

## Walking
* _north_ or _n_ - walk north
* _east_ or _e_ - walk east
* _south_ or _s_ - walk south
* _west_ or _w_ - walk west

* _help_ or _h_ - this help)";
    }
    else if (cmd == "reload")
      world.reloadMap(strm);
    else if (cmd == "respawn" || cmd == "rspwn")
    {
      hero.respawn();
      world.describeRoom(strm, hero);
    }
    else if ([&]() {
               for (auto d: Direction_META)
               {
                 if ((cmd == toShortString(d) || cmd == toString(d)))
                 {
                   if (!room || room->hasExit(d))
                   {
                     hero.walk(d);
                     world.describeRoom(strm, hero);
                   }
                   else
                     strm << "You cannot walk this way...\n";
                   return true;
                 }
               }
               return false;
             }())
    {
    }
    else if (cmd == "desc" || cmd == "describe")
      world.describeRoom(strm, hero);
    else if (cmd.find("change name ") == 0 || cmd.find("chname ") == 0)
    {
      const auto newName = [&cmd]() {
        auto p = cmd.find("change name ");
        if (p == 0)
          return cmd.substr(strlen("change name "));
        return cmd.substr(strlen("chname "));
      }();
      hero.setName(newName);
      strm << "Your new name is " << newName << "\n";
    }
    else if (world.processCmd(strm, hero, cmd))
    {
    }
    else
      strm << "Unknown command\n";
  }
  }
}
