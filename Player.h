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
	void setBattlesWon();
	void setBattlesLost();
	bool getIsAlive();
	void setDeath();
	std::string statistics();
	void exchangeCards(int* choices);
	void addCard();
	void setHasConquered(bool mIsConquered);
	bool getHasConquered();
	Card** getCards();
	void processCardExchange();
	void incrementArmies(int incrementValue);
	void transferCards(Player * player);
	bool canExchangeCards();
	int getTotalCards();
	inline std::string getPlayerType(){return typeid(*this).name();}
private:
	bool isAlive;
	int battlesWon;
	int battlesLost;
	int playerIndex;
	int numCountriesOwned;
	int numArmiesOwned;
	//int totalPlayers = 0;
	std::string name;	
	Card** cards;
	bool hasConquered;
	//int* getExchangeChoices();
	
	//std::string playerType;
};
