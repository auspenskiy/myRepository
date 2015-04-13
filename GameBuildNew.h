#pragma once

#include "GameBuilder.h"


class GameBuildNew: public GameBuilder{
public:
  GameBuildNew();
  void buildMap();
  void buildPlayers();
  void buildGameState();
  
  Game * getResult();
  
private:
  Controller cr;
  TextView tv; 
  Player ** playerArray;
  int numOfPlayers;
  Map * newMap;
};