
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
	return mapFileAdaptee->loadMap(fileName);
}

Map* MapFileAdapter::createMap()
{
	return mapFileAdaptee->createCustomMap();
}

void MapFileAdapter::saveMapToFile(const Map* mapToSave, string fileName)
{
	mapFileAdaptee->saveMap(mapToSave, fileName);
}
