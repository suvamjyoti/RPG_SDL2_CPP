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
	
	bool animated = false;
	int frame = 0;
	int speed = 100;		//delay between frames in miliseconds
	std::string  filepath;

public:

	void init() override
	{
		//get the transform component form the entity by derefrencing entity pointer
		transformComponentPointer = &(entity_p->getComponent<TransformComponent>());

		srcRect.x = srcRect.y = 100;
		srcRect.w = transformComponentPointer->width;
		srcRect.h = transformComponentPointer->height;

		destRect.w = transformComponentPointer->width * transformComponentPointer->scale;
		destRect.h = transformComponentPointer->height * transformComponentPointer->scale;

	}

	SpriteComponent() = default;
	
	SpriteComponent(const char* path)
	{
		SetTeture(path);
	}

	SpriteComponent(const char* path,int mFrames,int mSpeed)
	{
		animated = true;
		frame = mFrames;
		speed = mSpeed;
		filepath = path;
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
		if(animated)
		{
			std::string mFilePath = filepath;
			mFilePath += std::to_string((SDL_GetTicks()/speed) %frame);
			mFilePath += ".png";
			SetTeture(mFilePath.c_str());
		}

		destRect.x = static_cast<int>(transformComponentPointer->position.x);
		destRect.y = static_cast<int>(transformComponentPointer->position.y);
		destRect.w = (transformComponentPointer->width * transformComponentPointer->scale);
		destRect.h = (transformComponentPointer->height * transformComponentPointer->scale);

		//destRect.x = cnt++;
		//destRect.y = cnt++;

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}



};

