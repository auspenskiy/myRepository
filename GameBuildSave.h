#pragma once

#include "GameBuilder.h"
#include <string>
#include <fstream>
#include "game.h"

/*
Class GameBuildSave: implementation of the build pattern used to save games to file
*/
class GameBuildSave: public GameBuilder{
public:
  GameBuildSave(int saveSlotNum, Game * newGameToSave);
  void buildMap();
  void buildPlayers();
  void buildGameState();
  
  Game * getResult();
private:
  Player ** playerArray;
  int numOfPlayers;
  Map * newMap;
  std::ofstream outStream;
  Game * gameToSave;
  int gameSaveSlotNum;
};