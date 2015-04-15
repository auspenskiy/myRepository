#pragma once

#include "GameBuilder.h"


/*
Class GameBuildLoad: implementation of the build pattern used to create new games
*/
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