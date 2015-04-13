#pragma once

#include <string>
#include <iostream>
#include "map.h"
#include <time.h>
using std::cout;
using std::cin;
using std::endl;
class StrategyPattern{
protected:
	Map* map;
public:
	void setUpMap(Map* aMap){map = aMap;};
	virtual void action() = 0;
};
#endif