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
    std::cout << "Please select:\n n - start a new game\n l - load an existing game" << std::endl;
    inString = View::getString();
  }
  
  if(inString.compare("n") == 0){
    gb = new GameBuildNew();
  }
  else{    
    int inInt;
    
    do{
      std::cout << "Please input a save slot (0-9)" << std::endl;
      inInt = View::getInt();
      
    }while(!(inInt >= 0 && inInt <= 9) || !fileExists("save" +intToString(inInt) + ".msv"));
    
    gb = new GameBuildLoad(inInt);
  }
  gbd.setGameBuilder(gb);
  
  gbd.constructGame();
  game = gbd.getGame();
  
  return game->play();

}
