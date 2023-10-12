#include "GameDestroyer.h"
#include "../Game.h"

void GameDestroyer::operator()(Game* game)
{
	game->Destroy();
}
