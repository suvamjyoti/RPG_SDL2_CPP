#pragma once
#include "Game.h"
#include "TextureManager.h"
#include  "Map.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Collision.h"


Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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


	Map::LoadMap("Assets/map/tilemap.map",32,32);

	player.addComponent<TransformComponent>(40.0f,50.0f,32,32,4);
	player.addComponent<SpriteComponent>("Assets/character/idle/",3,500);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
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
	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		//check for collision with all the colliders in the list
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
	

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}


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

void Game::AddTiles(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}