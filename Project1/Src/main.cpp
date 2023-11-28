#pragma once
#include "Game.h"

Game* game = nullptr;

int main(int argc,char *argv[]) 
{
	{
		//SDL_Init(SDL_INIT_EVERYTHING);
		//SDL_Window* window = SDL_CreateWindow("Project1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
		//SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
		//
		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		//SDL_RenderClear(renderer);
		//SDL_RenderPresent(renderer);

		//SDL_Delay(10000);
	}

	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	//initialise
	game->init("RatriEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		//handle any input
		game->handleEvent();
		//update all positions
		game->update();
		//render/draw changes
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}


	game->clean();
	return 0;
}