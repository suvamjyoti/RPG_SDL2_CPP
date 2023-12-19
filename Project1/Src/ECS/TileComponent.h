#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent :public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

	TileComponent(int srcX,int srcY,int xpos,int ypos,const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.h = srcRect.w = 32;
		
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.h = destRect.w = 32;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE,false);
	}

};