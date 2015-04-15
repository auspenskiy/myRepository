#pragma once
#include "observer.h"
#include "map.h"
#include "View.h"
#include <sstream>

class Map; //forward declaration

/*
Class TextView: Implementation of Map Observer Pattern
	Used to observe and output updates of the map class
*/
class TextView : public Observer{
public:
  inline TextView(){};
  TextView(Map & newMap);
  ~TextView();
  void update();

private:
  Map * m;
};