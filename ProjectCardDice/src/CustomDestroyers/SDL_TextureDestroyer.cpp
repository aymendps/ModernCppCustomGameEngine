#include "SDL_TextureDestroyer.h"
#include <SDL.h>
#include <iostream>

void SDL_TextureDestroyer::operator()(SDL_Texture* texture)
{
	std::cout << "Destroying a texture that was rendered..." << std::endl;
	SDL_DestroyTexture(texture);
}
