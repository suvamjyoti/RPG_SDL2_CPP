#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB)
{
	if (AABB(colliderA.collider, colliderB.collider))
	{
		std::cout << colliderA.tag << "  HIT  " << colliderB.tag << std::endl;

		return true;
	}

	return false;
}