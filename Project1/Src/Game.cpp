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

SDL_Rect Game::Camera = { 0,0,800,640 };

auto& player(manager.addEntity());

Map* map;

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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;
	}

	else 
	{
		//if SDL doesnot initialise properly
		isRunning = false;
	}

	map = new Map("Assets/map/Map1.map", 3, 32);

	map->LoadMap("Assets/map/Map1.map", 20, 20);

	player.addComponent<TransformComponent>(400.0f,400.0f,50,64,2);
	player.addComponent<SpriteComponent>("Assets/character/idle/1.png");
	PlayerAnimation playerAnimation;
	player.addComponent<AnimationComponent>(playerAnimation.playerAnimationMap, AnimationType::idle);
	player.addGroup(groupPlayers);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

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

	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerpos = player.getComponent<TransformComponent>().position;

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerpos;
		}
	}

	manager.refresh();
	manager.update();

	Camera.x = player.getComponent<TransformComponent>().position.x - 400;
	Camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (Camera.x < 0) Camera.x = 0;
	if (Camera.y < 0) Camera.y = 0;
	if (Camera.x > Camera.w) Camera.x = Camera.w;
	if (Camera.y > Camera.h) Camera.y = Camera.h;
	
}



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

	for (auto& c : colliders)
	{
		c->draw();
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
