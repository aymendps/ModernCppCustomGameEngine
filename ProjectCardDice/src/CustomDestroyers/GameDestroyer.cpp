#include "GameDestroyer.h"
#include "../Core/Game.h"

void GameDestroyer::operator()(Game* game)
{
	game->Destroy();
}
