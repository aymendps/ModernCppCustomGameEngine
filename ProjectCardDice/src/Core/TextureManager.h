#pragma once
#include <SDL.h>
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
	static SDL_Texture* const LoadTexture(const char* filePath, SDL_Renderer* renderer);
};

