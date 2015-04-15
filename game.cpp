#include "game.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include "GameBuilderDirector.h"
#include "GameBuildSave.h"

//Main constructor for the game class
Game::Game(int newNumOfPlayers, Player ** playaArray, Map * newMap, int newPlayerTurns, int newPlayerIndex, int newBonusArmies, bool newJustLoaded, int numOfExchangeArmies){
	numOfPlayers = newNumOfPlayers;
	playerTurns = newPlayerTurns;
	playerIndex = newPlayerIndex;
	bonusArmies = newBonusArmies;
	justLoaded = newJustLoaded;
	
	playerArray = playaArray;
	playerArray[0]->setNumOfArmiesExchange(numOfExchangeArmies);
	
	totalBattles = 0;
	playersAlive = 0;
	
	for(int x = 0; x < newNumOfPlayers; x++){
	    totalBattles += playerArray[x]->getBattlesLost();
	    playersAlive += (int)playerArray[x]->getIsAlive();
	}
	
	map = newMap;
	
	if(!justLoaded){
	  map->setupCountryOwners(numOfPlayers);
	}
	map->setPlayerArrayInMap(playerArray);
	mapView = new TextView(*map);
	dice = new Dice();

}

Game::~Game(){
	delete map;
	delete mapView;
	delete dice;
	delete[] playerNames;
	delete[] playerArray;
}

//main loop of the game
int Game::play(){
	int choice;
	bool turnIsOver = false;
	std::string attackingCountry;
	std::string defendingCountry;
	//Main Game Loop
	
	do{
		currentPlayer = playerArray[playerIndex];
		turnIsOver = false;

		
		if (currentPlayer->getIsAlive()){
			map->notify();

			View::inform("Round " + intToString(playerTurns / numOfPlayers + 1) + " : " + currentPlayer->getName() + " (player " + intToString(playerIndex + 1) + ")'s turn");

			//reinforce, attack and move are the 3 actions a given player can do during his turn
			reinforce(playerIndex);
			
			do{
				
			  choice = currentPlayer->chooseAction(getMap());

				//used to open file for editing
				std::string path;
				std::string command = "Start notepad ";
				std::string appended;
				const char * c = NULL;

				switch (choice){
				case 0:
					turnIsOver = true;
					handleCards(playerIndex);
					break;
				case 1:
					attackingCountry = currentPlayer->chooseAttackingCountry(getMap());
					defendingCountry = currentPlayer->chooseDefendingCountry(getMap());
					battle(attackingCountry, defendingCountry);
					break;
				case 2:
					fortify(playerIndex);
					turnIsOver = true;
					break;
				case 3:
					map->notify();					
					break;
				case 4:
					map->updateCountriesAndArmies();
					displayStatistics();
					break;
				case 5:				
					View::inform("Type in the file you want to edit");
					path = View::getString();
					appended = command.append(path);
					c = appended.c_str();
					//system(c) is equivalent to system("Start notepad" + filePath);
					system(c);
					break;
				case 6:
					saveGame();
					break;
				case 7:
					return 0;
					break;

				default:
					View::inform("Invalid input");
				}
			} while (!turnIsOver);
		}

		playerTurns++;
		playerIndex = playerTurns % numOfPlayers;
	} while (playersAlive > 1);

	//if a player wins, find that player
	Player* winner = findWinner();
	View::inform("The winner is " + winner->getName());
	View::inform("(Enter any key to exit the game)");
	View::getString();


	return 0;
}

//returns number of players alive.  Helper function for determining if the game is over
int Game::countPlayersAlive(){
	int alive = 0;
	for (int x = 0; x < numOfPlayers; x++){
		if (playerArray[x]->getIsAlive()){
			alive++;
		}
	}
	return alive;
}

//returns a player if that player is the only one left alive
Player* Game::findWinner(){
	Player *p = NULL;
	for (int x = 0; x < numOfPlayers; x++){
		if (playerArray[x]->getIsAlive()){
			p = playerArray[x];
		}
	}
	return p;
}

