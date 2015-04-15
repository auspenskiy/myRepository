#include "Player.h"

Player::Player(){
  
}

Player::~Player()
{
	delete[] cards;
}


Player::Player(std::string aName, int newPlayerIndex)
{
	name = aName;
	playerIndex = newPlayerIndex;
	battlesLost = 0;
	battlesWon = 0;
	numArmiesOwned = 0;
	numCountriesOwned = 0;
	hasConquered = false;
	isAlive = true;
	cards = new Card*[3];
	
	for (int i = 0; i < 3; i++)
	{
		cards[i] = new Card(0,i);
	}

	srand(time(0)); // This will ensure a really randomized number by help of time.
}


//holds the total number of armies of the player
void Player::setArmiesOwned(int armiesOwned){
	numArmiesOwned = armiesOwned;
}

//holds the total number of countries of the player
void Player::setCountriesOwned(int countriesOwned){
	numCountriesOwned = countriesOwned;
}

std::string Player::getName(){
	return name;
}

bool Player::getIsAlive(){
	return isAlive;
}

//set the player as dead - a player is dead when he has 0 countries
void Player::setDeath(){
	isAlive = false;
}

void Player::setPlayerIndex(int index){
	playerIndex = index;
}

void Player::setName(std::string initialName){
	name = initialName;
}

//returns number of battles lost - used for statistics
int Player::getBattlesLost(){
	return battlesLost;
}

//returns number of battles won - used for statistics
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

//checks if player is eligible to exchange cards
bool Player::canExchangeCards()
{
	int infantry = cards[0]->getQuantity();
	int cavalry = cards[1]->getQuantity();
	int artillery = cards[2]->getQuantity();

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

void Player::addCard()
{
	if (hasConquered)
	{
		int xRan;
		xRan = rand() % 3;
		cards[xRan]->incrementQuantity();
		hasConquered = false;
	}
}

//returns total number of cards
int Player::getTotalCards()
{
	return cards[0]->getQuantity() + cards[1]->getQuantity() + cards[2]->getQuantity();
}

//returns cards
Card** Player::getCards()
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

void Player::transferCards(Player * player)
{
	if (player->getNumArmiesOwned() < 1)
	{
		for (int i = 0; i < 3; i++)
		{
			int updatedNumOfArmies = cards[i]->getQuantity() + player->cards[i]->getQuantity();
			cards[i]->setQuantity(updatedNumOfArmies);
		}
	}
}


void Player::incrementArmies(int incrementValue)
{
	numCountriesOwned += incrementValue;
}

int Player::getNumOfArmiesExchange(){return numOfArmiesExchange;}

void Player::setNumOfArmiesExchange(int newNumOfArmiesExchange){numOfArmiesExchange = newNumOfArmiesExchange;}

int Player::numOfArmiesExchange = 5; //local static incremented by 5 every time the function is called by any player - the requirement to update the value is met; be careful if change it
