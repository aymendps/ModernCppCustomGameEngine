#pragma once
#include <SDL.h>
#include <iostream>

struct SDLWindowDestroyer
{
	void operator()(SDL_Window* window);
};

