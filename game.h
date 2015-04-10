#include "map.h"
#include "continent.h"
#include "country.h"
#include "controller.h"
#include "textview.h"
#include "game_utils.h"
#include "dice.h"

#include <string>
#include "Player.h"
#include <cstdlib>

class Game{
public:
  Game(int newNumOfPlayers, Player* newPlayerNames);
  ~Game();
  int play();
  
private:
  void fortify(int playerNum);
  void reinforce(int playerNum);
  void attack(int playerNum);
  void battle(std::string attackingCountry, std::string defendingCountry);
  void handleCards(int playerNum);
  
  void outputCountryList(std::list<std::string> countryList);
  bool countryExistsAndFriendly(std::string country, int playerIndex);
    
  void setupHardcodedMap(Map & mainMap);
  void setupCountryOwners();

  TextView * textview;
  Controller * controller;
  Dice * dice;
  Map * map;
  Player* players;

  int numOfPlayers;

};