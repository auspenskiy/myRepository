#include "View.h"

//output something normally
void View::inform(std::string msg){
  std::cout << msg << std::endl;
}

//output something with formatting to indicate to the user that they should input something
void View::prompt(std::string msg){
  std::cout << "--> "  << msg << std::endl;
}


int View::getInt(){
  using std::cin;
  
  int inInt = 0;
  do{
    if(!cin){
      cin.clear();
      cin.ignore(256,'\n');
    }
    
    cin >> inInt;
    
    if(!cin){
      std::cout << "Invalid input. Please enter a valid integer." << std::endl;
    }
  }while (!cin);
    
  return inInt;
  
}

std::string View::getString(){
	  std::string i;
	  //This filters out extra \n's left over from previous input and gets input
	  do{
	    getline( std::cin, i);
	  }while((int)i[0] == 0);

	  return i;
}

void View::outputCountryList(std::list<std::string> countryList){
	//output list of countries
	std::list<std::string>::iterator iter = countryList.begin();
	while (iter != countryList.end()){
		View::inform("  " + *iter);
		iter++;
	}
}

bool View::putCountryExistsAndFriendly(std::string country, int currentPlayerIndex, Map * map){
	if (!map->countryExists(country)){
		View::inform(country + " does not exist.");
		return false;
	}
	else if (map->getCountryOwnerIndex(country) != currentPlayerIndex){
		View::inform(country + " does not belong to you.");
		return false;
	}
	return true;
}