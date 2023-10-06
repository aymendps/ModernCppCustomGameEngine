#pragma once
#include <SDL.h>
#include <iostream>

struct SDLRendererDestroyer
{
	void operator()(SDL_Renderer* renderer);
};

