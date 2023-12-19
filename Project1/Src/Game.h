#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int posx, int posy, int width, int height, bool fullscreen);

	void handleEvent();
	void update();
	void render();
	void clean();
	bool running();

	static void AddTiles(int srcX,int srcY, int xpos, int ypos);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int cnt;		//counter
	bool isRunning;
	SDL_Window* window;


};

