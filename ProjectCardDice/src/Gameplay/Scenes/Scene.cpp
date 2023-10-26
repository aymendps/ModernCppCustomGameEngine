#include "Scene.h"
#include "../Collections/CardCollection.h"
#include "../../Core/Managers/EntityManager.h"

void Scene::Render()
{
	EntityManager::GetInstance().Render();
}

void Scene::Destroy()
{
	for (auto& entity : _createdEntities)
	{
		entity->Destroy();
	}
}

Entity& Scene::CreateEntity(const std::string name)
{
	Entity& entity = EntityManager::GetInstance().CreateEntity(name);
	_createdEntities.insert(&entity);
	return entity;
}

Entity& Scene::CreateCardEntity(CardEntityUniqueID uniqueID, const std::string name)
{
	Entity& entity = CardCollection::GetInstance().CreateCardEntity(uniqueID, name);
	_createdEntities.insert(&entity);
	return entity;
}

Entity& Scene::CreateRandomCardEntity(const std::string name)
{
	Entity& entity = CardCollection::GetInstance().CreateRandomCardEntity(name);
	_createdEntities.insert(&entity);
	return entity;
}
