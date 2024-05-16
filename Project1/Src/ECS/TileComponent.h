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
	Vector2D position;

	TileComponent() = default;

	TileComponent(int srcX,int srcY,int xpos,int ypos,int tsize,int tscale,const char* tileMapPath)
	{
		texture = TextureManager::LoadTexture(tileMapPath);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.h = srcRect.w = tsize;
		
		position.x = xpos;
		position.y = ypos;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.h = destRect.w = tsize * tscale;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void update() override
	{
		destRect.x = position.x - Game::Camera.x;
		destRect.y = position.y - Game::Camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE,false);
	}

};