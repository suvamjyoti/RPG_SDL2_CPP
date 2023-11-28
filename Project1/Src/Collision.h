#pragma once

#include "SDL.h"

class Collision
{
public:
	//axis aligned bounding box
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);		
	
};
