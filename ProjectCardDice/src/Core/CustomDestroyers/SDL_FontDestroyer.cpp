#include "SDL_FontDestroyer.h"
#include <SDL.h>
#include <iostream>

void SDL_FontDestroyer::operator()(SDL_Font* font)
{
	std::cout << "Destroying a font that was rendered..." << std::endl;
	SDL_DestroyTexture(font->texture);
}
