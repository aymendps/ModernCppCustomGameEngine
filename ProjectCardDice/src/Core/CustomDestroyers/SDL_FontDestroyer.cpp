#include "SDL_FontDestroyer.h"
#include <SDL.h>
#include "../Utils/Logger.h"

void SDL_FontDestroyer::operator()(SDL_Font* font)
{
	Logger::LogLine(LogType::EngineRelated, "Destroying a font that was rendered...");
	SDL_DestroyTexture(font->texture);
}