//Executes all the game logic for the fortification/move process
void Game::fortify(int playerIndex){  
  std::string sourceCountry;
  std::string destinationCountry;
  std::list<std::string> lst;
  int numToMove;
  
  sourceCountry = currentPlayer->chooseSourceFortificationCountry(getMap());
  
  lst = map->getConnectedFriendlyCountries(sourceCountry, playerIndex);
  
  if (lst.size() > 1){
    destinationCountry = currentPlayer->chooseDestinationFortificationCountry(getMap(), lst);
    
    if (listContains(lst, destinationCountry) && destinationCountry.compare(sourceCountry) != 0){
      
      numToMove = currentPlayer->chooseNumberOfFortificationArmies(getMap());
      
      if (numToMove > 1 && numToMove < map->getCountryArmies(sourceCountry) - 1){ 
		map->setCountryArmies(sourceCountry, map->getCountryArmies(sourceCountry) - numToMove, false);
		map->setCountryArmies(destinationCountry, map->getCountryArmies(destinationCountry) + numToMove);
		View::inform(intToString(numToMove) + " armies moved from " + sourceCountry + " to " + destinationCountry + ".");
      }
    }
  }
}

//executes all the game logic for converting cards into bonus armies
int Game::getCardsExchange(int playerNum)
{
	bool doExchange = false;
	int armiesAdded = 0;	

	do{
		int infantry = playerArray[playerNum]->getCards()[0]->getQuantity();
		int cavalry = playerArray[playerNum]->getCards()[1]->getQuantity();
		int artillery = playerArray[playerNum]->getCards()[2]->getQuantity();
		

		std::cout << "You have " << infantry << " infantry cards, " << cavalry << " cavalry cards, and " << artillery << " artillery cards" << std::endl;
		if (playerArray[playerNum]->canExchangeCards()){
			
		

			if (infantry + cavalry+artillery >= 5){
				doExchange = true;
				View::inform("You have " + intToString(infantry + cavalry+artillery) + " cards and must trade in 3.");
			}else{
				doExchange = playerArray[playerNum]->chooseExchangeCards(getMap());
			}

			if (doExchange){
				if (infantry > 0 && cavalry > 0 && artillery > 0){
					playerArray[playerNum]->getCards()[0]->decrementQuantity(1);
					playerArray[playerNum]->getCards()[1]->decrementQuantity(1);
					playerArray[playerNum]->getCards()[2]->decrementQuantity(1);
				}else if (infantry > 2){
					playerArray[playerNum]->getCards()[0]->decrementQuantity(3);

				}else if (cavalry > 2){
					playerArray[playerNum]->getCards()[1]->decrementQuantity(3);

				}else if (artillery > 2){
					playerArray[playerNum]->getCards()[2]->decrementQuantity(3);

				}
				std::cout << "You now have " << playerArray[playerNum]->getCards()[0]->getQuantity() << " infantry cards, " << playerArray[playerNum]->getCards()[1]->getQuantity() << " cavalry cards, and " << playerArray[playerNum]->getCards()[2]->getQuantity() << " artillery cards" << std::endl;
				armiesAdded += playerArray[playerNum]->getNumOfArmiesExchange();
				playerArray[playerNum]->setNumOfArmiesExchange(playerArray[playerNum]->getNumOfArmiesExchange() + 5);
			}
		}
	}while(doExchange && playerArray[playerNum]->canExchangeCards());
	if (armiesAdded > 0){
		View::inform(playerArray[playerNum]->getName() + " has exchanged cards for " + intToString(armiesAdded) + " bonus armies.");
	}
	return armiesAdded;
}

