#include "GameBuildSave.h"
#include "MapConfig.h"

GameBuildSave::GameBuildSave(int saveSlotNum, Game * newGameToSave){
  gameToSave = newGameToSave;
  gameSaveSlotNum = saveSlotNum;
}

void GameBuildSave::buildMap(){
  MapConfig mapSave;
  
  mapSave.saveMap(gameToSave->getMap(), "save" +intToString(gameSaveSlotNum) + ".map");
  
  outStream.open (("save" +intToString(gameSaveSlotNum) + ".msv").c_str());
    outStream << gameToSave->getMap()->getCountryCount() << "\n";
    for(int x = 0; x < gameToSave->getMap()->getCountryCount(); x ++){
      outStream << gameToSave->getMap()->getCountries()[x]->getName()<< ","<< gameToSave->getMap()->getCountries()[x]->getArmies()<<"," << gameToSave->getMap()->getCountries()[x]->getOwnerIndex()  << "\n";    
    }
  outStream.close();
}

void GameBuildSave::buildPlayers(){
  outStream.open (("save" +intToString(gameSaveSlotNum) + ".psv").c_str());
  
  outStream << gameToSave->getNumOfPlayers() << std::endl;
  for(int x = 0; x < gameToSave->getNumOfPlayers(); x++){
    outStream << gameToSave->getPlayerArray()[x]->getName() << ",";
    outStream << gameToSave->getPlayerArray()[x]->getPlayerIndex() << ",";
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

void GameBuildSave::buildGameState(){
  outStream.open (("save" +intToString(gameSaveSlotNum) + ".gsv").c_str());
    outStream << gameToSave->getPlayerTurns() << std::endl;
    outStream << gameToSave->getPlayerIndex() << std::endl;
    outStream << gameToSave->getBonusArmies() << std::endl;
  outStream.close();
}

Game * GameBuildSave::getResult(){  
  //need new constructor for mid-game initialization
  return NULL;
  
}