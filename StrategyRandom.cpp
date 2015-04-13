#pragma once
#include "RandomPattern.h"
#include <iostream>

extern std::string territories[36];

void RandomPattern::action(){	
	cout << "COMPUTER PLAYER is currently in random mode" << endl;
	//coin toss to see if computer wants to attack
	srand(time(NULL));
    int x = (rand() % 2);
	if(x == 0){
		computerAttack();	
	}
	else{
		cout << "COMPUTER PLAYER does nothing..for now" << endl;
	}
}

void RandomPattern::computerAttack(){
	Country target;
	Country *attackingCountry = new Country;
	int numberOfNeighbors = 0;
	//pick a country at random, the country must not be from the computer
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

		//find a valid adjacent country that is owned by the computer
		bool hasTarget = false;
		for(int counter = 0;counter < numberOfNeighbors;counter = counter+1){
		compareNeighbors = neighbors[counter];

		
		if(compareNeighbors->getOwner() == "COMPUTER PLAYER"){
			attackingCountry = compareNeighbors;
			hasTarget = true;
			} 
		}
		

		if(hasTarget){
			cout << "COMPUTER PLAYER is using " << attackingCountry->getName() << " to attack " << target.getName() << endl;
		}
}