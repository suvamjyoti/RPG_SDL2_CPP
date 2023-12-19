#include "Map.h"
#include "Game.h"
#include <fstream>

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX,srcY;

	for (int y = 0;y < sizeY;y++)
	{
		for (int x = 0;x<sizeX;x++)
		{
			//say 01,

			//here get 0
			mapFile.get(tile);
			srcY = atoi(&tile) * 32;

			//here get 1
			mapFile.get(tile);
			srcX = atoi(&tile) * 32;

			Game::AddTiles(srcX,srcY, x * 32, y * 32);
			
			//here ignore ,
			mapFile.ignore();
		}
	}

	mapFile.close();
}

