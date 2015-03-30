#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

#include "game.h"

int getNumberOfPlayers(){
  using std::cin;
  
  
  Controller controller;
  int numOfPlayers = 0;
  
  std::cout << "How many people are playing? " << std::endl;
  numOfPlayers = controller.getInt();
    
  return numOfPlayers;

}

//create the player objects and give them countries at random
Player* createPlayers(int numOfPlayers)
{
	Player* playerArray = new Player[numOfPlayers];
	
	std::cin.ignore(256,'\n'); //clears input buffer
	for(int a = 0; a < numOfPlayers; a = a + 1 )
	{
		std::cout << "What is the name of player " << a << "?" << std::endl;
		string name;
		getline(std::cin, name);
		playerArray[a].setName(name);
	}
	return playerArray;
}


int main(){
  
  int numOfPlayers = getNumberOfPlayers();  
  
  Game * game = new Game(numOfPlayers, createPlayers(numOfPlayers));
  
  return game->play();

}
