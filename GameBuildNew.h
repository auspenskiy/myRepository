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
  Player ** playerArray;
  int numOfPlayers;
  Map * newMap;
  void buildCustomMap();
};