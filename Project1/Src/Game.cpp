#pragma once
#include "Game.h"
#include "TextureManager.h"
#include  "Map.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "ECS/AnimationComponent.h"
#include "Animations/PlayerAnimation.h"


Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* MapTileSetPath = "Assets/map/terrain.png";

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


	Map::LoadMap("Assets/map/Map1.map",20,20);

	player.addComponent<TransformComponent>(40.0f,50.0f,50,64,1);
	player.addComponent<SpriteComponent>("Assets/character/idle/1.png");
	PlayerAnimation playerAnimation;
	player.addComponent<AnimationComponent>(playerAnimation.playerAnimationMap, AnimationType::idle);
	player.addGroup(groupPlayers);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

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

void Game::AddTiles(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, MapTileSetPath);
	tile.addGroup(groupMap);
}