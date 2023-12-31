#pragma once
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet,int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);
	objTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = 64;
	srcRect.w = 64;

	
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w*2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}