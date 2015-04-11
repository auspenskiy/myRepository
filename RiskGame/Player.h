#pragma once
#include <string>

class Player{
public:
	Player(std::string aName);
	~Player();
	void setName(std::string);
	std::string getName();
	void setPlayerIndex(int index);
	int getBattlesWon();
	int getBattlesLost();
	int getNumCountriesOwned();
	int getNumArmiesOwned();
private:
	int battlesWon;
	int battlesLost;
	int playerIndex;
	int numCountriesOwned;
	int numArmiesOwned;
	std::string name;
};

