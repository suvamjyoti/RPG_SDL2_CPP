#pragma once
#include "Game.h"
#include "TextureManager.h"
#include  "Map.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"


Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;


auto& player(manager.addEntity());

Game::Game() 
{

}

Game::~Game()
{
	
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystms INitialised"<<std::endl;

		//create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std::cout << "window Created" << std::endl;
		}

		//create renderer
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;
	}

	else 
	{
		//if SDL doesnot initialise properly
		isRunning = false;
	}

	map = new Map();

	//ECS implementation
	player.addComponent<PositionComponent>();
	player.addComponent<SpriteComponent>("Assets/character/idle/i1.png");

}

void Game::handleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
		isRunning = false;
		break;

		default:
			break;
	}
}

void Game::update()
{
	manager.update();
	manager.draw();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	//this is where we add stuff to render

	//order in which added is the order in which it is displayed
	map->DrawMap();
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}

bool Game::running()
{
	return isRunning;
}