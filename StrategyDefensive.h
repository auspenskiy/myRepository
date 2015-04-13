#pragma once
#include "StrategyPattern.h"

class DefensivePattern : public StrategyPattern{
public:
	DefensivePattern(Map* amap){this->themap = amap;};
	void action();
private:
	Map* themap;
};