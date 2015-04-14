#include "GameBuildNew.h"
#include <fstream>
#include "game_utils.h"
#include "MapFileAdapter.h"
#include "PlayerHuman.h"
#include "PlayerAggressive.h"
#include "PlayerDefensive.h"
#include "PlayerRandom.h"

GameBuildNew::GameBuildNew(){
  
}

void GameBuildNew::buildMap(){
	std::string inString = "";
	std::string loadFile;
	std::ifstream inStream;
	bool mapLoaded = false;

	View::prompt("Would you like to create a custom map or play on an existing map?");
	View::prompt("Please select:\n c - custom map\n e - play on an existing map");

	inString = View::getString();

	if (inString.compare("c") == 0){
		MapFileAdapter* mapLoad = new MapFileAdapter();
		newMap = mapLoad->createMap();
		MapFileAdapter* adapter = new MapFileAdapter();
		adapter->saveMapToFile(newMap, "../Resources/Test.map");
	}
	else
	{

		do{
			View::prompt("Please enter the name of the map you would like to play");
			loadFile = View::getString();
			inStream.open("../Resources/Canada.map");

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
				newMap = mapLoad->loadMap("../Resources/Canada.map");
				mapLoaded = true;

			}
		} while (!mapLoaded);
	}
}

void GameBuildNew::buildPlayers(){
  int inInt;
  View::inform("How many people are playing?");
  
  do{
    View::prompt("Please enter between 2 and 6 players");  
    numOfPlayers = View::getInt();
  }while (numOfPlayers < 2 || numOfPlayers > 6);
  
  playerArray = new Player*[numOfPlayers];
  
  for (int a = 0; a < numOfPlayers; a++)
  {
    do{
      View::inform("Player "+ intToString(a) + ": Please select player type");
      View::inform("1 - Human");
      View::inform("2 - Aggressive Computer");
      View::inform("3 - Defensive Computer");
      View::inform("4 - Unpredictable Computer");
      inInt = View::getInt();
      if (inInt < 1 || inInt > 4){
	View::inform("\nInvalid input.  Please select an option between 1 and 4");
      }
    }while(inInt < 1 || inInt > 4);
    
    if(inInt == 1){
	View::prompt("Please enter the name of player " + intToString(a) + ":");
	playerArray[a] = new PlayerHuman(View::getString(), a);
    }
    else{
      View::prompt("Please enter the name of computer player " + intToString(a) + ":");
      if (inInt ==2){
	playerArray[a] = new PlayerAggressive(View::getString()+ " (Aggressive Computer)", a);
      }
      else if (inInt ==3){
	playerArray[a] = new PlayerDefensive(View::getString()+" (Defensive Computer)", a);
      }
      else if (inInt ==4){
	playerArray[a] = new PlayerRandom(View::getString()+" (Unpredictable Computer)", a);
      }
    }
  }
}

void GameBuildNew::buildGameState(){
  //Nothing to do here for a new game.  Intentionally left empty.
}

void GameBuildNew::buildCustomMap(){

}

Game * GameBuildNew::getResult(){
  
  return new Game(numOfPlayers, playerArray, newMap);
}