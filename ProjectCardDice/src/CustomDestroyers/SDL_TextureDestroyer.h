#pragma once

struct SDL_TextureDestroyer
{
	void operator()(struct SDL_Texture* texture);
};

