#pragma once
#include <string>
#include "country.h"
#include "Card.h"

class Player{
public:
	inline Player(){}
	Player(std::string aName, int newPlayerIndex);
	~Player();
	
	/*
	virtual std::string chooseCountryToReinforce()=0;
	virtual int chooseNumberToReinforce()=0;
	
	virtual std::string chooseSourceFortificationCountry()=0;
	virtual std::string chooseDestinationFortificationCountry()=0;
	virtual int chooseNumberOfFortificationArmies()=0;
	
	virtual std::string chooseAttackingCountry()=0;
	virtual std::string chooseDefendingCountry()=0;
	virtual bool chooseContinueAttack()=0;
	*/
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
	inline bool getIsHuman(){return isHuman;}
private:
	bool isAlive;
	bool isHuman;
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
};
