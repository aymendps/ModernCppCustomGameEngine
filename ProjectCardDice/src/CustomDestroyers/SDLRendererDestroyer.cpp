#include "SDLRendererDestroyer.h"

void SDLRendererDestroyer::operator()(SDL_Renderer* renderer)
{
	std::cout << "Destroying Game Renderer..." << std::endl;
	SDL_DestroyRenderer(renderer);
	std::cout << "Game Renderer was destroyed!" << std::endl;
}
