#include "PlayerAggressive.h"
#include <string>

PlayerAggressive::PlayerAggressive(std::string newPlayerName, int newPlayerIndex):Player(newPlayerName, newPlayerIndex){
  defendingCountry = "";
}

/*
 *      View::inform("1 - Attack");
 *      View::inform("2 - Fortify");
 *      View::inform("0 - End turn");
 */
int PlayerAggressive::chooseAction(Map * gameMap){
  for(int x = 0; x < gameMap->getCountryCount() ; x++){
    if (gameMap->getCountries()[x]->getOwnerIndex() == this->getPlayerIndex()){
      if(gameMap->getCountries()[x]->getArmies() > 1){
	attackingCountry= gameMap->getCountries()[x]->getName();
	for(int y = 0; y < gameMap->getCountries()[x]->getNeighbourCount(); y++){
	  if (gameMap->getCountries()[x]->getAllNeighbours()[y]->getArmies() < gameMap->getCountries()[x]->getArmies() &&
	    gameMap->getCountries()[x]->getAllNeighbours()[y]->getOwnerIndex() != this->getPlayerIndex()){   
	    defendingCountry= gameMap->getCountries()[x]->getAllNeighbours()[y]->getName();
	    return 1;
	  }
	}
      }
    }
  }
  return 0;
}

std::string PlayerAggressive::chooseCountryToReinforce( Map * gameMap,  int maxNumOfReinforcements){
  int choice = chooseAction(gameMap);
  
  if (choice = 0){
    for(int x = 0; x < gameMap->getCountryCount() ; x++){
      if (gameMap->getCountries()[x]->getOwnerIndex() == this->getPlayerIndex()){
	attackingCountry= gameMap->getCountries()[x]->getName();
      }
    }
  }
  
  return attackingCountry;
}

int PlayerAggressive::chooseNumberToReinforce( Map * gameMap,  int maxNumOfReinforcements){
  return maxNumOfReinforcements;
}

std::string PlayerAggressive::chooseAttackingCountry( Map * gameMap) {
  return attackingCountry;
}

std::string PlayerAggressive::chooseDefendingCountry( Map * gameMap){
  return defendingCountry;
}
bool PlayerAggressive::chooseContinueAttack( Map * gameMap){
  return true;
}
int PlayerAggressive::chooseNumberOfConsolidationArmies(Map * gameMap, int minConsolidationArmies, int maxConsolidationArmies){
    return maxConsolidationArmies;
}

std::string PlayerAggressive::chooseSourceFortificationCountry( Map * gameMap){
  return "";
}
std::string PlayerAggressive::chooseDestinationFortificationCountry( Map * gameMap, std::list<std::string> & connectedCountries){
  return "";
}
int PlayerAggressive::chooseNumberOfFortificationArmies( Map * gameMap){
  return 0;
}

