#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>
#include "map.h"

class Map;
class Player;

class View{
public:
  static std::string getString();
  static int getInt();
  static void inform(std::string msg);
  static void prompt(std::string msg);
  static void outputCountryList(std::list<std::string> countryList);
  static bool putCountryExistsAndFriendly(std::string country, int currentPlayerIndex, Map * map);
};