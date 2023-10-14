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
	// Using the erase-remove idiom to remove entities that are not active from the vector of entities
	_entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
		[](const std::shared_ptr<Entity>& entityPtr) {
			return !entityPtr->IsActive();
		}), 
		std::end(_entities));

	// Remove all entities that are not active from the map of entities by unique name
	// (Don't forget: Can't use remove_if on associative containers)
	for (auto it = _entitiesByUniqueName.begin(); it != _entitiesByUniqueName.end();) {
		if (!it->second->IsActive()) {
			// Proceed to next valid iterator after erasing
			it = _entitiesByUniqueName.erase(it);
		}
		else {
			++it;
		}
	}
}

Entity& EntityManager::CreateEntity(const std::string uniqueName)
{
	// Check if an entity with the given unique name already exists
	if (auto checkEntity = GetEntity(uniqueName); checkEntity != nullptr) {
		std::cout << "Entity with unique name '" << uniqueName << "' already exists!" << std::endl;
		return *checkEntity;
	}

	auto newEntity { std::shared_ptr<Entity>(new Entity()) };
	newEntity->_uniqueName = uniqueName;

	// Add the entity to the vector of entities so it can be updated and rendered
	_entities.push_back(std::move(newEntity));

	// Add the entity to the map so it can be found by its unique name
	_entitiesByUniqueName[uniqueName] = _entities.back();

	return *_entities.back();
}

Entity* EntityManager::GetEntity(const std::string uniqueName) const
{
	// Find the entity with the given unique name in the map
	auto entity = _entitiesByUniqueName.find(uniqueName);

	// If the entity was found, return a pointer to it
	if (entity != _entitiesByUniqueName.end()) {
		return entity->second.get();
	}

	// If the entity was not found, return a nullptr
	return nullptr;
}
