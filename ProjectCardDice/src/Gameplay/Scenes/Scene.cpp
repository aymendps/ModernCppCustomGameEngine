#include "Scene.h"

void Scene::Destroy()
{
	for (auto& entity : _createdEntities)
	{
		entity->Destroy();
	}
}
