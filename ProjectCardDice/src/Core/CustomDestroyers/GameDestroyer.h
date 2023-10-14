#pragma once

struct GameDestroyer
{
	void operator()(class Game* game);
};

