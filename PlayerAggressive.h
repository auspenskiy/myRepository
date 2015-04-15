#pragma once
#include "Player.h"

/*
Class PlayerAggressive: Implementation of Player Strategy Pattern
	A computer opponent who attack as much as possible
*/
class PlayerAggressive : public Player
{
public:
  PlayerAggressive(std::string newPlayerName, int newPlayerIndex);
  
  virtual int chooseAction(Map * gameMap);
  
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
};