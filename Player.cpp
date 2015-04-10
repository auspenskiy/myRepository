#include "Player.h"
#include <ctime>
#include <iostream>

void Player::incrementArmies(int incrementValue)
{
	numArmiesOwned += incrementValue;
}

void Player::setNumberOfArmies(int mNumOfArmies)
{
	numArmiesOwned = mNumOfArmies;
}
int Player::getNumberOfArmies()
{
	return numArmiesOwned;
}

bool Player::canExchangeCards()
{
	int infantry = cards[0].getQuantity();
	int cavalry = cards[1].getQuantity();
	int artillery = cards[2].getQuantity();

	if (infantry >= 1 && cavalry >= 1 && artillery >= 1)
	{
		return true;
	}
	else
	{
		if (infantry > 2)
		{
			return true;
		}
		else if (cavalry > 2)
		{
			return true;
		}
		else if (artillery > 2)
		{
			return true;
		}
	}
	return false;
}
void Player::processCardExchange()
{
	int infantry = cards[0].getQuantity();
	int cavalry = cards[1].getQuantity();
	int artillery = cards[2].getQuantity();
	std::cout << "You have " << infantry << " infantry cards, " << cavalry << " cavalry cards, and " << artillery << " artillery cards" << std::endl;

	if (canExchangeCards())
	{
		std::cout << "You can exchange 3 cards of the same type or three cards of all different types for armies. " <<std::endl;
		exchangeCards(getExchangeChoices());
	}
	else
	{
		std::cout << "You are not eligible to exchange cards for armies. " << std::endl;
	}
}

