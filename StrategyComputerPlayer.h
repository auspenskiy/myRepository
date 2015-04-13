#pragma once
#include "StrategyPattern.h"
#include "map.h"
#include <string>

class ComputerPlayer{
private:
	StrategyPattern *strategy;
	//Map* map;
public:
	std::string name;

	ComputerPlayer(){};
	//set initial strat
	ComputerPlayer(StrategyPattern *initStrategy){
		this->strategy = initStrategy;
	}
	//set new strat
	void setStrategy(StrategyPattern *newStrategy){
		this->strategy = newStrategy;
	}

	//run strat
	void executeStrategy(std::string str){
		return this->strategy->action();
	}

	void setMap(Map* aMap){
		this->strategy->setUpMap(aMap);
	}

	void setName(std::string aName);
};