#include "SDLRendererDestroyer.h"
#include <SDL.h>

void SDLRendererDestroyer::operator()(SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
}
