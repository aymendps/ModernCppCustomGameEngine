#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "../Fonts/SDL_Font.h"

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
	/// Loads and creates a font texture using the given parameters.
	/// </summary>
	/// <param name="font">Font family to use</param>
	/// <param name="fontSize">Font size to use</param>
	/// <param name="text">Text to render</param>
	/// <param name="bold">Whether or not to render the text in bold</param>
	/// <param name="outlineSize">Size of the outline to use. 0 for no outline</param>
	/// <param name="wrapLength">Length to wrap the text at. 0 for no wrapping</param>
	/// <param name="color">Color to render the text in. This is white by default</param>
	/// <returns>Pointer to the loaded font texture</returns>
	static SDL_Font* const LoadFontTexture(FontFamily font, int fontSize, const char* text, bool bold = false, int outlineSize = 1,
		int wrapLength = 0, SDL_Color color = {255, 255, 255});

	/// <summary>
	/// Renders a texture to the screen.
	/// </summary>
	/// <param name="texture">Pointer to the texture to be rendered</param>
	/// <param name="destination"Destination rect to use</param>
	/// <param name="source">Source rect to use, if any. This default to nullptr and uses the entire texture</param>
	/// <param name="flip">Flip mode to use, if any. This defaults to SDL_FLIP_NONE</param>
	static void RenderTexture(SDL_Texture* const texture, SDL_Rect* const destination, SDL_Rect* const source = nullptr,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	static const std::unordered_map<FontFamily, const char*> _fontPaths;
};

