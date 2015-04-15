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

class MapFile
{
public:
	MapFile(void);
	~MapFile(void);
	
	void saveMap(const Map * mapToSave, std::string mapFilePath);
	Map * loadMap(std::string mapFilePath);

	Map* createCustomMap();
	  
private:
  	void openInputFile(string path);
	void closeInputFile();

	void openOutputFile(string path) ;
	void closeOutputFile();

	Map * loadMapFromFile();
	void saveMapToFile(const Map * mapToSave);

	Map* createMapFile();

	//void displayMapFileContent();

	//list<Territory> MapConfig::getTerritoriesArray();
	bool isConnectedGraph() ;
	bool areContinentsSubGraphs() ;
	bool isOneCountyPerContinent() ;

	
//PRIVATE ATTRIBUTES-------------------------------------------------
	std::ifstream inStream;
	std::ofstream outStream;
};