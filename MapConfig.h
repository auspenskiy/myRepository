#pragma once

#include<string>
#include <iostream>
#include <fstream>
#include <list>
#include "TempCountry.h"
#include "continent.h"
#include "map.h"
#include "country.h"
using namespace std;

class MapConfig
{
public:
	MapConfig(void);
	~MapConfig(void);
	
	void saveMap(const Map * mapToSave, std::string mapFilePath);
	Map * loadMap(std::string mapFilePath);
	  
private:
  	void openInputFile(string path);
	void closeInputFile();

	void openOutputFile(string path) ;
	void closeOutputFile();

	Map * loadMapFromFile();
	void saveMapToFile(const Map * mapToSave);

	//void displayMapFileContent();

	//list<Territory> MapConfig::getTerritoriesArray();
	bool isConnectedGraph() ;
	bool areContinentsSubGraphs() ;
	bool isOneCountyPerContinent() ;
	
	
//PRIVATE ATTRIBUTES-------------------------------------------------
	std::ifstream inStream;
	std::ofstream outStream;
};