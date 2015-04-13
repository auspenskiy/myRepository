#include "map.h"
#include <iostream>
#include <sstream>
#include <time.h>

Map::Map(int numOfCountries, Country ** newCountries, int numOfContinents, Continent ** newContinents, 
	 std::string newAuthor, std::string newImage, std::string newWrap, std::string newScroll, std::string newWarn){
  countryCount = numOfCountries;
  continentCount = numOfContinents;
  countries = newCountries;
  continents = newContinents;
  
  author = newAuthor;
  image = newImage;
  wrap = newWrap;
  scroll = newScroll;
  warn = newWarn;

  views = new std::list<Observer*>();
}

Map::~Map(){
  
  //Destruct all the countries
  for(int x = 0; x < countryCount; x++){
    delete countries[x];
  }
  delete [] countries;
  countries = NULL;
  
  //Destruct all the continents
  for(int x = 0; x < continentCount; x++){
    delete continents[x];
  }
  delete [] continents;
  continents = NULL;
  
}
/*
//retrieve a continent based on its name alone
const Continent& Map::getContinent(std::string continentName){
  return findElement(continents, continentCount, continentName);
}
*/

//Returns the number of countries owned by the given player
int Map::countCountriesOwned(int playerIndex){
  int countriesOwnedCount = 0;
  for (int x = 0; x < countryCount; x ++){
    if ( countries[x]->getOwnerIndex() == playerIndex){
      countriesOwnedCount++;
    }
  }
  return countriesOwnedCount;
}

/*
 *********This is not a map specific function and should be considered for refactoring
 */
int Map::computeContinentsBonuses(int playerIndex){
  int continentBonuses = 0;
  for (int x = 0; x < continentCount; x ++){
    if(continents[x]->isOwnedByPlayer(playerIndex) ){
      continentBonuses += continents[x]->getControlValue();
    }
  }
  return continentBonuses;
}

void Map::setPlayerArrayInMap(Player ** playerArray){
	map_playerArray = playerArray;
}

void Map::updateCountriesAndArmies(){
	for (int i = 0; i < numPlayers; i++){
		int index = map_playerArray[i]->getPlayerIndex();
		map_playerArray[i]->setCountriesOwned(countCountriesOwned(index));
		map_playerArray[i]->setArmiesOwned(countArmiesOwned(index));
	}
}

//Assigns each player to own an equal number of randomly selected countries
void Map::setupCountryOwners(int numOfPlayers)
{

	int playerIndex = 0;
	int countryIndex = 0;
	Player* player;
	srand(time(NULL));   //Allows to generate unique numbers
	
	for(int i = 0;i< countryCount;i++){
		//randomly assign a country to the player
		playerIndex = i % numOfPlayers;
		countryIndex = rand() % (countryCount);
		
		//while the country assigned to the player is already taken, assign another
		while(countries[countryIndex]->getOwnerIndex() != -1){
		  countryIndex = rand() % countryCount;
		}
		//map_playerArray[playerIndex].setCountriesOwned(1);
		countries[countryIndex]->setOwnerIndex(playerIndex);
		
	}

	numPlayers = numOfPlayers;
}

/*
//retrieve a country based on its name alone
const Country& Map::getCountry(std::string countryName){
  return findElement(countries, countryCount, countryName);   
}
*/

//IMPLEMENTING OBSERVABLE-----------------------
void Map::attach(Observer & ob){
  //push an observer to the list
  views->push_front(&ob);
}

void Map::detach(Observer & ob){
  bool found = false;
  std::list<Observer*>::iterator findIter = views->begin();
  
  //go through the list of all the observers looking for the given one
  do{
      if (*findIter == &ob){found = true;}
  }while(findIter++ != views->end() && found == false);
  
  //if the given observer is found, remove it from the list
  if(found){
    views->erase(findIter);
  } 
}

void Map::notify(){
  std::list<Observer *>::iterator i = views->begin();

  //go through the list of all attached observers and notify them
  for (; i != views->end(); ++i){
    (*i)->update();
  }
}

