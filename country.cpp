#include "country.h"
#include <sstream>
#include <iostream>

Country::Country(std::string cName, Continent & setContinent, int newX, int newY){
  name = cName;
  myContinent = &setContinent;
  xCoord = newX;
  yCoord = newY;
  
  neighbourCount = 0;
  ownerIndex = -1;
  armies = 2;
  
    myContinent->addCountry(*this);
}

/*
 * Adds countries to an array which represents all the countries connected to this country
 * 
 * By default, it will make a two-way link between countries unless "unidirectional" is set to true
 */
void Country::addNeighbour(Country & newNeighbour, bool unidirectional){
  addNeighbourLink(newNeighbour);
  
  if (!unidirectional){
    newNeighbour.addNeighbourLink(*this);
  }
  
  //std::cout << this->getName() << " connected to "<< newNeighbour.getName() << std::endl;
}

//ACCESSORS------------------------------------
const Country * Country::getNeighbour(std::string countryName) {
  return & (findElement(neighbours, neighbourCount, countryName));
}

bool Country::isNeighbour(std::string countryName) {
  return &(findElement(neighbours, neighbourCount, countryName)) != NULL;
}

//MUTATORS------------------------------------
void Country::setOwnerIndex(int newOwnerIndex){ownerIndex = newOwnerIndex;}
void Country::setArmies(int newArmies){armies = newArmies;}

//PRIVATE FUNCTIONS---------------------------
/*
 * Creates a link between two countries, by adding "newNeighbour" to a country's "neighbours" array
 * This function is used to enable one class to call another to get the other to add the first one to itself.
 * 
 * Post: newNeighbour is added to neighbours in alphabetical order by name.
 */

void Country::addNeighbourLink(Country &newNeighbour){
  this->neighbours = insertElement(this->neighbours, this->neighbourCount, newNeighbour);
  //std::cout << newNeighbour.getName() << " connected to " << this->getName() << std::endl;
}

//returns a string representation of the country.
std::string Country::to_string() const{
  std::ostringstream oss;
  oss << name << " : player "  << ownerIndex <<" : " <<  armies << " armies" << " : Connected to " ;
  if(neighbourCount == 0){
  oss << "no one.";  
  }
  else{
    for (int x = 0; x < neighbourCount; x++){
      oss << neighbours[x]->getName();
      if (x < neighbourCount - 1){
	oss << ", ";
      }
      
    }
  }
  return oss.str();
}