#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent :public Component
{
public:
	TransformComponent* transform_p;
	SpriteComponent* sprite_p;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "Assets/map/dirt.png";
			break;
		case 1:
			path = "Assets/map/grass.png";
			break;
		case 2:
			path = "Assets/map/water.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity_p->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform_p = &(entity_p->getComponent<TransformComponent>());
		
		entity_p->addComponent<SpriteComponent>(path);
		sprite_p = &(entity_p->getComponent<SpriteComponent>());

	}

};