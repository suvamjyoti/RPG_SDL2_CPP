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

	TransformComponent* transformPointer;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entityPointer->hasComponent<TransformComponent>())
		{
			entityPointer->addComponent<TransformComponent>();
		}

		transformPointer = &entityPointer->getComponent<TransformComponent>();
	}

	void update() override
	{
		collider.x = static_cast<int> (transformPointer->position.x);
		collider.y = static_cast<int> (transformPointer->position.y);
		collider.w = static_cast<int> (transformPointer->width * transformPointer->scale);
		collider.h = static_cast<int> (transformPointer->height * transformPointer->scale);
	}
};
