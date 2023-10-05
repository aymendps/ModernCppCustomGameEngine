#include <SDL.h>
#include <memory>
#include "CustomDestroyers/SDLWindowDestroyer.h"
#include "CustomDestroyers/SDLRendererDestroyer.h"

inline const char* const GAME_TITLE = "Project Card Dice";
inline int const GAME_HEIGHT = 1080;
inline int const GAME_WIDTH = 1920;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto window = std::unique_ptr<SDL_Window, SDLWindowDestroyer>(SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP));

	auto renderer = std::unique_ptr<SDL_Renderer, SDLRendererDestroyer>(SDL_CreateRenderer(window.get(), -1, 0));

	SDL_SetRenderDrawColor(renderer.get(), 0, 255, 0, 255);

	SDL_RenderClear(renderer.get());

	SDL_RenderPresent(renderer.get());

	SDL_Delay(10000);

	return 0;
}