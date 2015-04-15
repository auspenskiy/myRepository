#include "game_utils.h"


#include <algorithm> //std::find function
#include <fstream>
#include "PlayerHuman.h"
#include "PlayerAggressive.h"
#include "PlayerDefensive.h"
#include "PlayerRandom.h"
#include <cstring>

//HELPER METHOD FOR FORTIFY
//checks if a list of string contains a given string
bool listContains(std::list<std::string> & lst, std::string str){
  std::list<std::string>::iterator findIter = std::find(lst.begin(), lst.end(), str);
  
  return findIter != lst.end() || findIter == lst.end() && lst.back().compare(str) == 0;
}

//returns true if a given file exists on the hard disk
bool fileExists(std::string fileName){
  std::ifstream inStream;
  bool fileExists = false;
  
  inStream.open(fileName.c_str());
  if (inStream.good()) {
    fileExists = true;
  }
  inStream.close();
  
  return fileExists;
}

//function to convert integer to string - used in conjunction with View
std::string intToString(int i){
  int temp = i;
  int digit = 0;
  int counter = 0;
  int length = 0;

  do{
    temp /= 10;
    counter++;
  }while (temp != 0);
  
  length = counter;
  
  if (i < 0){
   length++; 
   temp = -1 * i;}
  else{
    temp = i;
    counter --;
  }
  
  char * toString = new char[length];
  
  if (i<0){
    toString[0] = '-';
  }
  
  do{
    digit = temp %10;
    toString[counter]= (char)digit + 48;
    
    temp /=10;
    counter --;
    
  }while (temp != 0);
  
  std::string returnString (toString, length);

  delete [] toString;
      
  return returnString;
}

//Creates player objects based on the string used to save them in save files
Player * tinyFactory(std::string playerType, std::string newName, int newPlayerIndex){
  View::inform(playerType);
  
  if (strstr(playerType.c_str(), "PlayerHuman") != NULL){
      return new PlayerHuman(newName, newPlayerIndex);
  }
  if (strstr(playerType.c_str(), "PlayerAggressive") != NULL){
      return new PlayerAggressive(newName, newPlayerIndex);
  }
  if (strstr(playerType.c_str(), "PlayerDefensive") != NULL){
      return new PlayerDefensive(newName, newPlayerIndex);
  }
  if (strstr(playerType.c_str(), "PlayerRandom") != NULL){
      return new PlayerRandom(newName, newPlayerIndex);
  }
  
  return new PlayerHuman(newName, newPlayerIndex);  
}