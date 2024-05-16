#pragma once
#include "Game.h"
#include <string>

class Map
{
public:

	Map(const char* mfp, const char* tfp,int ms,int ts);
	~Map();

	void LoadMap(std::string path,int sizeX,int sizeY);
	void AddTiles(int srcX, int srcY, int xpos, int ypos);
	

private:

	const char* mapFilePath;
	const char* tileFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};

