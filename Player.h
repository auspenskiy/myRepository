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

/*
Class Player: Virtual class that sets the parent class in the player stategy pattern.
	Holds all info relating to players and the virtual functions for all their behaviours
*/
class Player{
public:
	Player();
	Player(std::string aName, int newPlayerIndex);
	~Player();

//VIRTUAL FUNCTIONS USED IN STRATEGY PATTERN-----------------------------------------------------
	
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
	virtual bool chooseExchangeCards(Map * gameMap)=0;
	
//COMMON PLAYER FUNCTIONS-----------------------------------------------------
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
	int getTotalCards();
	bool canExchangeCards();
	inline std::string getPlayerType(){return typeid(*this).name();}
	static int getNumOfArmiesExchange();
	static void setNumOfArmiesExchange(int newNumOfArmiesExchange);

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
<<<<<<< HEAD
	static int numOfArmiesExchange;

=======
>>>>>>> 6485d835a9a9f45568a02f03c64cc076ec13cb15
};
