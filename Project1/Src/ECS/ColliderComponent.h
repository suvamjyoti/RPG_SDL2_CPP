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

	TransformComponent* transform_p;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity_p->hasComponent<TransformComponent>())
		{
			entity_p->addComponent<TransformComponent>();
		}

		transform_p = &entity_p->getComponent<TransformComponent>();

		if (tag != "player")
		{
			Game::colliders.push_back(this);
		}
	}

	void update() override
	{
		collider.x = static_cast<int> (transform_p->position.x);
		collider.y = static_cast<int> (transform_p->position.y);
		collider.w = static_cast<int> (transform_p->width * transform_p->scale);
		collider.h = static_cast<int> (transform_p->height * transform_p->scale);
	}
};
