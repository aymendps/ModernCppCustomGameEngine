#include "GameDestroyer.h"

void GameDestroyer::operator()(Game* game)
{
	game->Destroy();
}