//executes all the game logic for calculating and deploying bonus "reinforcement" armies at the start of the turn
void Game::reinforce(int playerNum){
  int numToReinforce = 0;
  std::string countryToReinforce;
  
  if (!justLoaded){
    bonusArmies = 0;
    //calculate # of reinforcements
    bonusArmies = map->computeContinentsBonuses(playerNum);
    bonusArmies += map->countCountriesOwned(playerNum) / 3;
    bonusArmies += getCardsExchange(playerNum);
  }
  else{
    justLoaded = false;
  }
  
  while (bonusArmies > 0){
    countryToReinforce = currentPlayer->chooseCountryToReinforce(getMap(), bonusArmies);
    
    if (map->countryIsFriendly(countryToReinforce, playerNum)){
      numToReinforce = currentPlayer->chooseNumberToReinforce(getMap(), bonusArmies);
      
      if (numToReinforce > bonusArmies){
		numToReinforce = bonusArmies;
      }
      
      //put the number of armies specified in the country specifeid and decrement the number of bonus armies
      map->setCountryArmies(countryToReinforce, map->getCountryArmies(countryToReinforce) + numToReinforce);
      bonusArmies -= numToReinforce;
      View::inform(currentPlayer->getName() + " reinforced " + countryToReinforce + " with " + intToString(numToReinforce) + " armies which now has " + intToString(map->getCountryArmies(countryToReinforce)) + " armies.");
    }
  }
}

