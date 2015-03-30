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
	Card* exchangeCards();
	void addCard();
	void setHasConquered(bool mIsConquered);
	bool getHasConquered();
	Card* getCards();

private:
	std::string name;
	Card* cards;
	bool hasConquered;
};

