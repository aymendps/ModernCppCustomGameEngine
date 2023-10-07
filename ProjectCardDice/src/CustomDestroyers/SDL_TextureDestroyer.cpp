#include "SDL_TextureDestroyer.h"
#include <iostream>

void SDL_TextureDestroyer::operator()(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}
