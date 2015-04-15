#include "GameBuildSave.h"
#include "MapFileAdapter.h"

GameBuildSave::GameBuildSave(int saveSlotNum, Game * newGameToSave){
  gameToSave = newGameToSave;
  gameSaveSlotNum = saveSlotNum;
}

//builds the game map
void GameBuildSave::buildMap(){
	MapFileAdapter* mapSave = new MapFileAdapter();
  
  mapSave->saveMapToFile(gameToSave->getMap(), "save" + intToString(gameSaveSlotNum) + ".map");
  
  outStream.open (("save" +intToString(gameSaveSlotNum) + ".msv").c_str());
    outStream << gameToSave->getMap()->getCountryCount() << "\n";
    for(int x = 0; x < gameToSave->getMap()->getCountryCount(); x ++){
      outStream << gameToSave->getMap()->getCountries()[x]->getName()<< ","<< gameToSave->getMap()->getCountries()[x]->getArmies()<<"," << gameToSave->getMap()->getCountries()[x]->getOwnerIndex()  << "\n";    
    }
  outStream.close();
}

//builds the game's player array
void GameBuildSave::buildPlayers(){
  outStream.open (("save" +intToString(gameSaveSlotNum) + ".psv").c_str());
  
  outStream << gameToSave->getNumOfPlayers() << std::endl;
  for(int x = 0; x < gameToSave->getNumOfPlayers(); x++){
    outStream << gameToSave->getPlayerArray()[x]->getName() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getPlayerIndex() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getPlayerType() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getIsAlive() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getHasConquered() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getBattlesLost() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getBattlesWon() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getNumArmiesOwned() << ","; 
    outStream << gameToSave->getPlayerArray()[x]->getNumCountriesOwned() << ",";
    
    for(int y = 0; y < 3; y++){      
      outStream << gameToSave->getPlayerArray()[x]->getCards()[y]->getQuantity() << ",";
    }
    outStream << std::endl;
  }
  
  outStream.close();
  
}

//builds the game object and its specific instance varibles
void GameBuildSave::buildGameState(){
  outStream.open (("save" +intToString(gameSaveSlotNum) + ".gsv").c_str());
    outStream << gameToSave->getPlayerTurns() << std::endl;
    outStream << gameToSave->getPlayerIndex() << std::endl;
    outStream << gameToSave->getBonusArmies() << std::endl;
	outStream << gameToSave->getPlayerArray()[0]->getNumOfArmiesExchange() << std::endl;
  outStream.close();
}

Game * GameBuildSave::getResult(){  
  return NULL;
}