//Pre: attackingCountry and defendingCountry are validly selected countries to do battle.
//battle calculates all the game logic behind the attack of one country against another
void Game::battle(std::string attackingCountry, std::string defendingCountry)
{
	// Boolean variable which will verify whether the attacker wants to keep attacking, it's gonna be used at very end of the while loop
	bool continueBattle = true;
	int lastAttackDice;
	int attackingArmies = map->getCountryArmies(attackingCountry);
	int defendingArmies = map->getCountryArmies(defendingCountry);
	int defendingPlayerIndex = map->getCountryOwnerIndex(defendingCountry);
	int attackingPlayerIndex = map->getCountryOwnerIndex(attackingCountry);
	std::string outString;
	std::string inString;
	int inInt;

	if (attackingArmies >1){

		View::inform("\n" + attackingCountry + " attacks " + defendingCountry + " with " + intToString(attackingArmies) + " armies against " + intToString(defendingArmies) + " armies.");

		// This while loop is placed to verify whether the attacker wants to keep attacking in case the battle phase is finished and no one won yet

		do{
			//function to randomly generates the dices
			dice->roll_dice(attackingArmies, defendingArmies);

			//BATTLE DAMAGES CALCULATIONS--------------------------------------------------------------
			//function to determine the fightning phase, who wins and who losses

			outString = "";
			if (attackingArmies >2 && defendingArmies > 1){
				if (dice->getFirstAttackDie() > dice->getFirstDefendDie()){
					outString = "The attacker won ";
					defendingArmies--;
					playerArray[map->getCountryOwnerIndex(attackingCountry)]->setBattlesWon();
					playerArray[map->getCountryOwnerIndex(defendingCountry)]->setBattlesLost();
				}
				else{
					outString = "The attacker lost ";
					attackingArmies--;
					playerArray[map->getCountryOwnerIndex(defendingCountry)]->setBattlesWon();
					playerArray[map->getCountryOwnerIndex(attackingCountry)]->setBattlesLost();
				}
				outString += "the first attack " + intToString(dice->getFirstAttackDie()) + ":" + intToString(dice->getFirstDefendDie());

				if (dice->getSecondAttackDie() > dice->getSecondDefendDie()){
					outString += "\nThe attacker won ";
					defendingArmies--;
					playerArray[map->getCountryOwnerIndex(attackingCountry)]->setBattlesWon();
					playerArray[map->getCountryOwnerIndex(defendingCountry)]->setBattlesLost();
				}
				else{
					outString += "\nThe attacker lost ";
					attackingArmies--;
					playerArray[map->getCountryOwnerIndex(defendingCountry)]->setBattlesWon();
					playerArray[map->getCountryOwnerIndex(attackingCountry)]->setBattlesLost();
				}
				outString += "the second attack " + intToString(dice->getSecondAttackDie()) + ":" + intToString(dice->getSecondDefendDie());
				lastAttackDice = dice->getSecondAttackDie();
			}
			else{
				if (dice->getFirstAttackDie() > dice->getFirstDefendDie()){
					outString = "The attacker won ";
					defendingArmies--;
					playerArray[map->getCountryOwnerIndex(attackingCountry)]->setBattlesWon();
					playerArray[map->getCountryOwnerIndex(defendingCountry)]->setBattlesLost();
				}
				else{
					outString = "The attacker lost ";
					attackingArmies--;
					playerArray[map->getCountryOwnerIndex(defendingCountry)]->setBattlesWon();
					playerArray[map->getCountryOwnerIndex(attackingCountry)]->setBattlesLost();
				}
				outString += "the attack " + intToString(dice->getFirstAttackDie()) + ":" + intToString(dice->getFirstDefendDie());
				lastAttackDice = dice->getFirstAttackDie();
			}


			View::inform(outString);

			//output updated army counts 
			View::inform(attackingCountry + ": " + intToString(attackingArmies) + " armies remaining \n" + defendingCountry + ": " + intToString(defendingArmies) + " armies remaining");


			//BATTLE OUTCOME CALCULATIONS--------------------------------------------------------------
			outString = "";
			if (attackingArmies <= 1)    //Verify whether the attacker has no army left
			{
				continueBattle = false;
				outString += "\n" + attackingCountry + " does not have enough armies to continue the attack";

			}
			else if (defendingArmies <= 0)    //Verify whether the defender has no army left
			{
				continueBattle = false;
				outString += "\nYou have conquered " + defendingCountry + ".";
				outString += "\nYou must settle at least " + intToString(lastAttackDice) + " armies in this newly conquered territory.";
			
				//The attacker won, so now he must deploy his army
				if (attackingArmies > lastAttackDice)
				{
					View::inform(outString);
					outString = "";
					inInt = currentPlayer->chooseNumberOfConsolidationArmies(getMap(),lastAttackDice, attackingArmies - 1);
				
					if (inInt < lastAttackDice){
					  inInt = lastAttackDice;
					}else if (inInt > attackingArmies - 1){
					  inInt = attackingArmies - 1;
					}

					//Update the number of armies in the two countries
					defendingArmies = inInt;
					attackingArmies -= inInt;

					outString = intToString(inInt) + " armies moved from " + attackingCountry + " to " + defendingCountry + ".\n";
				}
				else    // This is when the attacker won but doesn't have enough army greater than his previous rolled dice
				{
					outString += "\nBecause you have only " + intToString(attackingArmies) + " armies left in " + attackingCountry + ", you automatically settle " + intToString(attackingArmies - 1) + " in " + defendingCountry + ".";

					//Update the army counts
					defendingArmies = attackingArmies - 1;
					attackingArmies = 1;
				}

				//change the owner of the country
				map->setCountryOwnerIndex(defendingCountry, map->getCountryOwnerIndex(attackingCountry), false);

				playerArray[attackingPlayerIndex]->setHasConquered(true);
				
				//transfer cards and update death status and country counts if required 
				if (map->countCountriesOwned(defendingPlayerIndex) < 1)
				{
					playerArray[defendingPlayerIndex]->transferCards(playerArray[attackingPlayerIndex]);
					playerArray[defendingPlayerIndex]->setDeath();
					playersAlive = countPlayersAlive();

				}

			}

			//If both sides attacker and defender still have armies left after the battle phase then the attacker will receive the choice to continue attacking or stop
			else
			{
				inString = currentPlayer->chooseContinueAttack(getMap());
				continueBattle = inString.compare("n") != 0;
			}


		} while (continueBattle);




		//Update the number of armies in the two countries before terminating the function
		map->setCountryArmies(defendingCountry, defendingArmies, false);
		map->setCountryArmies(attackingCountry, attackingArmies);


		//Output summary of the battle via outString
		outString += "\nAt the end of battle:";
		outString += "\n  " + attackingCountry + " has " + intToString(attackingArmies) + " armies";
		outString += "\n  " + defendingCountry + " has " + intToString(defendingArmies) + " armies";
		outString += "\n  " + defendingCountry;

		if (map->getCountryOwnerIndex(defendingCountry) == map->getCountryOwnerIndex(attackingCountry)){
			outString += " now";
		}
		else
		{
			outString += " still";
		}

		
		outString += " belongs to " + playerArray[map->getCountryOwnerIndex(defendingCountry)]->getName() + "\n";

		if(!playerArray[defendingPlayerIndex]->getIsAlive()){
			outString += "  " + playerArray[defendingPlayerIndex]->getName() + " has been defeated.\n";
		}

		totalBattles++;
		View::inform(outString);
	}
	else
	{
		View::inform("\n" + attackingCountry + " does not have enough armies to launch an attack.");
	}

}//END battle function


