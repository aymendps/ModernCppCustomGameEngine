#pragma once

struct GameDestroyer
{
	void operator()(struct Game* game);
};

