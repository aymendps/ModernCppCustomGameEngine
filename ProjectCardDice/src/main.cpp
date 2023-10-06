#include <SDL.h>
#include <memory>
#include "Core/Game.h"
#include "CustomDestroyers/GameDestroyer.h"

inline const char* const GAME_TITLE = "Project Card Dice";
inline int const GAME_HEIGHT = 1080;
inline int const GAME_WIDTH = 1920;
inline bool const GAME_FULLSCREEN = true;

int main(int argc, char* argv[])
{
	auto game = std::unique_ptr<Game, GameDestroyer>(new Game);
	
	game->Init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, GAME_FULLSCREEN);

	while (game->IsRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	return 0;
}