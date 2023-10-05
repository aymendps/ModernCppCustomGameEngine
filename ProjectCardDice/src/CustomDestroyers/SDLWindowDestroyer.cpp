#include "SDLWindowDestroyer.h"
#include <SDL.h>

void SDLWindowDestroyer::operator()(SDL_Window* window)
{
	SDL_DestroyWindow(window);
}