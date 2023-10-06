#pragma once
#include "../Core/Game.h"

struct GameDestroyer
{
	void operator()(Game* game);
};

