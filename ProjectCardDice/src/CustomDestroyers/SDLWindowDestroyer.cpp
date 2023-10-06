#include "SDLWindowDestroyer.h"

void SDLWindowDestroyer::operator()(SDL_Window* window)
{
	std::cout << "Destroying Game Window..." << std::endl;
	SDL_DestroyWindow(window);
	std::cout << "Game Window was destroyed!" << std::endl;
}