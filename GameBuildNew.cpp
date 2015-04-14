#include "GameBuildNew.h"
#include <fstream>
#include "game_utils.h"
#include "MapFileAdapter.h"

GameBuildNew::GameBuildNew(){
  
}

void GameBuildNew::buildMap(){
  std::string loadFile;
  std::ifstream inStream;
  bool mapLoaded = false;
    
  do{
    View::prompt("Please enter the name of the map you would like to play");
    //loadFile = View::getString();
    inStream.open ("../Resources/World.map");
    
    if (!inStream.good())
    {
      View::inform("Map file not found");
      inStream.close();
    }
    else
    {
      //inStream.close();
      //!!!future improvement: try and catch exceptions of bad map formats
		MapFileAdapter* mapLoad = new MapFileAdapter();
	  newMap = mapLoad->loadMap("../Resources/World.map");
      mapLoaded = true;

    }
  }while(!mapLoaded);
} 

void GameBuildNew::buildPlayers(){
  
  View::inform("How many people are playing?");
  
  do{
    View::prompt("Please enter between 2 and 6 players");  
    numOfPlayers = View::getInt();
  }while (numOfPlayers < 2 || numOfPlayers > 6);
  
  playerArray = new Player*[numOfPlayers];
  
  for (int a = 0; a < numOfPlayers; a++)
  {
    View::prompt("What is the name of player " + intToString(a) + "?");
    playerArray[a] = new Player(View::getString(), a);
  }
}

void GameBuildNew::buildGameState(){
  //Nothing to do here for a new game.  Intentionally left empty.
}

Game * GameBuildNew::getResult(){
  
  return new Game(numOfPlayers, playerArray, newMap);
}