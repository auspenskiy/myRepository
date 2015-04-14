#include "MapConfig.h"
#include "TempCountry.h"

MapConfig::MapConfig(void)
{

}


MapConfig::~MapConfig(void)
{
}

void MapConfig::readMapFromFile(string fileName)
{
	ifstream fileToRead = openInputFile(fileName);
	string skip;
	string read;

	std::list<Continent> continents;
	string strCont;
	string scoreCont;

	getline(fileToRead, skip, '\n');//read [continents]

	int index = 0;

	while (fileToRead.peek() != '\n')
	{
		Continent continent;
		getline(fileToRead, strCont, '=');
		continent.setName(strCont);
		getline(fileToRead, scoreCont, '\n');
		continent.setControlValue(atoi(scoreCont.c_str()));
		continents.push_back(continent);
		index++;
<<<<<<< HEAD
	}
=======
}
>>>>>>> 3d2feef5b49e69365f5ce71d6306a6f0af05bdd3

	setContinents(continents);

	getline(fileToRead, skip, '\n');//read empty line
	getline(fileToRead, skip, '\n');//read [territories]

	string territoryName;
	string parentContinent;
	std::list<TempCountry> listTerritories;

	int x, y;

	while (!fileToRead.eof())
	{
		if (fileToRead.peek() != '\n')
		{
			std::list<string> adjacent;
			getline(fileToRead, territoryName, ',');//read territory

			TempCountry territory;
			territory.setName(territoryName);

			fileToRead >> x;//read x
			territory.setX(x);
			fileToRead.get();
			fileToRead >> y;//read y
			territory.setY(y);
			fileToRead.get();

			getline(fileToRead, parentContinent, ',');//read continent it belongs to
			territory.setParentCont(parentContinent);

			getline(fileToRead, territoryName, '\n');//read adjacents


			std::istringstream ss(territoryName);
			std::string token;

			while (std::getline(ss, token, ','))
			{
				adjacent.push_back(token);
			}
			territory.setAdjacent(adjacent);
			listTerritories.push_back(territory);
		}
		else
		{
			fileToRead.get();
		}
	}
	fileToRead.close();
}

ifstream MapConfig::openInputFile(string path)
{
	ifstream inputFile;
	inputFile.open(path);

	if (inputFile.good())
	{
		return inputFile;
	}
	else
	{
		cin.get();
		exit(0);
	}
}

ofstream MapConfig::openOutputFile(string path)
{
	ofstream outputFile;
	outputFile.open(path);
	if (outputFile.good())
	{
		return outputFile;
	}
	else
	{
		cin.get();
		exit(0);
	}
}

void MapConfig::setContinents(std::list<Continent> cContinents)
{
	continents = cContinents;
}