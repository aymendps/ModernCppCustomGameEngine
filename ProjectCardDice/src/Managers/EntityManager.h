#pragma once
#include "../EC/Entity.h"

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
	Entity& CreateEntity();

private:
	std::vector<std::unique_ptr<Entity>> _entities;

	// private constructor because of singleton
	EntityManager() {};
};

