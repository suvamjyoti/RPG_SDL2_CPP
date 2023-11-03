#pragma once
#include "Game.h"

class Map
{
public:
	static const int Levelrows = 20;
	static const int Levelcols = 25;

	Map();
	~Map();

	void LoadMap(int arr[Levelrows][Levelcols]);
	void DrawMap();
	void CreateLevel(int(&arr)[Levelrows][Levelcols]);

private:

	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
 
};