int* Player::getExchangeChoices()
{
	int* choices = new int[3];
	std::fill(choices, choices + 3, 0);

	std::cout << "You need to choose 3 cards of the same type or three cards of all different types to exchange for armies. " << std::endl;

	if (getTotalCards() >= 5)
	{
		std::cout << "You have more than 5 cards. You must exchange three of them for armies. " << std::endl;
		int sumOfChoices = choices[0] + choices[1] + choices[2];
		do
		{
			//check if a player will exchange all cards of the same type
			for (int i = 0; i < 3; i++)
			{
				if (cards[i].getQuantity() > 3)
				{
					std::cout << "You have more than 3 cards of " << cards[i].getType(i) << ". Would you like to exchange all of them for armies ? (y / n)" << std::endl;
					char decision = 'n';
					do
					{
						if (decision != 'n' && decision != 'y')
						{
							std::cout << "Your choice is invalid. Please choose y or n " << std::endl;
						}
						std::cin >> decision;
					} while (decision != 'n' && decision != 'y');

					if (decision == 'y')
					{
						choices[i] = 3;
						return choices;
					}
					else
					{
						continue;
					}
				}
			}

			for (int i = 0; i < 3; i++)
			{
				if (cards[i].getQuantity() > 0)
				{
					char choice;
					std::cout << "You have " << cards[i].getQuantity() << " of " << cards[i].getType(i) << ". Would you like to use " << cards[i].getType(i) << " cards for exchange (y/n): ";
					std::cin >> choice;
					do
					{
						if (choice != 'y' && choice != 'n')
						{
							std::cout << "Your choice is invalid. Please choose y or n " << std::endl;
						}

					} while (choice != 'y' && choice != 'n');

					if (choice == 'y')
					{
						int numChoice = 1;
						do
						{
							if (numChoice < 0 && numChoice > cards[i].getQuantity())
							{
								std::cout << "Your choice is invalid " << std::endl;
							}
							std::cout << "How many " << cards[i].getType(i) << " cards would you like to exchange? Enter the number between 1 and " << cards[i].getQuantity() << std::endl;
							std::cin >> numChoice;
						} while (numChoice < 1 && numChoice > cards[i].getQuantity());

						choices[i] = numChoice;
					}
					else
					{
						continue;
					}
				}
			}
			sumOfChoices = choices[0] + choices[1] + choices[2];

			if (sumOfChoices > 3)
			{
				return choices;
			}

		} while (sumOfChoices < 3);
	}
	//check if a player will exchange all cards of the same type
	for (int i = 0; i < 3; i++)
	{
		if (cards[i].getQuantity() > 3)
		{
			std::cout << "You have more than 3 cards of " << cards[i].getType(i) << ". Would you like to exchange all of them for armies ? (y / n)" << std::endl;
			char decision = 'n';
			do
			{
				if (decision != 'n' && decision != 'y')
				{
					std::cout << "Your choice is invalid. Please choose y or n " << std::endl;
				}
				std::cin >> decision;
			} while (decision != 'n' && decision != 'y');

			if (decision == 'y')
			{
				choices[i] = 3;
				return choices;
			}
			else
			{
				continue;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (cards[i].getQuantity() > 0)
		{
			char choice;
			std::cout << "You have " << cards[i].getQuantity() << " of " << cards[i].getType(i) << ". Would you like to use " << cards[i].getType(i) << " cards for exchange (y/n): ";
			std::cin >> choice;
			do
			{
				if (choice != 'y' && choice != 'n')
				{
					std::cout << "Your choice is invalid. Please choose y or n " << std::endl;
				}

			} while (choice != 'y' && choice != 'n');

			if (choice == 'y')
			{
				int numChoice = 1;
				do
				{
					if (numChoice < 0 && numChoice > cards[i].getQuantity())
					{
						std::cout << "Your choice is invalid " << std::endl;
					}
					std::cout << "How many " << cards[i].getType(i) << " cards would you like to exchange? Enter the number between 1 and " << cards[i].getQuantity() << std::endl;
					std::cin >> numChoice;
				} while (numChoice < 1 && numChoice > cards[i].getQuantity());

				choices[i] = numChoice;
			}
			else
			{
				continue;
			}
		}
	}

	return choices;
}

void Player::exchangeCards(int* choices)
{
	static int numOfArmiesExchange = 5;

	for (int i = 0; i < 3; i++)
	{
		cards[i].decrementQuantity(choices[i]);
	}

	incrementArmies(numOfArmiesExchange);

	//return cards;
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

int Player::getTotalCards()
{
	return cards[0].getQuantity() + cards[1].getQuantity() + cards[2].getQuantity();
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

void Player::transferCards(Player player)
{
	if (player.getNumberOfArmies() < 1)
	{
		for (int i = 0; i < 3; i++)
		{
			int updatedNumOfArmies = cards[i].getQuantity() + player.cards[i].getQuantity();
			cards[i].setQuantity(updatedNumOfArmies);
		}
	}
}

#include "Player.h"


Player::Player(std::string aName)
{
	name = aName;
	battlesLost = 0;
	battlesWon = 0;
	numArmiesOwned = 0;
	numCountriesOwned = 0;
	isAlive = true;

	cards = new Card[3];
	for (int i = 0; i < 3; i++)
	{
		cards[i] = *new Card();
	}

}
Player::Player(){
	cards = new Card[3];
	for (int i = 0; i < 3; i++)
	{
		cards[i] = *new Card();
	}
}

Player::~Player()
{
	//delete cards;
}

void Player::setArmiesOwned(int armiesOwned){
	numArmiesOwned = armiesOwned;
}

void Player::setCountriesOwned(int countriesOwned){
	numCountriesOwned = countriesOwned;
}

std::string Player::getName(){
	return name;
}

bool Player::getIsAlive(){
	return isAlive;
}

void Player::setDeath(){
	isAlive = false;
}

void Player::setPlayerIndex(int index){
	playerIndex = index;
}

void Player::setName(std::string initialName){
	name = initialName;
}

int Player::getBattlesLost(){
	return battlesLost;
}

int Player::getBattlesWon(){
	return battlesWon;
}

int Player::getNumArmiesOwned(){
	return numArmiesOwned;
}

int Player::getNumCountriesOwned(){
	return numCountriesOwned;
}
void Player::setBattlesWon(){
	battlesWon++;
}

void Player::setBattlesLost(){
	battlesLost++;
}

int Player::getPlayerIndex(){
	return playerIndex;
}
