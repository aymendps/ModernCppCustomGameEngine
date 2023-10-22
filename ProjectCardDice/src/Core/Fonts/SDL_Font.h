#pragma once

enum class FontFamily {
	Goudy,
	Arial
};

struct SDL_Texture;

struct SDL_Font
{
	SDL_Texture* texture;
	int width;
	int height;
};

