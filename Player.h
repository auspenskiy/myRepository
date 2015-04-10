#pragma once
#include <string>
#include "country.h"

class Player{
public:
	Player();
	Player(std::string aName);
	~Player();
	void setName(std::string);
	std::string getName();
	void setPlayerIndex(int index);
	int getBattlesWon();
	int getBattlesLost();
	int getNumCountriesOwned();
	int getNumArmiesOwned();
	void setArmiesOwned(int armiesOwned);
	void setCountriesOwned(int countriesOwned);
	int getPlayerIndex();
	void setBattlesWon();
	void setBattlesLost();
	bool getIsAlive();
	void setDeath();
	std::string statistics();

	void exchangeCards(int* choices);
	void addCard();
	void setHasConquered(bool mIsConquered);
	bool getHasConquered();
	Card* getCards();
	void processCardExchange();
	void setNumberOfArmies(int numOfArmies);
	int getNumberOfArmies();
	void incrementArmies(int incrementValue);
	void transferCards(Player player);
private:
	std::string name;
	Card* cards;
	bool hasConquered;
	bool canExchangeCards();
	int* getExchangeChoices();
	int getTotalCards();
	//int numOfArmies;
	//int numOfCountriesOwned;
	bool isAlive;
	int battlesWon;
	int battlesLost;
	int playerIndex;
	int numCountriesOwned;
	int numArmiesOwned;
	//int totalPlayers = 0;
	std::string name;
};
