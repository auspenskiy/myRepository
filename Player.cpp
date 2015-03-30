#include "Player.h"
#include <ctime>
#include <iostream>

Player::Player()
{
	cards = new Card[3];
}


Player::~Player()
{
	delete cards;
}

void Player::setName(std::string mName)
{
	name = mName;
}
std::string Player::getName()
{
	return name;
}

Card* Player::exchangeCards()
{
	int infantry = cards[0].getQuantity();
	int cavalry = cards[1].getQuantity();
	int artillery = cards[2].getQuantity();

	for (int i = 0; i < 2; ++i)
	{
		if (cards[i].getQuantity() > 2)
		{
			cards[i].decrementQuantity(3);
			return cards;
		}
	}

	if (infantry > 0 && cavalry > 0 && artillery > 0)
	{
		cards[0].decrementQuantity(3);
		cards[1].decrementQuantity(3);
		cards[2].decrementQuantity(3);
	}

	return cards;
}

void Player::addCard()
{
	if (hasConquered)
	{
		int xRan;
		srand(time(0)); // This will ensure a really randomized number by help of time.
		xRan = rand() % 3;
		cards[xRan].incrementQuantity();
		hasConquered = false;
	}
}

Card* Player::getCards()
{
	return cards;
}

void Player::setHasConquered(bool mHasConquered)
{
	hasConquered = mHasConquered;
}

bool Player::getHasConquered()
{
	return hasConquered;
}
