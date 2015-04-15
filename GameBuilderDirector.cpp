#include "GameBuilderDirector.h"

  GameBuilderDirector::GameBuilderDirector(){
  }

//save the initialized polymorphic builder object
void GameBuilderDirector::setGameBuilder(GameBuilder * gb){
  gameBuilderUsed = gb;
}

//return the built game
Game * GameBuilderDirector::getGame()
{
  return gameBuilderUsed->getResult();
}

//execute the game builder functions
void GameBuilderDirector::constructGame(){
  gameBuilderUsed->buildMap();
  gameBuilderUsed->buildPlayers();
  gameBuilderUsed->buildGameState();
}
