#pragma once
#include "Player.h"

/*
Class PlayerDefensive: Implementation of Player Strategy Pattern
	A computer opponent who attacks only when certain of victory and the unliklihood of counterattack
*/
class PlayerDefensive : public Player{
public:
  PlayerDefensive(std::string newPlayerName, int newPlayerIndex);
  
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
  std::string attackingCountry;
  std::string defendingCountry;
  int attackingCountryIndex;
  int defendingCountryIndex;
};