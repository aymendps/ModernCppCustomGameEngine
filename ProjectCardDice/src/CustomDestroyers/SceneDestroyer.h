#pragma once
#include "../Scenes/Scene.h"

struct SceneDestroyer
{
	void operator()(Scene* scene);
};

