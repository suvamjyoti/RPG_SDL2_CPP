#pragma once

#include "../../SDL2/include/SDL.h"
#include "../TextureManager.h"
#include "TransformComponent.h"
#include <string>

class SpriteComponent : public Component
{
private: 

	TransformComponent* transformComponentPointer;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	
	void init() override
	{
		//get the transform component form the entity by derefrencing entity pointer
		transformComponentPointer = &(entity_p->getComponent<TransformComponent>());

		srcRect.x = srcRect.y = 0;
		srcRect.w = transformComponentPointer->width;
		srcRect.h = transformComponentPointer->height;

		destRect.w = transformComponentPointer->width * transformComponentPointer->scale;
		destRect.h = transformComponentPointer->height * transformComponentPointer->scale;

	}

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	
	SpriteComponent(const char* path)
	{
		SetTeture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void SetTeture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void update() override
	{

		destRect.x = static_cast<int>(transformComponentPointer->position.x);
		destRect.y = static_cast<int>(transformComponentPointer->position.y);
		destRect.w = (transformComponentPointer->width * transformComponentPointer->scale);
		destRect.h = (transformComponentPointer->height * transformComponentPointer->scale);

		//destRect.x = cnt++;
		//destRect.y = cnt++;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect,spriteFlip,true);
	}



};

