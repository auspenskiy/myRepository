
#include "MapFile.h"
#include "MapFileAdapter.h"

MapFileAdapter::MapFileAdapter(MapFile* adaptee)
{
	mapFileAdaptee = adaptee;
}

MapFileAdapter::MapFileAdapter()
{
	mapFileAdaptee = new MapFile();
}

Map* MapFileAdapter::loadMap(string fileName)
{
	Game game(fileName);
	return mapFileAdaptee->loadMap(fileName);
}

void MapFileAdapter::saveMapToFile(const Map* mapToSave, string fileName)
{
	mapFileAdaptee->saveMap(mapToSave, fileName);
}
