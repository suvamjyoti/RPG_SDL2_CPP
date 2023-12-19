#pragma once
#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager:: Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip, bool isSprite)
{
	if (isSprite)
	{
		SDL_RenderCopyEx(Game::renderer, tex, NULL, &dst, NULL, NULL, flip);
		return;
	}

	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst,NULL,NULL,flip);
}