//get a list of all neighbours of a country who do not belong to the owner of that country
std::list<std::string> Map::getEnemyNeighbours(std::string &countryName, int playerIndex){
  std::list<std::string> enemyNeighbourList;
  
  Country attackingCountry = findElement(countries, countryCount, countryName);
  
  if(&attackingCountry != NULL){
    //for every neighbouring country, check if the owner is the same as the given owner
    for(int x = 0; x < attackingCountry.getNeighbourCount(); x++){
      //if the owners are not the same, add that neighbour to the list of enemy countries
      if(attackingCountry.getAllNeighbours()[x]->getOwnerIndex() != attackingCountry.getOwnerIndex()){
	enemyNeighbourList.push_front(attackingCountry.getAllNeighbours()[x]->getName());
      } 
    }
  }
  return enemyNeighbourList;
}

//COUNTRY CONNECTION FUNCTIONS---------------------------------------------------
//recursively searches for any friendly neighbouring countries (and any of their friendly neightbours) and add them to the list parameter
void Map::recursiveGetConnectedFriendlyCountries(const Country &startCountry, int playerIndex, std::list<std::string> &connectedCountryList){
  //the the current country to the list
  connectedCountryList.push_front(startCountry.getName());
  //for every neighbour of the country
  for (int x = 0; x < startCountry.getNeighbourCount(); x++){
    //if that neighbour is friendly and not already in the list call the function on them
    if (startCountry.getAllNeighbours()[x]->getOwnerIndex() == playerIndex 
      && !listContains(connectedCountryList, startCountry.getAllNeighbours()[x]->getName())){
      recursiveGetConnectedFriendlyCountries(*startCountry.getAllNeighbours()[x], playerIndex, connectedCountryList);
    }
  }  
}

//recursively find all friendly countries connected to the given country
std::list<std::string> Map::getConnectedFriendlyCountries(std::string &startCountry, int playerIndex){
  std::list<std::string> connectedCountryList;
  
  Country startCountryObject = findElement(countries, countryCount, startCountry);
  
  //simply call the private recursive country search algorithm
  if (&startCountryObject != NULL){  
    recursiveGetConnectedFriendlyCountries(startCountryObject, playerIndex, connectedCountryList);
  }
  
  //return everything found by the recursive search function
  return connectedCountryList;
  
}




//COUNTRY ACCESSORS & MUTATORS---------------------------------------------------
int Map::setCountryArmies(std::string countryName, int numOfArmies, bool updateMap){
  //if the country exists
  if (countryExists(countryName)){
    //get the actual country object and update it
    findElement(countries, countryCount, countryName).setArmies(numOfArmies);

    //if the action doesn't have view updates disabled
    if (updateMap){
      //update all relevant observers of the change to the model
      notify();
    }
    return 1;
  }
  return -1;
}

int Map::setCountryOwnerIndex(std::string countryName, int playerIndex, bool updateMap){
  //if the country actually exists
  if (countryExists(countryName)){
	  
    //update the country object's owner
    findElement(countries, countryCount, countryName).setOwnerIndex(playerIndex);
    //if the action doesn't have view updates disabled
    if (updateMap){
      //update all relevant observers of the change to the model
      notify();
    }
    return 1;
  }
  return -1; 
}

//simple accessor.  Finds the country and returns its number of armies
int Map::getCountryArmies(std::string countryName){
 if (countryExists(countryName)){
    return findElement(countries, countryCount, countryName).getArmies();
  }
  return -1;  
}

//counts total armies for a given player
int Map::countArmiesOwned(int playerIndex){
	int armiesOwnedCount = 0;
	for (int x = 0; x < countryCount; x++){
		if (countries[x]->getOwnerIndex() == playerIndex){
			armiesOwnedCount += countries[x]->getArmies();
		}
	}
	return armiesOwnedCount;
}

//simple accessor.  Finds the country and returns its owner
int Map::getCountryOwnerIndex(std::string countryName){
  if (countryExists(countryName)){
    return findElement(countries, countryCount, countryName).getOwnerIndex();
  }
  return -1;  
}

//simple accessor, returns true is the country exists on the map
bool Map::countryExists(std::string countryName){return &(findElement(countries, countryCount, countryName)) != NULL;}
  
  //returns a string representation of the map
std::string Map::to_string() const {
  std::ostringstream oss;
  for (int x = 0; x < continentCount; x++){
    oss << continents[x]->to_string();
  }
  return oss.str();
} 