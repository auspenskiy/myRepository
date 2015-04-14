#pragma once
#include <string>
#include "country.h"
#include "Card.h"
#include <typeinfo>
#include "View.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "map.h"

class Map;

class Player{
public:
	Player();
	Player(std::string aName, int newPlayerIndex);
	~Player();
	
	//functions to simulate AI behavior
	virtual int chooseAction(Map * gameMap)=0;
	
	virtual std::string chooseCountryToReinforce(Map * gameMap, int maxNumOfReinforcements)=0;
	virtual int chooseNumberToReinforce(Map * gameMap, int maxNumOfReinforcements)=0;
	
	virtual std::string chooseSourceFortificationCountry(Map * gameMap)=0;
	virtual std::string chooseDestinationFortificationCountry(Map * gameMap, std::list<std::string> & connectedCountries)=0;
	virtual int chooseNumberOfFortificationArmies(Map * gameMap)=0;
	
	virtual std::string chooseAttackingCountry(Map * gameMap)=0;
	virtual std::string chooseDefendingCountry(Map * gameMap)=0;
	virtual bool chooseContinueAttack(Map * gameMap)=0;
	virtual int chooseNumberOfConsolidationArmies(Map * gameMap, int minConsolidationArmies, int maxConsolidationArmies)=0;
	
	//ACCESSORS
	void setName(std::string);
	std::string getName();
	void setPlayerIndex(int index);
	void setArmiesOwned(int armiesOwned);
	void setCountriesOwned(int countriesOwned);
	void setBattlesWon();
	void setBattlesLost();
	void setDeath();
	void setHasConquered(bool mIsConquered);
	void incrementArmies(int incrementValue);

	//MUTATORS
	int getBattlesWon();
	int getBattlesLost();
	int getNumCountriesOwned();
	int getNumArmiesOwned();
	int getTotalCards();
	int getPlayerIndex();
	Card** getCards();
	bool getIsAlive();
	inline std::string getPlayerType(){return typeid(*this).name();}
	bool getHasConquered();

	//CARD FUNCTIONS
	void exchangeCards(int* choices);
	void addCard();
	void processCardExchange();
	void transferCards(Player * player);
	bool canExchangeCards();
	
	
private:
	bool isAlive;
	int battlesWon;
	int battlesLost;
	int playerIndex;
	int numCountriesOwned;
	int numArmiesOwned;
	std::string name;	
	Card** cards;
	bool hasConquered;
};
