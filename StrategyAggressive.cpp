#pragma once
#include "AggressivePattern.h"
#include <iostream>
#include "country.h"
extern std::string territories[36];

void AggressivePattern::action(){
	Country target;
	int numberOfNeighbors = 0;
	cout << "COMPUTER PLAYER is currently in aggressive mode" << endl;

	//loops until it finds a target
	bool hasTarget = false;
	do{
		//pick a country to attack from in random
		int y = 0;
		
		do{
			//36 is the number of countries
			//this implementation is based on the version of the game where there were only European countries
			y = (rand() % 36);
			target = themap->getCountry(territories[y]);
		}while(themap->getCountry(territories[y]).getOwner() == "COMPUTER PLAYER");

		numberOfNeighbors = target.getNeighbourCount();

		Country** neighbors = target.getNeighbours();
		Country* compareNeighbors;

		//find a viable country to attack
		for(int counter = 0;counter < numberOfNeighbors;counter = counter+1){
			compareNeighbors = neighbors[counter];
			std::string localArmyName = compareNeighbors->getName();
			int localArmy = themap->getCountry(localArmyName).getArmies();
		
			//prints the attacking country, breaks out of the loop afterwards
			int enemyArmy = themap->getCountry(target.getName()).getArmies();
			if((compareNeighbors->getOwner() == "COMPUTER PLAYER") && (localArmy > enemyArmy)){
				cout << "COMPUTER PLAYER has " << localArmy << " armies in " << localArmyName << endl;
				cout << "You have " << enemyArmy << " armies in " << target.getName() << endl;
				cout << "COMPUTER PLAYER is using " << localArmyName << " to attack " << target.getName() << endl;
				hasTarget = true;
				return;
				} 
			}
		}while(hasTarget == false);
}
