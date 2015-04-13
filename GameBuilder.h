#pragma once
#include "game.h"

class GameBuilder{
  //1) current state of the map (i.e. map + armies on countries + ownership of countries)
  //2) Player state (number of players, cards held by each, strategy of each comp player)
  //3) Current state of the game engine (which player's turn/phase)
public:
  virtual void buildMap() = 0;
  virtual void buildPlayers() = 0;
  virtual void buildGameState() = 0;
  
  virtual Game * getResult() = 0;
  
private:
  Game * localGame;
  
};