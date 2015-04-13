#pragma once
#include "StrategyPattern.h"

class AggressivePattern : public StrategyPattern
{
public:
	AggressivePattern(Map* amap){this->themap = amap;};
	void action();
private:
	Map* themap;
};