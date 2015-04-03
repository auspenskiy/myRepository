#include "Player.h"


Player::Player(std::string aName)
{
	name = aName;
	battlesLost = 0;
	battlesWon = 0;
	numArmiesOwned = 0;
	numCountriesOwned = 0;
}
Player::Player(){
}

Player::~Player()
{
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
void Player::setBattlesWon(int victories){
	battlesWon = victories;
}

void Player::setBattlesLost(int defeats){
	battlesLost = defeats;
}

int Player::getPlayerIndex(){
	return playerIndex;
}