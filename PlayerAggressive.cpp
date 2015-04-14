#include "PlayerAggressive.h"
#include <string>

PlayerAggressive::PlayerAggressive(std::string newPlayerName, int newPlayerIndex):Player(newPlayerName, newPlayerIndex){
  defendingCountry = "";
}


int PlayerAggressive::chooseAction(Map * gameMap){
	//for all countries
  for(int x = 0; x < gameMap->getCountryCount() ; x++){
	  //if the country is owned by the AI
    if (gameMap->getCountries()[x]->getOwnerIndex() == this->getPlayerIndex()){
		//if the country has enough armies to attack someone
      if(gameMap->getCountries()[x]->getArmies() > 1){
		  //set that as the attacking country
		attackingCountry= gameMap->getCountries()[x]->getName();

			//search all neighbours to find if an enemy neighbour has less armies than us
		for(int y = 0; y < gameMap->getCountries()[x]->getNeighbourCount(); y++){
			//if the neighbout has less armies && the neighbour does not belong to us
		  if (gameMap->getCountries()[x]->getAllNeighbours()[y]->getArmies() < gameMap->getCountries()[x]->getArmies() &&
			gameMap->getCountries()[x]->getAllNeighbours()[y]->getOwnerIndex() != this->getPlayerIndex()){   
				//set that neighbour as defender
			defendingCountry= gameMap->getCountries()[x]->getAllNeighbours()[y]->getName();
				//return the choice to attack that neighbour
			return 1;
		  }
		}
      }
    }
  }
  //if no one is found who fits the above criteria, attack no one.
  return 0;
}

std::string PlayerAggressive::chooseCountryToReinforce( Map * gameMap,  int maxNumOfReinforcements){
	//get action choice (if choice is 1, it will have automatically picked a good country to reinforce
	int choice = chooseAction(gameMap);
  
	//if the choose action returned 0 i.e. it did not find an ideal country to attack, reinforce near ANY country you might be able to attack
  if (choice == 0){
	  //for all countries
    for(int x = 0; x < gameMap->getCountryCount() ; x++){
		//if its a friendly country
      if (gameMap->getCountries()[x]->getOwnerIndex() == this->getPlayerIndex()){
			//search all its neighbours
		  for(int y = 0; y < gameMap->getCountries()[x]->getNeighbourCount(); y++){
				//if the neighbour does not belong to us, reinforce next to it
			  if (gameMap->getCountries()[x]->getAllNeighbours()[y]->getOwnerIndex() != this->getPlayerIndex()){   
					//set that neighbour as defender
				attackingCountry= gameMap->getCountries()[x]->getName();
				defendingCountry= gameMap->getCountries()[x]->getAllNeighbours()[y]->getName();				
			  }
			}		
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

