#pragma once

struct SDLWindowDestroyer
{
	void operator()(struct SDL_Window* window);
};

