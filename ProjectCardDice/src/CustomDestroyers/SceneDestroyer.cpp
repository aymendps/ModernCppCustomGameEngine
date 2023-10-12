#include "SceneDestroyer.h"

void SceneDestroyer::operator()(Scene* scene)
{
	scene->Destroy();
}
