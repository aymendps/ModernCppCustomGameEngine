#include "TextureManager.h"
#include "Game.h"

SDL_Texture* const TextureManager::LoadTexture(const char* filePath)
{
	SDL_Surface* surface = IMG_Load(filePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::RenderTexture(SDL_Texture* const texture, SDL_Rect* const source, SDL_Rect* const destination)
{
	SDL_RenderCopy(Game::renderer, texture, source, destination);
}
