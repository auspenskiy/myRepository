#pragma once
#include <string>
#include "View.h"
#include "game_utils.h"
#include "Player.h"
#include "map.h"

class Map;

class PlayerHuman: public Player{
public:
  PlayerHuman(std::string newPlayerName, int newPlayerIndex);
  
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
 
private:
  std::list<std::string> enemyNeighbourList;
  std::string countryToReinforce;
  std::string attackingCountry;
  std::string defendingCountry;
  std::string sourceCountry;
  std::string destinationCountry;
};