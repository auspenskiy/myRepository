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
	void setBattlesWon(int victories);
	void setBattlesLost(int defeats);
	//virtual void statistics();
private:
	int battlesWon;
	int battlesLost;
	int playerIndex;
	int numCountriesOwned;
	int numArmiesOwned;
	int totalPlayers = 0;
	std::string name;
};
