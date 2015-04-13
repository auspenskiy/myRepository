#pragma once
#include "StrategyPattern.h"

class RandomPattern : public StrategyPattern 
{
public:
	RandomPattern(Map* amap){this->themap = amap;};
	void action();
	void putMap(Map* aMap){this->themap = aMap;};
	void computerAttack();
private:
	Map* themap;
};