//returns a player based on their index in the player array
Player* Game::findPlayerByIndex(int i){
	Player* _player = NULL;
	for (int x = 0; x < numOfPlayers; x++){
		if (playerArray[x]->getPlayerIndex() == i){
			_player = playerArray[x];
			break;
		}
	}
	return _player;
}

//displays in-game statistics for all the players
void Game::displayStatistics(){
	for (int x = 0; x < numOfPlayers; x++){
		//various numbers used to calculate the percentages
		std::string countriesOwned = intToString(playerArray[x]->getNumCountriesOwned());
		std::string armiesOwned = intToString(playerArray[x]->getNumArmiesOwned());
		std::string playerName = playerArray[x]->getName();
		int totalCountries = map->getCountryCount();
		int battlesWon = playerArray[x]->getBattlesWon();
		int battlesLost = playerArray[x]->getBattlesLost();
		int totalBattles = playerArray[x]->getBattlesWon() + playerArray[x]->getBattlesLost();
		//scale is used to format output to 2 digits
		double scale = 0.01;
		double percentCountriesOwned = (double(playerArray[x]->getNumCountriesOwned()) / double(totalCountries) * 100);
		double roundedCountriesOwned = floor(percentCountriesOwned / scale + 0.5)*scale;


		//calculates percentage of battles won, not rounded 
		double percentBattlesWon = (double(battlesWon) / double(totalBattles) * 100);
		double roundedBattlesWon = 0;
		//roundedBattlesWon is implemented this way to prevent an output error
		//rounds the percentage of battles won
		if (totalBattles != 0){
			roundedBattlesWon = floor(percentBattlesWon / scale + 0.5)*scale;
		}

		//convert double to string for countries owned
		std::ostringstream countries;
		countries << roundedCountriesOwned;
		std::string str = countries.str();

		//convert double to string for battles won
		std::ostringstream battles;
		battles << roundedBattlesWon;
		std::string str2 = battles.str();

		//output both percentage and the numbers
		View::inform("--------------------------------------");
		View::inform(playerName + " owns " + armiesOwned + " armies across " + countriesOwned + " countries.");
		View::inform(playerName + " owns " + str + "% of the map (" + countriesOwned + "/" + intToString(totalCountries) + ").");
		View::inform(playerName + " won " + intToString(battlesWon) + " battles and lost " + intToString(battlesLost) + " battles.");
		View::inform(playerName + " won " + str2 + "% of the battles (" + intToString(battlesWon) + "/" + intToString(totalBattles) + ").");
	}
	View::inform("--------------------------------------");
}

//determines if a player should be awarded cards for the current turn
void Game::handleCards(int playerNum)
{
	if (playerArray[playerNum]->getHasConquered())
	{
		playerArray[playerNum]->addCard();
		playerArray[playerNum]->setHasConquered(false);
	}
}

//Starts the process for mid-game saving before handing it off to the appropriate builder class
void Game::saveGame(){
  GameBuilderDirector gbd;
  int inInt;
  do{
    View::prompt("Please input a save slot (0-9)");
    inInt = View::getInt();
  }while(inInt < 0 || inInt > 9);
  
  GameBuildSave * gbs = new GameBuildSave(inInt, this);
  gbd.setGameBuilder(gbs);
  gbd.constructGame();
  delete gbs;
  View::inform("Game Saved Successfully\n");
}