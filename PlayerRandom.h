#pragma once
#include "Player.h"

/*
Class PlayerRandom: Implementation of Player Strategy Pattern
	A computer opponent who leaves all his decisions to random varibles.
*/
class PlayerRandom : public Player{
public:
  PlayerRandom(std::string newPlayerName, int newPlayerIndex);
  
  int chooseAction(Map * gameMap);
  
  std::string chooseCountryToReinforce( Map * gameMap,  int maxNumOfReinforcements);
  int chooseNumberToReinforce( Map * gameMap,  int maxNumOfReinforcements);

  std::string chooseSourceFortificationCountry( Map * gameMap);
  std::string chooseDestinationFortificationCountry( Map * gameMap, std::list<std::string> & connectedCountries);
  int chooseNumberOfFortificationArmies( Map * gameMap);

  std::string chooseAttackingCountry( Map * gameMap) ;
  std::string chooseDefendingCountry( Map * gameMap);
  bool chooseContinueAttack( Map * gameMap);
  int chooseNumberOfConsolidationArmies(Map * gameMap, int minConsolidationArmies, int maxConsolidationArmies);

  bool chooseExchangeCards(Map * gameMap);
 
private:
  int getRandomFriendlyCountryIndex(Country const* const* countryArray, int arraySize);
  int getRandomEnemyCountryIndex(Country const* const* countryArray, int arraySize);
  
  int attackingCountryIndex;
};