#include <SDL.h>
#include <memory>
#include "Game.h"
#include "Core/CustomDestroyers/GameDestroyer.h"

int main(int argc, char* argv[])
{
	auto game = std::unique_ptr<Game, GameDestroyer>(new Game);
	
	game->Init();

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