#include <SDL.h>
#include <memory>
#include "Game.h"
#include "CustomDestroyers/GameDestroyer.h"

constexpr const char* GAME_TITLE = "Project Card Dice";
constexpr int GAME_HEIGHT = 1080;
constexpr int GAME_WIDTH = 1920;
constexpr bool GAME_FULLSCREEN = true;

int main(int argc, char* argv[])
{
	auto game = std::unique_ptr<Game, GameDestroyer>(new Game);
	
	game->Init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, GAME_FULLSCREEN);

	Uint64 oldTime = SDL_GetTicks64();

	while (game->IsRunning()) {
		Uint64 newTime = SDL_GetTicks64();
		float deltaTime = (newTime - oldTime) / 1000.0f;

		game->HandleEvents();
		game->Update(deltaTime);
		game->Render();

		SDL_Delay(1);

		oldTime = newTime;
	}

	return 0;
}