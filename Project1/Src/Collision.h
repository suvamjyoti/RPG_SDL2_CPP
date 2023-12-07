#pragma once

#include "SDL.h"

class ColliderComponent;

class Collision
{
public:
	//axis aligned bounding box
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);
};
