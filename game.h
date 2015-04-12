#include "map.h"
#include "continent.h"
#include "country.h"
#include "controller.h"
#include "textview.h"
#include "game_utils.h"
#include "dice.h"
#include "Player.h"
#include <string>
#include <cstdlib>


class Game{
public:
	//Game(int newNumOfPlayers, std::string * newPlayerNames);
	Game(int newNumOfPlayers, Player * playaArray);
	~Game();
	int play();
	Player * findPlayerByIndex(int i);	//function to find a player using index
	Player * findWinner();
	int countPlayersAlive();
private:
	void fortify(int playerNum);
	void reinforce(int playerNum);
	void attack(int playerNum);
	void battle(std::string attackingCountry, std::string defendingCountry);
	void displayStatistics();
	int getCardsExchange(int playerNum);
	int* getExchangeChoices(int playerNum);
	int exchangeCards(int* choices, int playerNum);//returns number of armies which the player got as a result of exchange for cards
	void updateCountriesAndArmies();
	void outputCountryList(std::list<std::string> countryList);
	bool countryExistsAndFriendly(std::string country, int playerIndex);

	void setupHardcodedMap(Map & mainMap);
	void setupCountryOwners();
	void handleCards(int playerNum);
	TextView * textview;
	Controller * controller;
	Dice * dice;
	Map * map;
	std::string * playerNames;
	int numOfPlayers;
	int totalBattles;
	int playersAlive;
	Player * playerArray;
	Player * currentPlayer;
	Player * defendingPlayer;
};