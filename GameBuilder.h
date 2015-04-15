#pragma once
#include "game.h"

/*
Class Game Build: A virtual class, used to implement the builder pattern for creating, saving and loading games
*/
class GameBuilder{
  
public:
	//1) Builds current state of the map (i.e. map + armies on countries + ownership of countries)
  virtual void buildMap() = 0;
  //2) Builds player state (number of players, cards held by each, strategy of each comp player)
  virtual void buildPlayers() = 0;
  //3) Builds current state of the game engine (which player's turn/phase)
  virtual void buildGameState() = 0;
  
  virtual Game * getResult() = 0;
  
private:
  Game * localGame;
  
};