#include "continent.h"
#include <iostream>
#include <sstream>

Continent::Continent()
{
}

void Continent::addCountry(Country & newCountry){
  countries = insertElement(countries, countryCount, newCountry);
  
  //std::cout << newCountry.getName() << " added to " << name << std::endl;
}

const Country& Continent::getCountry(std::string countryName){
  return findElement(countries, countryCount, countryName);
}

bool Continent::isOwnedByPlayer(int playerIndex)const{
  for(int x = 0; x < countryCount; x++){
    if (countries[x]->getOwnerIndex() != playerIndex){
      return false;
    }
  }
  return true;
}

std::string Continent::to_string() const{
  std::ostringstream oss;
  using std::endl;
  oss << getName() << ":" << endl;
  for (int y = 0; y < getCountryCount(); y ++){
    oss << "  " << getCountries()[y]->to_string() << endl;
  }
  return oss.str();
}
