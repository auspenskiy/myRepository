#include "GameBuilderDirector.h"

  GameBuilderDirector::GameBuilderDirector(){
  }

void GameBuilderDirector::setGameBuilder(GameBuilder * gb){
  gameBuilderUsed = gb;
}

Game * GameBuilderDirector::getGame()
{
  return gameBuilderUsed->getResult();
}

void GameBuilderDirector::constructGame(){
  gameBuilderUsed->buildMap();
  gameBuilderUsed->buildPlayers();
  gameBuilderUsed->buildGameState();
}
