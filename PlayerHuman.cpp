#include "PlayerHuman.h"
  
  PlayerHuman::PlayerHuman(std::string newPlayerName, int newPlayerIndex):Player(newPlayerName, newPlayerIndex){
          
  }
  
  int PlayerHuman::chooseAction(Map * gameMap){
    int choice= 0;
    do{
      View::inform("What would you like to do?");
      View::inform("1 - Attack");
      View::inform("2 - Fortify");
      View::inform("3 - Display the Map");
      View::inform("4 - Display statistics");
      View::inform("5 - Edit map");
      View::inform("6 - Save game");
      View::inform("7 - Quit");
      View::inform("0 - End turn");
      choice = View::getInt();
      
      if(choice < 0 || choice > 7){
	View::inform("Invalid input.");
      }
      
    }while(choice < 0 || choice > 7);
      
    return choice;
   
  }
  
  std::string PlayerHuman::chooseCountryToReinforce(Map * gameMap, int maxNumOfReinforcements){
    countryToReinforce = "";
    //Get the country to be reinforced
    do{
      View::inform(this->getName() + ", you have " + intToString(maxNumOfReinforcements) + " armies of reinforcements to distribute.");
    
      View::prompt("Please input the country you want to reinforce.");      
      countryToReinforce = View::getString();
    }while(!(View::putCountryExistsAndFriendly(countryToReinforce, this->getPlayerIndex(), gameMap)));
    
    return countryToReinforce;
  }
  
  int PlayerHuman::chooseNumberToReinforce(Map * gameMap, int maxNumOfReinforcements){
    int numToReinforce;
    //Get number of reinforcements to deploy in the selected country
    do{
      View::prompt("Please input the number of armies to add to " + countryToReinforce);
      numToReinforce = View::getInt();
      if (numToReinforce < 1 || numToReinforce > maxNumOfReinforcements){
	View::inform("Invalid input, please enter a number between 1 and " + intToString(maxNumOfReinforcements));
      }
    } while (numToReinforce < 1 || numToReinforce > maxNumOfReinforcements);
    
    return numToReinforce;
  }

  std::string PlayerHuman::chooseAttackingCountry(Map * gameMap) {
    attackingCountry = "";
    //GET THE ATTACKING COUNTRY************************************************************   
    do{
      do{
	
		View::prompt("Choose a country you wish to launch your attack from.");
		attackingCountry = View::getString();
	
		//if country doesn't have enough armies to attack another country
		if (this->getPlayerIndex() == gameMap->getCountryOwnerIndex(attackingCountry) && gameMap->countryExists(attackingCountry) && gameMap->getCountryArmies(attackingCountry) < 2){
		  View::inform(attackingCountry + " does not have enough armies to launch an attack.");
		}
	
      } while (!(View::putCountryExistsAndFriendly(attackingCountry, this->getPlayerIndex(), gameMap) && gameMap->getCountryArmies(attackingCountry) > 1));
      
      //it is possible that a country has nothing to attack; for example when a country is in between friendly countries
      //the statement below avoids such possiblity
      enemyNeighbourList = gameMap->getEnemyNeighbours(attackingCountry, this->getPlayerIndex());
      if (enemyNeighbourList.empty()){
	View::inform(attackingCountry + " has no enemy neighbours to attack.");
      }
      
    } while (enemyNeighbourList.empty());
    
    return attackingCountry;
  }
  
  
  std::string PlayerHuman::chooseDefendingCountry(Map * gameMap){
    defendingCountry = "";
    //GET THE DEFENDING COUNTRY************************************************************
    //output all available countries to attack
    View::inform(attackingCountry + "'s enemy neighbours are:");
    View::outputCountryList(enemyNeighbourList);
    
    //Ask for user input and validates to see whether player chose an enemy country       
    do{
      //get country choice and error check
      View::prompt("Choose the country you want to attack");
      defendingCountry = View::getString();
      
      //if you selected a country that isn't a neighbour
      if (!gameMap->countryExists(defendingCountry)){
	View::inform(defendingCountry + " does not exist.");
      }
      //if you selected a friendly country to attack
      else if (gameMap->getCountryOwnerIndex(defendingCountry) == this->getPlayerIndex())
      {
	View::inform("Invalid choice: " + defendingCountry + " already belongs to you.");
      }
      else if (!listContains(enemyNeighbourList, defendingCountry)){
	View::inform("Invalid choice: " + defendingCountry + " is not a neighbour of " + attackingCountry + ".");
      }
    } while (!(gameMap->countryExists(defendingCountry) && gameMap->getCountryOwnerIndex(defendingCountry) != this->getPlayerIndex() &&
    listContains(enemyNeighbourList, defendingCountry)));
    
    return defendingCountry;
  }
  
  bool PlayerHuman::chooseContinueAttack(Map * gameMap){
    std::string inString;
    View::prompt("Would you like to continue the attack? (y/n)");
    inString = View::getString();
    View::prompt(inString + intToString((int)inString.compare("y") == 0));
    return (inString.compare("y") == 0);
    
  }
  
  int PlayerHuman::chooseNumberOfConsolidationArmies(Map * gameMap, int minConsolidationArmies, int maxConsolidationArmies){
    int inInt = 0;
    do{
      View::prompt("How many armies would you like to settle in " + defendingCountry + "?");
      inInt = View::getInt();
      //Asking the user again to deploy the right amount
      if (inInt > maxConsolidationArmies || inInt < minConsolidationArmies){
	View::inform("Invalid input. Need to add between " + intToString(minConsolidationArmies) + " and " + intToString(maxConsolidationArmies) + " armies.");
      }
    }while (inInt < minConsolidationArmies || inInt > maxConsolidationArmies);
    
    return inInt;
  }
  
  std::string PlayerHuman::chooseSourceFortificationCountry(Map * gameMap){
    sourceCountry = "";
    std::list<std::string> connectedFriendlyCountries;
    //input loop: prompt user for a friendly country until they pick one with friendly neighbours
	do{
		//input loop: prompt user for a friendly country until they pick one with enough armies to move elsewhere
		do{
			View::prompt("Choose a country to move troops from.");
			sourceCountry = View::getString();
			//if country doesn't have enough armies to move some to a neighbour
			if (gameMap->countryExists(sourceCountry) && gameMap->getCountryOwnerIndex(destinationCountry) == this->getPlayerIndex() && gameMap->getCountryArmies(sourceCountry) < 2){
				View::inform(sourceCountry + " does not have enough armies to move troops to another country");
			}

		} while (!(View::putCountryExistsAndFriendly(sourceCountry, this->getPlayerIndex(), gameMap) && gameMap->getCountryArmies(sourceCountry) > 1));

		//get list of all countries connected to the selected country
		connectedFriendlyCountries = gameMap->getConnectedFriendlyCountries(sourceCountry, this->getPlayerIndex());

		//if the country has no countries connected to it (other than itself)
		if (connectedFriendlyCountries.size() <= 1){
			View::inform(sourceCountry + " is not connected to any friendly neighbours to which it can move armies.");
		}
	} while (connectedFriendlyCountries.size() <= 1);

	View::inform(sourceCountry + " is connected to:");
	View::outputCountryList(connectedFriendlyCountries);
	
	return sourceCountry;
	
  }
  
  std::string PlayerHuman::chooseDestinationFortificationCountry(Map * gameMap, std::list<std::string> & connectedCountries){
    destinationCountry = "";
    //Input loop: prompt for a friendly country until they enter one on the list of connected countries
    do{
      View::prompt("Choose the country to fortify.");
      destinationCountry = View::getString();
      
      //if the entered country is not on the list of connected countries
      if (gameMap->countryExists(destinationCountry) && gameMap->getCountryOwnerIndex(destinationCountry) == this->getPlayerIndex() && !listContains(connectedCountries, destinationCountry)){
	View::inform(destinationCountry + " is not connected to " + sourceCountry + " and therefore cannot be fortified with armies from " + sourceCountry + ".");
      }
      else if(destinationCountry.compare(sourceCountry) ==0){
	View::inform(destinationCountry + " cannot fortify itself.");
      }
    } while (!(View::putCountryExistsAndFriendly(destinationCountry, this->getPlayerIndex(), gameMap) && listContains(connectedCountries, destinationCountry) && destinationCountry.compare(sourceCountry) != 0));
    
    return destinationCountry;
  }
  
  int PlayerHuman::chooseNumberOfFortificationArmies( Map * gameMap){
    int numToMove;
    //Input loop: prompt for the number of armies to move until they pick a number between 1 and the max they can move
    View::prompt(sourceCountry + " can move up to " + intToString(gameMap->getCountryArmies(sourceCountry) - 1) + " armies to " + destinationCountry + ".  How many would you like to move?");
    do{
      numToMove = View::getInt();
      
      //if they pick a number not between 1 and the number they are allowed to move
      if (numToMove < 1 || numToMove > gameMap->getCountryArmies(sourceCountry) - 1){
	View::inform("Invalid input.");
	View::prompt("Please enter a number between 1 and " + intToString(gameMap->getCountryArmies(sourceCountry) - 1) + ".");
      }
    } while (numToMove < 1 || numToMove > gameMap->getCountryArmies(sourceCountry) - 1);
    
    return numToMove;
    
    //update the two countries army counts
  }