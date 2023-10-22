#pragma once
#include "../Fonts/SDL_Font.h"

struct SDL_FontDestroyer
{
	void operator()(SDL_Font* font);
};

