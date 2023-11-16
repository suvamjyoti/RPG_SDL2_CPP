#pragma once

#include "../../SDL2/include/SDL.h"
#include "../../Src/TextureManager.h"
#include "PositionComponent.h"

class SpriteComponent : public Component
{
private: 

	PositionComponent* positionComponentPointer;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int cnt = 0;

public:

	void init() override
	{
		positionComponentPointer = &(entityPointer->getComponent<PositionComponent>());

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;

	}

	SpriteComponent() = default;
	
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}



	void update() override
	{
		destRect.x = positionComponentPointer->x();
		destRect.y = positionComponentPointer->y();
		//destRect.x = cnt++;
		//destRect.y = cnt++;

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}



};

