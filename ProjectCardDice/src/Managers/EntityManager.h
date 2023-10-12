#pragma once
#include "../EC/Entity.h"
#include <unordered_map>
#include <string>

class EntityManager
{
public:
	// Delete copy/move of singleton instance
	EntityManager(EntityManager& other) = delete;
	void operator=(const EntityManager&) = delete;

	// Singleton instance
	static EntityManager& GetInstance() {
		static EntityManager instance;
		return instance;
	}

	/// <summary>
	/// Runs every frame and updates all entities
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	void Update(const float deltaTime);

	/// <summary>
	/// Runs every frame and renders all entities
	/// </summary>
	void Render();

	/// <summary>
	/// Removes all entities that are marked for deletion
	/// </summary>
	void Refresh();

	/// <summary>
	/// Creates a new entity and returns a reference to it
	/// </summary>
	Entity& CreateEntity(const std::string uniqueName);

	/// <summary>
	/// Returns a reference to the entity with the given unique name
	/// </summary>
	/// <param name="uniqueName">The unique name used when creating the entity</param>
	Entity* GetEntity(const std::string uniqueName) const;

private:
	std::vector<std::shared_ptr<Entity>> _entities;
	std::unordered_map<std::string, std::shared_ptr<Entity>> _entitiesByUniqueName;

	// private constructor because of singleton
	EntityManager() {};
};

