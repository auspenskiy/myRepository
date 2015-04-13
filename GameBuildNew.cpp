#include "GameBuildNew.h"
#include <fstream>
#include "game_utils.h"
#include "MapConfig.h"

GameBuildNew::GameBuildNew(){
  
}

void GameBuildNew::buildMap(){
  std::string loadFile;
  std::ifstream inStream;
  bool mapLoaded = false;
    
  do{
    tv.prompt("Please enter the name of the map you would like to play");
    loadFile = cr.getString();
    inStream.open (loadFile.c_str());
    
    
    if (!inStream.good())
    {
      tv.inform("Map file not found");
      inStream.close();
    }
    else
    {
      inStream.close();
      //!!!future improvement: try and catch exceptions of bad map formats
      MapConfig mapLoad;
      newMap = mapLoad.loadMap("m");
      mapLoaded = true;

    }
  }while(!mapLoaded);
} 

void GameBuildNew::buildPlayers(){
  
  tv.inform("How many people are playing?");
  
  do{
    tv.prompt("Please enter between 2 and 6 players");  
    numOfPlayers = cr.getInt();
  }while (numOfPlayers < 2 || numOfPlayers > 6);
  
  playerArray = new Player*[numOfPlayers];
  
  for (int a = 0; a < numOfPlayers; a++)
  {
    tv.prompt("What is the name of player " + intToString(a) + "?");
    playerArray[a] = new Player(cr.getString(), a);
  }
}

void GameBuildNew::buildGameState(){
  //Nothing to do here for a new game.  Intentionally left empty.
}

Game * GameBuildNew::getResult(){
  
  return new Game(numOfPlayers, playerArray, newMap);
}