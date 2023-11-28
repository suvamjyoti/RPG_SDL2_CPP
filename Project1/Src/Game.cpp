#pragma once
#include "Game.h"
#include "TextureManager.h"
#include  "Map.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Collision.h"

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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
	player.addComponent<TransformComponent>(40.0f,50.0f,64,64,2);
	player.addComponent<SpriteComponent>("Assets/character/idle/i1.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Assets/map/wall.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvent()
{
	
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
	//manager.refresh();
	manager.update();
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