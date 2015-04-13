#pragma once
#include "observer.h"
#include "map.h"
#include "View.h"
#include <sstream>

class Map; //forward declaration

class TextView : public Observer{
public:
  inline TextView(){};
  TextView(Map & newMap);
  ~TextView();
  void update();

private:
  Map * m;
};