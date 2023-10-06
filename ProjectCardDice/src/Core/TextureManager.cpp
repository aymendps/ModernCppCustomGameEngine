#include "TextureManager.h"

SDL_Texture* const TextureManager::LoadTexture(const char* filePath, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(filePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}
