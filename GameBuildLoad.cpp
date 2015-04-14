#include "GameBuildLoad.h"
#include "MapConfig.h"
#include <sstream>
#include <stdlib.h> 
#include <fstream>

GameBuildLoad::GameBuildLoad(int saveSlotNum){
  gameSaveSlotNum = saveSlotNum;
}

void GameBuildLoad::buildMap(){
  MapConfig mapLoad;
  int countryCount;
  std::string inCountryName;
  int inArmies;
  int inOwner;
  
  newMap = mapLoad.loadMap("save" +intToString(gameSaveSlotNum) + ".map");
  
  inStream.open (("save" +intToString(gameSaveSlotNum) + ".msv").c_str());
  
  inStream >> countryCount;
  inStream.get();

    for(int x = 0; x < countryCount; x ++){
      getline(inStream, inCountryName, ',');
     
      inStream >> inArmies;
      inStream.get();
      inStream >> inOwner;
      inStream.get();
      
      newMap->setCountryArmies(inCountryName, inArmies, false);
      newMap->setCountryOwnerIndex(inCountryName, inOwner, false);
    }
    getline(inStream, inCountryName, '\n');
    
  inStream.close();
}

void GameBuildLoad::buildPlayers(){
  int inInt;
  std::string newName;
  std::string inString;
  
  inStream.open (("save" +intToString(gameSaveSlotNum) + ".psv").c_str());
  
  inStream >> numOfPlayers;
  inStream.get();
  playerArray = new Player*[numOfPlayers];
  
  for(int x = 0; x < numOfPlayers; x++){
    getline(inStream, newName, ',');//getName
    inStream >> inInt;//getPlayer index
    inStream.get();
    getline(inStream, inString, ',');
    playerArray[x] = tinyFactory(inString, newName, inInt);
    
    inStream >> inInt;//getDeath
    inStream.get();
    if (inInt == 0){
      playerArray[x]->setDeath();
    }
    
    inStream >> inInt;
    inStream.get();
    playerArray[x]->setHasConquered((bool)inInt);
    
    inStream >> inInt;
    inStream.get();
    for (int y=0; y < inInt; y++){
      playerArray[x]->setBattlesLost();
    }
    
    inStream >> inInt;
    inStream.get();
    for (int y=0; y < inInt; y++){
      playerArray[x]->setBattlesWon();
    }
    
    inStream >> inInt;
    inStream.get();
    playerArray[x]->setArmiesOwned(inInt);
    
    inStream >> inInt;
    inStream.get();
    playerArray[x]->setCountriesOwned(inInt);
    
    for(int y = 0; y < 3; y++){
      inStream >> inInt;
      inStream.get();
      playerArray[x]->getCards()[y]->setQuantity(inInt);
    }
    getline(inStream, inString, '\n');
  }
  
  inStream.close();
  
}

void GameBuildLoad::buildGameState(){
  int inInt;
  
  inStream.open (("save" +intToString(gameSaveSlotNum) + ".gsv").c_str());
    inStream >> inInt;
    inStream.get();
    playerTurns = inInt;
    
    inStream >> inInt;
    inStream.get();
    playerIndex = inInt;
    
    inStream >> inInt;
    inStream.get();
    bonusArmies = inInt;

  inStream.close();
}

Game * GameBuildLoad::getResult(){  
  return new Game(numOfPlayers, playerArray, newMap, playerTurns, playerIndex, bonusArmies, true);
}