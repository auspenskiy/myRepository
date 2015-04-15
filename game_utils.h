#pragma once

#include <list>
#include <string>
#include "Player.h"

/*
Class game_utils: A collection of miscellaneous helper methods used throughout the program
*/
class Player;

bool listContains(std::list<std::string> & lst, std::string str);
std::string intToString(int i);
bool fileExists(std::string fileName);

Player * tinyFactory(std::string playerType, std::string newName, int newPlayerIndex);