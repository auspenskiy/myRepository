#include "PlayerRandom.h"

#include <time.h>
#include <cstdlib>

PlayerRandom::PlayerRandom(std::string newPlayerName, int newPlayerIndex):Player(newPlayerName, newPlayerIndex){
  srand(static_cast<unsigned int>(time(NULL)));
}

 int PlayerRandom::getRandomFriendlyCountryIndex(Country const* const* countryArray, int arraySize){
   int randomIndex;
   do{
     randomIndex = rand() % arraySize;
   }while (!(countryArray[randomIndex]->getOwnerIndex() == this->getPlayerIndex()));
   
   return randomIndex;
 }
 
 int PlayerRandom::getRandomEnemyCountryIndex(Country const* const* countryArray, int arraySize){
   int randomIndex;
   do{
     randomIndex = rand() % arraySize;
   }while (countryArray[randomIndex]->getOwnerIndex() == this->getPlayerIndex());
   
   return randomIndex;
 }

int PlayerRandom::chooseAction(Map * gameMap){
  return rand() % 2;
}

//chooseCountryToReinforce calls chooseAttackingCountry since the function returns a friendly country
std::string PlayerRandom::chooseCountryToReinforce( Map * gameMap,  int maxNumOfReinforcements){
  return chooseAttackingCountry(gameMap);
}

int PlayerRandom::chooseNumberToReinforce( Map * gameMap,  int maxNumOfReinforcements){
  return rand() % maxNumOfReinforcements + 1;
}


std::string PlayerRandom::chooseAttackingCountry( Map * gameMap) {
  bool hasEnemyCountries = false;
  do{
    attackingCountryIndex = getRandomFriendlyCountryIndex(gameMap->getCountries(), gameMap->getCountryCount());

    for(int x = 0; x < gameMap->getCountries()[attackingCountryIndex]->getNeighbourCount(); x ++){
      if (gameMap->getCountries()[attackingCountryIndex]->getAllNeighbours()[x]->getOwnerIndex() != this->getPlayerIndex()){
		hasEnemyCountries = true;
      }

    }
	
  } while (!hasEnemyCountries);
  
  return gameMap->getCountries()[attackingCountryIndex]->getName();
}

std::string PlayerRandom::chooseDefendingCountry( Map * gameMap){  
  int enemyIndex = getRandomEnemyCountryIndex(gameMap->getCountries()[attackingCountryIndex]->getAllNeighbours(), gameMap->getCountries()[attackingCountryIndex]->getNeighbourCount());
  return gameMap->getCountries()[attackingCountryIndex]->getAllNeighbours()[enemyIndex]->getName();
}

bool PlayerRandom::chooseContinueAttack( Map * gameMap){
  return (int)(rand() % gameMap->getCountries()[attackingCountryIndex]->getArmies()) == 0;
}
int PlayerRandom::chooseNumberOfConsolidationArmies(Map * gameMap, int minConsolidationArmies, int maxConsolidationArmies){
  return rand() % (maxConsolidationArmies - minConsolidationArmies + 1) + minConsolidationArmies;
}

std::string PlayerRandom::chooseSourceFortificationCountry( Map * gameMap){
  return "";
}
std::string PlayerRandom::chooseDestinationFortificationCountry( Map * gameMap, std::list<std::string> & connectedCountries){
  return "";
}
int PlayerRandom::chooseNumberOfFortificationArmies( Map * gameMap){
  return 1;
}