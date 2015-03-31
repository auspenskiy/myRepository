#include "Player.h"


Player::Player(std::string aName)
{
	name = aName;
	battlesLost = 0;
	battlesWon = 0;
	numArmiesOwned = 0;
	numCountriesOwned = 0;
}

Player::~Player()
{
}

std::string Player::getName(){
	return name;
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