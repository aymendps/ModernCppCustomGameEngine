#include <SDL.h>
#include <memory>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game {};
	
	Uint64 oldTime = SDL_GetTicks64();
	
	game.Init();

	while (game.IsRunning()) {
		Uint64 newTime = SDL_GetTicks64();
		float deltaTime = (newTime - oldTime) / 1000.0f;

		game.HandleEvents();
		game.Update(deltaTime);
		game.Render();

		SDL_Delay(1);

		oldTime = newTime;
	}

	game.Destroy();

	return 0;
}