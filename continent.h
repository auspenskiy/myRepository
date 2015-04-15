#pragma once

#include "country.h"
#include <string>
#include <sstream>
class Country; //forward declaration needed due to circular dependancy between Continent and Country;

/*
Class Contient: A collection of te data related to a continent in the map
	Considered part of the model
*/
class Continent{
public:
  Continent();
  
  //!!!should be added as an initialization parameter with country count and removed from here
  void addCountry(Country& newCountry);
  
  const Country& getCountry(std::string countryName);
  bool isOwnedByPlayer(int playerIndex) const;
  
//ACCESSORS-------------------------------------  
  inline int getControlValue() const {return controlValue;}
  inline Country const*const* getCountries() const {return countries;}
  inline int getCountryCount() const {return countryCount;}
  inline const std::string getName()const {return name;}
 
  std::string to_string() const;
  
//MUTATORS-------------------------------------
  inline void setControlValue(int newControlValue){controlValue = newControlValue;}
  inline void setName(std::string cContName){name = cContName;}
  
private:
  int countryCount;
  Country ** countries;
  std::string name;
  int controlValue;
    
};

std::ostream& operator<<(std::ostream& os, Continent & outputContinent);