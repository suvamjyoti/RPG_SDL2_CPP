#include "Map.h"
#include "TextureManager.h"

const int tileSize = 128;
int lvl1[Map::Levelrows][Map::Levelcols];


void Map::CreateLevel(int(&arr)[Map::Levelrows][Map::Levelcols])
{
	for (int i = 0; i < Map::Levelrows; ++i) {
		for (int j = 0; j < Map::Levelcols; ++j) {
			arr[i][j] = rand() % 3; // Generating random values 0, 1, or 2
		}
	}
}

Map::Map()
{
	CreateLevel(lvl1);

	dirt = TextureManager::LoadTexture("Assets/map/dirt.png");
	grass = TextureManager::LoadTexture("Assets/map/grass.png");
	water = TextureManager::LoadTexture("Assets/map/water.png");

	LoadMap(lvl1);

	src.x = src.y = 0;
	src.h = dest.h = tileSize;
	src.w = dest.w = tileSize;

	dest.x = dest.y = 0;


}

Map::~Map()
{
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(dirt);

}

void Map::LoadMap(int arr[Levelrows][Levelcols])
{
	for (int row = 0; row < Levelrows; ++row) 
	{
		for (int col = 0; col < Levelcols; ++col)
		{
			map[row][col] = arr[row][col];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < Levelrows; ++row)
	{
		for (int col = 0; col < Levelcols; ++col)
		{
			type = map[row][col];
			dest.x = col * tileSize;
			dest.y = row * tileSize;

			switch (type)
			{
			case 0:
				TextureManager::Draw(water, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;

			default:
				break;
			}
		}
	}
}

