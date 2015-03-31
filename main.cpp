#include <iostream>
#include <string>
#include "game.h"
#include "player.h"


int getNumberOfPlayers(){
  using std::cin;
  
  Controller controller;
  int numOfPlayers = 0;
  std::cout << "How many people are playing? " << std::endl;
  numOfPlayers = controller.getInt();
    
  return numOfPlayers;

}

//create the player objects and give them countries at random
/*std::string * createPlayers(int numOfPlayers){

	 std::string * playerNameArray = new std::string[numOfPlayers];
	Player ** playerArray = new Player*[numOfPlayers];

	std::cin.ignore(256,'\n'); //clears input buffer
	for(int a = 0; a < numOfPlayers; a = a + 1 )
		{
		std::cout << "What is the name of player " << a << "?" << std::endl;
		getline( std::cin, playerNameArray[a]);
		Player* player = new Player(playerNameArray[a]);
		player->setPlayerIndex(a);
		*playerArray[a] = *player;
		//playerArray[a]->setPlayerIndex(a);
	}
	Player * p = new Player();
	*p->playersArray = **playerArray;

	return playerNameArray;
	
}
*/
//create the player objects and give them countries at random
Player * createPlayerArray(int numOfPlayers){

	std::string * playerNameArray = new std::string[numOfPlayers];
	Player * playerArray = new Player[numOfPlayers];

	std::cin.ignore(256, '\n'); //clears input buffer
	for (int a = 0; a < numOfPlayers; a = a + 1)
	{
		std::cout << "What is the name of player " << a << "?" << std::endl;
		getline(std::cin, playerNameArray[a]);
		Player* player = new Player(playerNameArray[a]);
		player->setPlayerIndex(a);
		playerArray[a] = *player;
		//playerArray[a]->setPlayerIndex(a);
	}
	//Player * p = new Player();
	//*p->playersArray = **playerArray;
	//cout << "IT REACHES CREATEPLAYAARRAY";
	return playerArray;

}

int main(){
  
  int numOfPlayers = getNumberOfPlayers();  
  
  Game * game = new Game(numOfPlayers, createPlayerArray(numOfPlayers));
  
  return game->play();

}
