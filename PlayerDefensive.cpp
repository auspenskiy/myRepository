#include "PlayerDefensive.h"

PlayerDefensive::PlayerDefensive(std::string newPlayerName, int newPlayerIndex):Player(newPlayerName, newPlayerIndex){
  
}

int PlayerDefensive::chooseAction(Map * gameMap){
  int enemyArmies=0;
  int lowestEnemyArmyAmount = 0;
  int lowestEnemyIndex = -1;
  for(int x = 0; x < gameMap->getCountryCount() ; x++){
    if (gameMap->getCountries()[x]->getOwnerIndex() == this->getPlayerIndex()){
      if(gameMap->getCountries()[x]->getArmies() > 1){
	enemyArmies = 0;
	lowestEnemyArmyAmount = 0;
	lowestEnemyIndex = -1;
	for(int y = 0; y < gameMap->getCountries()[x]->getNeighbourCount(); y++){
	  if (gameMap->getCountries()[x]->getAllNeighbours()[y]->getOwnerIndex() != this->getPlayerIndex()){
	    enemyArmies += gameMap->getCountries()[x]->getAllNeighbours()[y]->getArmies();
	    if(lowestEnemyIndex < 0 || lowestEnemyArmyAmount > gameMap->getCountries()[x]->getAllNeighbours()[y]->getArmies()){
	      lowestEnemyIndex = y;
	      lowestEnemyArmyAmount = gameMap->getCountries()[x]->getAllNeighbours()[y]->getArmies();
	    }	      
	  }
	}
	if(enemyArmies < gameMap->getCountries()[x]->getArmies() && enemyArmies != 0){
	  attackingCountry= gameMap->getCountries()[x]->getName();
	  attackingCountryIndex = x;
	  defendingCountry= gameMap->getCountries()[x]->getAllNeighbours()[lowestEnemyIndex]->getName();
	  defendingCountryIndex=lowestEnemyIndex;
	  return 1;
	}  
      }
    }
  }
  return 0;
}

std::string PlayerDefensive::chooseCountryToReinforce( Map * gameMap,  int maxNumOfReinforcements){
  int minEnemyArmiesCount = 0;
  int minEnemyArmiesCountIndex = -1;
  int enemyArmiesTemp = 0;
  
  for(int x = 0; x < gameMap->getCountryCount() ; x++){
    if (gameMap->getCountries()[x]->getOwnerIndex() == this->getPlayerIndex()){
      enemyArmiesTemp = 0;
      for(int y = 0; y < gameMap->getCountries()[x]->getNeighbourCount(); y++){
	if (gameMap->getCountries()[x]->getAllNeighbours()[y]->getOwnerIndex() != this->getPlayerIndex()){
	  enemyArmiesTemp += gameMap->getCountries()[x]->getAllNeighbours()[y]->getArmies();	      
	}  
      }
      if((enemyArmiesTemp < minEnemyArmiesCount || minEnemyArmiesCountIndex == -1) && enemyArmiesTemp > 0){
	minEnemyArmiesCount = enemyArmiesTemp;
	minEnemyArmiesCountIndex = x;
      }
    }      
  }
  return gameMap->getCountries()[minEnemyArmiesCountIndex]->getName();
}

int PlayerDefensive::chooseNumberToReinforce( Map * gameMap,  int maxNumOfReinforcements){
  return maxNumOfReinforcements;
}


std::string PlayerDefensive::chooseAttackingCountry( Map * gameMap) {
  return attackingCountry;
}

std::string PlayerDefensive::chooseDefendingCountry( Map * gameMap){
  return defendingCountry;
}

bool PlayerDefensive::chooseContinueAttack( Map * gameMap){
  int enemyArmies = 0;
  for(int y = 0; y < gameMap->getCountries()[attackingCountryIndex]->getNeighbourCount(); y++){
    if (gameMap->getCountries()[attackingCountryIndex]->getAllNeighbours()[y]->getOwnerIndex() != this->getPlayerIndex()){
      enemyArmies += gameMap->getCountries()[attackingCountryIndex]->getAllNeighbours()[y]->getArmies();	      
    }
  }
  
  //continues attack if it still has more armies than all neighbouring enemies combined
  return (enemyArmies < gameMap->getCountries()[attackingCountryIndex]->getArmies());
}
int PlayerDefensive::chooseNumberOfConsolidationArmies(Map * gameMap, int minConsolidationArmies, int maxConsolidationArmies){
  return minConsolidationArmies;
}

std::string PlayerDefensive::chooseSourceFortificationCountry( Map * gameMap){
  return "";
}
std::string PlayerDefensive::chooseDestinationFortificationCountry( Map * gameMap, std::list<std::string> & connectedCountries){
  return "";
}
int PlayerDefensive::chooseNumberOfFortificationArmies( Map * gameMap){
  return 1;
}

bool PlayerDefensive::chooseExchangeCards(Map * gameMap){
	return false;
}