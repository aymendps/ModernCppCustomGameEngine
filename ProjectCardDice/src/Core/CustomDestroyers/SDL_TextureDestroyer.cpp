#include "SDL_TextureDestroyer.h"
#include <SDL.h>
#include "../Utils/Logger.h"

void SDL_TextureDestroyer::operator()(SDL_Texture* texture)
{
	Logger::LogLine(LogType::EngineRelated, "Destroying a texture that was rendered...");
	SDL_DestroyTexture(texture);
}
