#include "GameDestroyer.h"

void GameDestroyer::operator()(Game* game)
{
	game->_window.reset();
	game->_renderer.reset();
	game->Clean();
}
