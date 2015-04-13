#pragma once
#include <string>
#include "game.h"
#include "GameBuilder.h"

class GameBuilderDirector{
public:
  GameBuilderDirector();
  void setGameBuilder(GameBuilder * gb);
  Game * getGame();
  void constructGame();
  
private:
  GameBuilder * gameBuilderUsed;
};