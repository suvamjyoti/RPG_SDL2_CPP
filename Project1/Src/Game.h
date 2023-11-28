#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

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
	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	int cnt;		//counter
	bool isRunning;
	SDL_Window* window;


};

