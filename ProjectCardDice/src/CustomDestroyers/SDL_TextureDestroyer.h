#pragma once
#include <SDL.h>

struct SDL_TextureDestroyer
{
	void operator()(SDL_Texture* texture);
};

