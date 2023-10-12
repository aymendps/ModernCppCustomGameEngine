#include "EntityManager.h"

void EntityManager::Update(const float deltaTime)
{
	for (auto& entity : _entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (auto& entity : _entities) {
		entity->Render();
	}
}

void EntityManager::Refresh()
{
	// Using the erase-remove idiom to remove entities that are not active
	_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
		[](const std::unique_ptr<Entity>& entityPtr) {
			return !entityPtr->IsActive();
		}), 
		std::end(_entities));
}

Entity& EntityManager::CreateEntity()
{
	// Add a new entity to the vector then return a reference to it
	auto entity = std::unique_ptr<Entity>(new Entity());
	_entities.push_back(std::move(entity));

	return *_entities.back();
}
