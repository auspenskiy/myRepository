#include<string>
#include <iostream>
#include <fstream>
#include <list>
#include "Continent.h"
#include <sstream>
#include <stdlib.h>

using namespace std;

#pragma once

class MapConfig
{
public:
	MapConfig(void);
	~MapConfig(void);

	void readMapFromFile(string fileName);
	void setContinents(std::list<Continent> cContinents);

private:
	std::list<Continent> continents;
	std::ifstream openInputFile(string path);
	std::ofstream openOutputFile(string path);
};

