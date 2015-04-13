#pragma once
#include "DefensivePattern.h"
#include "country.h"
#include <iostream>
extern std::string territories[36];

void DefensivePattern::action(){
	cout << "COMPUTER PLAYER is currently in defensive mode" << endl;
	Country* target;
	Country currentCountry;
	Country* currentNeighbor;
	int numberOfNeighbors = 0;
	bool hasTarget = false;
	int localArmy = 0;
	int enemyArmy = 0;

	//selectedLocalArmy and selectedEnemyArmy differs from localArmy and enemyArmy. The selected variables hold the number of armies
	//for the countries that will do the actual attacking and defending
	int selectedLocalArmy = 0;
	int selectedEnemyArmy = 0;
	int numberOfEnemies = 0;
	//find a country which it is surrounded by weaker enemy neighbors
	for(int i = 0; i < themap->getCountryCount();i++){
		currentCountry = themap->getCountry(territories[i]);
		numberOfNeighbors = currentCountry.getNeighbourCount();
		Country** neighbors = currentCountry.getNeighbours();

		//counts the number of enemies
		for(int i = 0;i < numberOfNeighbors;i = i+1){
			currentNeighbor = neighbors[i];
			if(currentNeighbor->getOwner() != "COMPUTER PLAYER"){
				numberOfEnemies++;
			}
		}


		if(currentCountry.getOwner() == "COMPUTER PLAYER"){
			int numOfWeakerEnemies = 0;

			for(int counter = 0;counter < numberOfNeighbors;counter = counter+1){
			currentNeighbor = neighbors[counter];
			localArmy = currentCountry.getArmies();
			enemyArmy = currentNeighbor->getArmies();

			//counts the enemy of weaker enemies
			if((currentNeighbor->getOwner() != "COMPUTER PLAYER") && (localArmy > enemyArmy)){
				selectedLocalArmy = localArmy;
				selectedEnemyArmy = enemyArmy;
				target = currentNeighbor;
				numOfWeakerEnemies++;
				//hasTarget = true;
				//break;
				} 
			}
			//if number of weaker enemies = number of enemies, computer will attack
			if(numOfWeakerEnemies == numberOfEnemies){
				hasTarget = true;
				break;
			}
		}
	}
	
	//attack only if there's a target
	if(hasTarget){	
		cout << "COMPUTER PLAYER has "<< selectedLocalArmy << " in " << currentCountry.getName() << endl;
		cout << "You have "<< selectedEnemyArmy << " in " << target->getName() << endl;
		cout << "COMPUTER PLAYER is using " << currentCountry.getName() << " to attack " << target->getName() << endl;
	}
	else{
		//outputs message if no country is surrended by weaker enemy countries
		cout << "COMPUTER PLAYER did not find a suitable target" << endl;
	}
}
