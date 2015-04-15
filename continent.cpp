#include "continent.h"
#include <iostream>
#include <sstream>

Continent::Continent()
{
	countryCount = 0;
}

//inserts a country into the continent's country array
void Continent::addCountry(Country & newCountry){
  countries = insertElement(countries, countryCount, newCountry);
}

//finds a country from the continent's country array based on its string name
const Country& Continent::getCountry(std::string countryName){
  return findElement(countries, countryCount, countryName);
}

//returns true if every country in the continent is owned by the given player
//used for calculating bonus armies
bool Continent::isOwnedByPlayer(int playerIndex)const{
  for(int x = 0; x < countryCount; x++){
    if (countries[x]->getOwnerIndex() != playerIndex){
      return false;
    }
  }
  return true;
}

//returns string representation of the continent
std::string Continent::to_string() const{
  std::ostringstream oss;
  using std::endl;
  oss << getName() << ":" << endl;
  for (int y = 0; y < getCountryCount(); y ++){
    oss << "  " << getCountries()[y]->to_string() << endl;
  }
  return oss.str();
}
