#include "textview.h"
#include <string>
#include "game.h"
//Store a reference to the map being observed and the attach itself to it as an observer
TextView::TextView(Map & newMap){
  m = & newMap;
  m->attach(*this);
}

TextView::~TextView(){
}

//update simply outputs the map's string representation
void TextView::update(){
  View::inform(m->to_string());
  //updates statistics
  m->updateCountriesAndArmies();
}