#include "TextureManager.h"
#include "../../Game.h"

const std::unordered_map<FontFamily, const char*> TextureManager::_fontPaths = {
	{ FontFamily::Goudy, "assets/fonts/goudy.ttf" },
	{ FontFamily::Arial, "assets/fonts/arial.ttf" }
};

SDL_Texture* const TextureManager::LoadTexture(const char* filePath)
{
	auto surface = IMG_Load(filePath);
	auto texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Font* const TextureManager::LoadFontTexture(FontFamily font, int fontSize, const char* text, bool bold, int outlineSize,
	int wrapLength, SDL_Color color)
{
	auto ttfFont = TTF_OpenFont(_fontPaths.at(font), fontSize);
	auto ttfOutline = TTF_OpenFont(_fontPaths.at(font), fontSize);
	TTF_SetFontOutline(ttfOutline, outlineSize);

	if (ttfFont == nullptr || ttfOutline == nullptr) {
		std::cout << "\033[31m" << "Failed to load font " << _fontPaths.at(font) << " with reason: " << TTF_GetError() << "\033[0m" << std::endl;
		return nullptr;
	}

	if (bold) {
		TTF_SetFontStyle(ttfFont, TTF_STYLE_BOLD);
		TTF_SetFontStyle(ttfOutline, TTF_STYLE_BOLD);
	}
	
	// Create the main surface depending on whether or not we want to wrap the text
	auto surface = wrapLength != 0 ? TTF_RenderUTF8_Blended_Wrapped(ttfFont, text, color, wrapLength)
		: TTF_RenderUTF8_Blended(ttfFont, text, color);

	// Create the outline surface depending on whether or not we want to wrap the text
	auto outlineSurface = wrapLength != 0 ? TTF_RenderUTF8_Blended_Wrapped(ttfOutline, text, { 0, 0, 0 }, wrapLength)
		: TTF_RenderUTF8_Blended(ttfOutline, text, { 0, 0, 0 });

	// Add the main surface on top of the outline surface
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	SDL_Rect blitRect = { outlineSize, outlineSize, surface->w, surface->h };
	SDL_BlitSurface(surface, nullptr, outlineSurface, &blitRect);

	// Create the texture from the outline surface now that it has the main surface on top of it
	auto texture = SDL_CreateTextureFromSurface(Game::renderer, outlineSurface);

	// Using new here because this function does not own the pointer, the caller does and is responsible for deleting it
	SDL_Font* finalFont = new SDL_Font { texture, surface->w, surface->h };

	SDL_FreeSurface(surface);
	SDL_FreeSurface(outlineSurface);
	TTF_CloseFont(ttfFont);
	TTF_CloseFont(ttfOutline);

	return finalFont;
}

void TextureManager::RenderTexture(SDL_Texture* const texture, SDL_Rect* const destination, SDL_Rect* const source, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, source, destination, 0.0, nullptr, flip);
}
