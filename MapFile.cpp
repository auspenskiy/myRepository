#include "MapFile.h"
#include <list>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <fstream>
using namespace std;
MapFile::MapFile(void)
{
}
MapFile::~MapFile(void)
{
}
void MapFile::openInputFile(string path)
{
	inStream.open(path.c_str());
	if (!inStream.good())
	{
		std::cout << "FILE OPENING ERROR - file path: " << path << endl;
		std::cin.get();
		exit(0);
	}
}
void MapFile::closeInputFile()
{
	inStream.close();
}
void MapFile::openOutputFile(string path)
{
	outStream.open(path.c_str());
	if (!outStream.good())
	{
		std::cout << "FILE CLOSING ERROR - file path: " << path << endl;
		std::cin.get();
		exit(0);
	}
}
void MapFile::closeOutputFile()
{
	outStream.close();
}
//the function to be implemented with an object Map from Part 1 of the assignment
//traversal of the graph will be performed to find out if the map is a connected graph
bool MapFile::isConnectedGraph()
{
	return true;
}
//the function to be implemented with an object Map from Part 1 of the assignment
//traversal of the graph will be performed to find out if the continents are connected subgraphs
bool MapFile::areContinentsSubGraphs()
{
	return true;
}
//the function to be implemented with an object Map from Part 1 of the assignment
//traversal of the graph will be performed to find out if a country belongs to exactly one continent
bool MapFile::isOneCountyPerContinent()
{
	return true;
}
Map * MapFile::loadMapFromFile()
{
	string skip;
	string read;
	string author;
	string image;
	string wrap;
	string scroll;
	string warn;
	Continent ** continents = NULL;
	Country ** countries = NULL;
	int numOfContinents = 0;
	int numOfCountries = 0;
	//Sets the end-of-line delimiting character depending on whether the program is being run in linux or not.
#ifdef linux
	const char END_LINE_CHARACTER = (char)13;
#else
	const char END_LINE_CHARACTER = '\n';
#endif
	string inString;
	getline(inStream, skip, '\n');
	getline(inStream, skip, '=');//read author line
	getline(inStream, author, '\n');
	getline(inStream, skip, '=');//read image line
	getline(inStream, image, '\n');
	getline(inStream, skip, '=');//read wrap line
	getline(inStream, wrap, '\n');
	getline(inStream, skip, '=');//read scroll line
	getline(inStream, scroll, '\n');
	getline(inStream, skip, '=');//read warn line
	getline(inStream, warn, '\n');
	getline(inStream, skip, '\n');//read empty line
	getline(inStream, skip, '\n');//read [continents]
	int index = 0;
	Continent * newContinent;
	while (inStream.peek() != '\n')
	{
		//add a continent to a big array of continents
		newContinent = new Continent();
		getline(inStream, inString, '=');
		newContinent->setName(inString);
		getline(inStream, inString, '\n');
		newContinent->setControlValue(atoi(inString.c_str()));
		continents = insertElement(continents, numOfContinents, *newContinent);
		//std::cout << newContinent->getName() << " added to the map" << std::endl;
	}
	getline(inStream, skip, '\n');//read empty line
	getline(inStream, skip, '\n');//read [territories]
	TempCountry tempCountry;
	string tempCountryName;
	string parentContinent;
	std::list<TempCountry> listTempCountries;
	int x, y;
	while (!inStream.eof())
	{
		if (inStream.peek() != '\n' && inStream.peek() != (char)13 && inStream.peek() != -1)
		{
			std::list<string> adjacent;
			getline(inStream, tempCountryName, ',');//read tempCountry
			tempCountry.setName(tempCountryName);
			inStream >> x;//read x
			tempCountry.setX(x);
			inStream.get();
			inStream >> y;//read y
			tempCountry.setY(y);
			inStream.get();
			getline(inStream, parentContinent, ',');//read continent it belongs to
			tempCountry.setParentCont(parentContinent);
			getline(inStream, tempCountryName, '\n');//read adjacents
			tempCountryName += ',';
			std::istringstream ss(tempCountryName);
			std::string token;
			while (std::getline(ss, token, ','))
			{
				adjacent.push_back(token);
			}
			tempCountry.setAdjacent(adjacent);
			listTempCountries.push_back(tempCountry);
		}
		else
		{
			inStream.get();
		}
	}
	for (std::list<TempCountry>::iterator it = listTempCountries.begin(); it != listTempCountries.end(); ++it)
	{
		//find the new country's continent
		Continent * inContinent = &findElement(continents, numOfContinents, (*it).getParentCont());
		//Create new country (which automatically adds it to its continent
		Country * newCountry = new Country((*it).getName(), *inContinent, (*it).getX(), (*it).getY());
		//Add Country to Map's Country array
		countries = insertElement(countries, numOfCountries, *newCountry);
		//std::cout << newCountry->getName() << " added to the map." << std::endl;
	}
	//connect the countries to their neighbours
	//for each country in the list of loaded countries
	for (std::list<TempCountry>::iterator it = listTempCountries.begin(); it != listTempCountries.end(); ++it)
	{
		//find the country object
		Country * neighbourCountry = &findElement(countries, numOfCountries, (*it).getName());
		std::list<string> neighbourList = (*it).getAdjacent();
		//for each entry in its attached territories
		for (std::list<string>::iterator itNeighbours = neighbourList.begin(); itNeighbours != neighbourList.end(); ++itNeighbours)
		{
			//find the neighbour's country object, add them as neighbours
			findElement(countries, numOfCountries, (*itNeighbours)).addNeighbour(*neighbourCountry);
		}
	}
	return new Map(numOfCountries, countries, numOfContinents, continents, author, image, wrap, scroll, warn);
}
void MapFile::saveMapToFile(const Map * mapToSave)
{
	if (isConnectedGraph() && areContinentsSubGraphs() && isOneCountyPerContinent())
	{
		outStream << "[Map]" << endl;
		outStream << "author=" << mapToSave->getAuthor() << endl;
		outStream << "image=" << mapToSave->getImage() << endl;
		outStream << "wrap=" << mapToSave->getWrap() << endl;
		outStream << "scroll=" << mapToSave->getScroll() << endl;
		outStream << "warn=" << mapToSave->getWarn() << endl << endl;
		outStream << "[Continents]" << endl;
		for (int z = 0; z < mapToSave->getContinentCount(); z++)
		{
			outStream << mapToSave->getContinents()[z]->getName() << "=" << mapToSave->getContinents()[z]->getControlValue() << (char)10;
		}
		outStream << endl;
		outStream << "[Territories]" << endl;
		for (int z = 0; z < mapToSave->getCountryCount(); z++)
		{
			outStream << mapToSave->getCountries()[z]->getName() << ",";
			outStream << mapToSave->getCountries()[z]->getX() << "," << mapToSave->getCountries()[z]->getY() << ",";
			outStream << mapToSave->getCountries()[z]->getContinent()->getName() << ",";
			for (int a = 0; a < mapToSave->getCountries()[z]->getNeighbourCount(); a++)
			{
				outStream << mapToSave->getCountries()[z]->getAllNeighbours()[a]->getName();
				//outputs the separating colon, making sure it doesn't put one after the last neighbour.
				if (a < mapToSave->getCountries()[z]->getNeighbourCount() - 1){
					outStream << ",";
				}
			}
			outStream << endl;
		}
	}
	else
	{
		std::cout << "The map you are providing doesn't meet the criteria of the game";
	}
	closeOutputFile();
}

