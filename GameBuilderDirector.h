#pragma once
#include <string>
#include "game.h"
#include "GameBuilder.h"

/*
Class GameBuilderDirector: Used to control and direct objects implementing the Build pattern via the GameBuilder class
*/
class GameBuilderDirector{
public:
  GameBuilderDirector();
  void setGameBuilder(GameBuilder * gb);
  Game * getGame();
  void constructGame();
  
private:
  GameBuilder * gameBuilderUsed;
};