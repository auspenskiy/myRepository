#pragma once
#include <string>
#include "Card.h"

class Player
{
public:
	Player();
	~Player();
	void setName(std::string mName);
	std::string getName();
	void exchangeCards(int* choices);
	void addCard();
	void setHasConquered(bool mIsConquered);
	bool getHasConquered();
	Card* getCards();
	void processCardExchange();
	void setNumberOfArmies(int numOfArmies);
	int getNumberOfArmies();
	void incrementArmies(int incrementValue);
	void transferCards(Player* player);
private:
	std::string name;
	Card* cards;
	bool hasConquered;
	bool canExchangeCards();
	int* getExchangeChoices();
	int getTotalCards();
	int numOfArmies;
	int numOfCountriesOwned;
};

