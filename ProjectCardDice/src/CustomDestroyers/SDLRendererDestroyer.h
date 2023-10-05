#pragma once
struct SDLRendererDestroyer
{
	void operator()(struct SDL_Renderer* renderer);
};

