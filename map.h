#pragma once

#include <string>
#include <list>
#include <cstdlib>
#include "country.h"
#include "continent.h"
#include "observable.h"
#include "game_utils.h"
#include "Player.h"

class MapView;

class Map: public Observable{
public:
  Map(int numOfCountries, Country ** newCountries, int numOfContinents, Continent ** newContinents, 
	 std::string newAuthor, std::string newImage, std::string newWrap, std::string newScroll, std::string newWarn);
  ~Map();
  
  //MAP LOADING RELATED FUNCTIONS---------------------------------------
  void setupCountryOwners(int numOfPlayers);
  void setPlayerArrayInMap(Player ** playerArray);
  
  //MAIN GAME USED FUNCTIONS-------------------------------------------
  int countCountriesOwned(int playerIndex);
  int countArmiesOwned(int playerIndex);
  int computeContinentsBonuses(int playerIndex);

  void updateCountriesAndArmies();

  std::list<std::string> getEnemyNeighbours(std::string &countryName, int playerIndex);
  std::list<std::string> getConnectedFriendlyCountries(std::string &startCountry, int playerIndex);
  
//STRING BASED "SAFETY COUNTRY ACCESSORS & MUTATORS---------------------------------------------------
  int setCountryArmies(std::string countryName, int numOfArmies, bool updateMap = true);
  int setCountryOwnerIndex(std::string countryName, int playerIndex, bool updateMap = true);
  int getCountryArmies(std::string countryName);
  int getCountryOwnerIndex(std::string countryName);
  bool countryExists(std::string countryName);

//IMPLEMENTING OBSERVABLE FUNCTIONS-----------------------
  void attach(Observer & ob);
  void detach(Observer & ob);
  void notify();
  
//INPUT AND OUTPUT OF THE MAP-------------------------------
  std::string to_string() const;

//CONST ACCESSORS-------------------------------
  inline int getCountryCount() const {return countryCount;}
  inline Country const* const* getCountries() const { return countries;}
  inline int getContinentCount() const {return continentCount;}
  inline Continent const* const* getContinents() const { return continents;}

//CONST ACCESSORS OF MAP IO ATTRIBUTES------------------------------- 
  inline const std::string getAuthor()const {return author;}
  inline const std::string getImage()const {return image;}
  inline const std::string getWrap()const {return wrap;}
  inline const std::string getScroll()const {return scroll;}
  inline const std::string getWarn()const {return warn;}
  
private:
 
  //getConnectedFriendlyCountries HELPER FUNCTIONS---------------------------------------------------
  void recursiveGetConnectedFriendlyCountries(const Country &startCountry, int playerIndex, std::list<std::string> &connectedCountryList);
  
  //!!!I don't think these are needed anymore
  //MAP SETUP HELPER FUNCTIONS------------------------------------------
  /*
  Continent& getContinent(std::string continentName);
  Country& getCountry(std::string countryName);
  */

  //PRIVATE ATTRIBUTES-------------------------------------------------  
  int countryCount;
  int continentCount;
  Country ** countries;
  Continent ** continents;
  std::list<Observer*> * views;
  Player ** map_playerArray;
  int numPlayers;
  
  //PRIVATE ATTRIBUTES FROM MAP IO-------------------------------------------------  
  	std::string author;
	std::string image;
	std::string wrap;
	std::string scroll;
	std::string warn;
};