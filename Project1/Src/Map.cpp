#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\Components.h"

extern Manager manager;

Map::Map(const char* mfp,const char* tfp,int ms,int ts): 
					mapFilePath(mfp),tileFilePath(tfp),mapScale(ms),tileSize(ts)
{
	scaledSize = ms * ts;
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX,srcY;

	for (int y = 0;y<sizeY;y++)
	{
		for (int x = 0;x<sizeX;x++)
		{
			//say 01,

			//here get 0
			mapFile.get(tile);
			srcY = atoi(&tile) * tileSize;

			//here get 1
			mapFile.get(tile);
			srcX = atoi(&tile) * tileSize;

			AddTiles(srcX,srcY, x * tileSize * mapScale , y * tileSize * mapScale);
			
			//here ignore ,
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0;y < sizeY;y++)
	{
		for (int x = 0;x < sizeX;x++)
		{
			mapFile.get(tile);
			if (tile == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize , scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}


	mapFile.close();
}

void Map::AddTiles(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos,tileSize,mapScale,tileFilePath);
	tile.addGroup(Game::groupMap);
}

