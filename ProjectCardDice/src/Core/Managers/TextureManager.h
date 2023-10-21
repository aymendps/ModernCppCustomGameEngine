#pragma once
#include <SDL_image.h>

class TextureManager
{
public:
	/// <summary>
	/// Loads a texture from a file.
	/// </summary>
	/// <param name="filePath">Path to the file to be loaded</param>
	/// <param name="renderer">Pointer to the game's renderer</param>
	/// <returns>Pointer to the loaded texture</returns>
	static SDL_Texture* const LoadTexture(const char* filePath);

	/// <summary>
	/// Renders a texture to the screen.
	/// </summary>
	/// <param name="texture">Pointer to the texture to be rendered</param>
	/// <param name="destination"Destination rect to use</param>
	/// <param name="source">Source rect to use, if any. This default to nullptr and uses the entire texture</param>
	/// <param name="flip">Flip mode to use, if any. This defaults to SDL_FLIP_NONE</param>
	static void RenderTexture(SDL_Texture* const texture, SDL_Rect* const destination, SDL_Rect* const source = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
};

