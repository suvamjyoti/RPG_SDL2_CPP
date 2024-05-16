#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"


class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, DestR;

	TransformComponent* transform_p;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init() override
	{
		if (!entity_p->hasComponent<TransformComponent>())
		{
			entity_p->addComponent<TransformComponent>();
		}

		transform_p = &entity_p->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/map/CollisionBorder.png");
		srcR = { 0,0,32,32 };
		DestR = { collider.x,collider.y,collider.w,collider.h };
	}

	void update() override
	{
		if (tag != "terrain")
		{

			collider.x = static_cast<int> (transform_p->position.x);
			collider.y = static_cast<int> (transform_p->position.y);
			collider.w = static_cast<int> (transform_p->width * transform_p->scale);
			collider.h = static_cast<int> (transform_p->height * transform_p->scale);
		}

		DestR.x = collider.x - Game::Camera.x;
		DestR.y = collider.y - Game::Camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, DestR, SDL_FLIP_NONE);
	}
};
