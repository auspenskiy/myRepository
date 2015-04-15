#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include "Player.h"
#include "GameBuilder.h"
#include "GameBuilderDirector.h"
#include "GameBuildNew.h"
#include "GameBuildLoad.h"
#include "textview.h"
#include "game_utils.h"
#include "View.h"


int main(){
  
  std::string inString = "";
  GameBuilderDirector gbd;
  GameBuilder * gb;
  Game * game;

  while (inString.compare("n") != 0 && inString.compare("l") != 0){
    View::inform("Please select:\n n - start a new game\n l - load an existing game");
    inString = View::getString();
  }
  
  if(inString.compare("n") == 0){
    gb = new GameBuildNew();
  }
  else{    
    int inInt;
	int savedFiles = 0;

	//checks if there are any saved games
	for(int i = 0;i<10;i++){
		if(fileExists("save"+intToString(i)+ ".msv"))
		{
			View::inform("Saved game in slot " + intToString(i) + " is ready to be loaded.");
			savedFiles++;
		}
	}
	//if there are no saved games, start a new one
    if(savedFiles == 0){
		View::inform("No saved game detected");
		View::inform("Starting new game..");
		gb = new GameBuildNew();	 
	}
	else{
		do{
			View::inform("Please input a save slot (0-9)");
			inInt = View::getInt();      
		}while(!(inInt >= 0 && inInt <= 9) || !fileExists("save" +intToString(inInt) + ".msv"));
		gb = new GameBuildLoad(inInt);
	}
  }


  gbd.setGameBuilder(gb);
  
  gbd.constructGame();
  game = gbd.getGame();
  
  return game->play();

}