Map* MapFile::createMapFile()
{
		int contNum;
		string skip;
		string read;
		string author;
		string image;
		string wrap;
		string scroll;
		string warn;

		Continent ** continents = NULL;
		Country ** countries = NULL;
		int numOfContinents = 0;
		int numOfCountries = 0;

		View::prompt("Enter the author's name: ");
		author = View::getString();

		View::prompt("Enter the image file path: ");
		image = View::getString();

		View::prompt("Enter the wrap value: ");
		wrap = View::getString();

		View::prompt("Enter the scroll value: ");
		scroll = View::getString();

		View::prompt("Enter the warn value: ");
		warn = View::getString();

		View::prompt("How many continents do you want to have in a game?");
		contNum = View::getInt();
		string contName;
		int controlValue;
		Continent * newContinent;
		std::list<string> continentNames;
		for (int k = 0; k < contNum; k++)
			{
				View::prompt("Enter the name of the continent " + intToString(k));
				cin.get();
				getline(cin, contName);
				newContinent = new Continent();
				newContinent->setName(contName);

				std::cout << "Enter the control value for the continent" << endl;
				std::cin >> controlValue;
				newContinent->setControlValue(controlValue);
				continents = insertElement(continents, numOfContinents, *newContinent);
				continentNames.push_back(contName);
			}

			int numTer;
			string terrName;
			cout << "How many countries do you want to create?" << endl;
			cin >> numTer;
			cin.get();

			TempCountry tempCountry;
			string tempCountryName;
			string parentContinent;
			std::list<TempCountry> listTempCountries;
			int x, y;
			for (int i = 0; i < numTer; i++)
			{
					std::list<string> adjacent;
					View::prompt("Enter country name " + intToString(i) + ": ");
					//cin.get();
					getline(cin, tempCountryName, '\n');
					tempCountry.setName(tempCountryName);

					View::prompt("Enter x value: ");
					x = View::getInt();
					tempCountry.setX(x);

					View::prompt("Enter y value: ");
					y = View::getInt();
					tempCountry.setY(y);
					cin.get();

					bool valid = false;
					do
					{
						View::prompt("Enter the name of a parent continent for " + tempCountryName);
						//sgetline(cin, skip, '\n');
						getline(cin, parentContinent, '\n');

						for (std::list<string>::iterator it = continentNames.begin(); it != continentNames.end(); ++it)
						{
							Continent cont;
							string curName = (*it);
							if (curName == parentContinent)
							{
								valid = true;
								tempCountry.setParentCont(parentContinent);
								break;
							}
							else
							{
								continue;
							}
						}
						if (!valid)
						{
							View::inform("You didn't create this continent. Please enter the name of a valid continent ");
						}
					} while (!valid);
					
					View::prompt("How many adjacent countries does " + tempCountryName + " has?: ");

					int numOfAdj = View::getInt();
					string adj = "";
					for (int a = 0; a < numOfAdj; a++)
					{
						View::prompt("Enter the name of the adjacent country: ");
						//getline(cin, skip, '\n');
						cin.get();
						getline(cin, adj);
						adjacent.push_back(adj);
					}
					tempCountry.setAdjacent(adjacent);
					listTempCountries.push_back(tempCountry);
			}

			for (std::list<TempCountry>::iterator it = listTempCountries.begin(); it != listTempCountries.end(); ++it)
			{
				//find the new country's continent
				Continent * inContinent = &findElement(continents, numOfContinents, (*it).getParentCont());
				//Create new country (which automatically adds it to its continent
				Country * newCountry = new Country((*it).getName(), *inContinent, (*it).getX(), (*it).getY());
				//Add Country to Map's Country array
				countries = insertElement(countries, numOfCountries, *newCountry);
				//std::cout << newCountry->getName() << " added to the map." << std::endl;
			}
			//connect the countries to their neighbours
			//for each country in the list of loaded countries
			for (std::list<TempCountry>::iterator it = listTempCountries.begin(); it != listTempCountries.end(); ++it)
			{
				//find the country object
				Country * neighbourCountry = &findElement(countries, numOfCountries, (*it).getName());
				std::list<string> neighbourList = (*it).getAdjacent();
				//for each entry in its attached territories
				for (std::list<string>::iterator itNeighbours = neighbourList.begin(); itNeighbours != neighbourList.end(); ++itNeighbours)
				{
					//find the neighbour's country object, add them as neighbours
					findElement(countries, numOfCountries, (*itNeighbours)).addNeighbour(*neighbourCountry);
				}
			}

		return new Map(numOfCountries, countries, numOfContinents, continents, author, image, wrap, scroll, warn);
}

Map * MapFile::loadMap(std::string mapFilePath){
	Map * newMap;
	openInputFile(mapFilePath);
	newMap = loadMapFromFile();
	closeInputFile();
	return newMap;
}
void MapFile::saveMap(const Map * mapToSave, std::string mapFilePath){
	openOutputFile(mapFilePath);
	saveMapToFile(mapToSave);
	closeOutputFile();

}

Map* MapFile::createCustomMap(){
	Map * newMap;
	newMap = createMapFile();
	return newMap;
}