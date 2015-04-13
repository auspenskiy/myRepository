#pragma once

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
	Game(int newNumOfPlayers, Player ** playaArray, Map * newMap, int newPlayerTurns=0, 
	     int newPlayerIndex=0, int newBonusArmies=0, bool newJustLoaded=false);
	~Game();
	int play();
	Player * findPlayerByIndex(int i);	//function to find a player using index
	Player * findWinner();
	int countPlayersAlive();
	
//CONST ACCESSORS-------------------------------
	inline const Map * getMap(){return map;}
	inline Player ** getPlayerArray(){return playerArray;}
	inline int getNumOfPlayers(){return numOfPlayers;}
	inline int getPlayerTurns(){return playerTurns;}
	inline int getPlayerIndex(){return playerIndex;}
	inline int getBonusArmies(){return bonusArmies;}
	
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
	void saveGame();
	
	bool justLoaded;
	int bonusArmies;
	int playerTurns;
	int playerIndex;
	TextView * textview;
	Controller * controller;
	Dice * dice;
	Map * map;
	std::string * playerNames;
	int numOfPlayers;
	int totalBattles;
	int playersAlive;
	Player ** playerArray;
	Player * currentPlayer;
	Player * defendingPlayer;
};