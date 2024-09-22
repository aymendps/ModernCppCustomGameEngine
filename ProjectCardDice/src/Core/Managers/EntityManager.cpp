#include "EntityManager.h"

void EntityManager::HandleEvents(SDL_Event& event)
{
	for (auto& entityEntry : _entitiesByUniqueName) {
		entityEntry.second->HandleEvents(event);
	}
}

void EntityManager::Update(const float deltaTime)
{
	for (auto& entityEntry : _entitiesByUniqueName) {
		entityEntry.second->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (auto& entityEntry : _entitiesByUniqueName) {
		entityEntry.second->Render();
	}
}

void EntityManager::Refresh()
{
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

Entity* EntityManager::CreateEntity(const std::string& uniqueName)
{
	// Check if an entity with the given unique name already exists
	if (auto checkEntity = GetEntity(uniqueName); checkEntity != nullptr) {
		std::cout << "\033[31m" << "Entity with unique name '" << uniqueName << "' already exists!" << "\033[0m" << std::endl;
		return checkEntity;
	}

	// Create a new entity with the given unique name and add it to the map
	_entitiesByUniqueName[uniqueName] = std::move(std::unique_ptr<Entity>{new Entity(uniqueName)});

	return _entitiesByUniqueName[uniqueName].get();
}

Entity* EntityManager::GetEntity(const std::string& uniqueName) const
{
	// Check if an entity with the given unique name exists and return it if found, otherwise return nullptr
	if (_entitiesByUniqueName.contains(uniqueName)) {
		return _entitiesByUniqueName.at(uniqueName).get();
	}

	return nullptr;
}

std::vector<Entity*> EntityManager::GetAllEntities() const
{
	std::vector<Entity*> entities;

	// Iterate through all entities in the map and add them to the vector
	for (auto& entityEntry : _entitiesByUniqueName) {
		entities.push_back(entityEntry.second.get());
	}

	return entities;
}

bool EntityManager::DestroyEntity(const std::string& uniqueName)
{
	// Check if an entity with the given unique name exists and destroy it if found (returning true), otherwise return false
	if (_entitiesByUniqueName.contains(uniqueName)) {
		_entitiesByUniqueName[uniqueName]->Destroy();
		return true;
	}

	return false;
}

void EntityManager::DestroyAllEntities()
{
	std::cout << "Destroying all entities within the current Scene" << std::endl;
	
	for (auto& entityEntry : _entitiesByUniqueName) {
		entityEntry.second->Destroy();
	}
}
