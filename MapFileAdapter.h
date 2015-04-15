#pragma once
#include "MapFile.h"
#include "MapConfig.h"
#include "Game.h"



class MapFileAdapter : public MapConfig
{
private:
	MapFile* mapFileAdaptee;
public:
	MapFileAdapter(MapFile* adaptee);
	MapFileAdapter(void);
	~MapFileAdapter(void);

	Map* loadMap(string fileName);
	void saveMapToFile(const Map* mapToSave, string fileName);

	Map* createMap();

};