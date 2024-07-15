#pragma once
#include "../EC/Entity.h"
#include <unordered_map>
#include <vector>
#include <string>

class EntityManager
{
public:
	//Delete copy/move of singleton instance
	EntityManager(EntityManager& other) = delete;
	void operator=(const EntityManager&) = delete;

	// Singleton instance.
	static EntityManager& GetInstance() {
		static EntityManager instance;
		return instance;
	}

	/// <summary>
	/// Handles the events of all entities like SDL events and inputs.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	void HandleEvents(union SDL_Event& event);

	/// <summary>
	/// Runs every frame and updates all entities.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	void Update(const float deltaTime);

	/// <summary>
	/// Runs every frame and renders all entities.
	/// </summary>
	void Render();

	/// <summary>
	/// Removes all entities that are marked for deletion.
	/// </summary>
	void Refresh();

	/// <summary>
	/// Creates a new entity.
	/// </summary>
	/// <param name="uniqueName">The unique name to use when creating the entity</param>
	/// <returns>A pointer to the newly created entity</returns>
	Entity* CreateEntity(const std::string& uniqueName);

	/// <summary>
	/// Retrieves an entity by its unique name.
	/// </summary>
	/// <param name="uniqueName">The unique name used when creating the entity</param>
	/// <returns>A pointer to the entity with the given unique name, or nullptr if not found</returns>
	Entity* GetEntity(const std::string& uniqueName) const;

	/// <summary>
	/// Retrieves all entities.
	/// </summary>
	/// <returns>A vector containing pointers to all entities</returns>
	std::vector<Entity*> GetAllEntities() const;

	/// <summary>
	/// Retrieves all entities that have a specific component.
	/// </summary>
	/// <typeparam name="T">The type of component to look for</typeparam>
	/// <returns>A vector containing pointers to all entities that have the specified component</returns>
	template <typename T>
	std::vector<Entity*> GetEntitiesWithComponent() const {
		std::vector<Entity*> entitiesWithComponent;
		for (auto& entityEntry : _entitiesByUniqueName) {
			if (entityEntry.second->HasComponent<T>()) {
				entitiesWithComponent.push_back(entityEntry.second.get());
			}
		}
		return entitiesWithComponent;
	}

	/// <summary>
	/// Marks the entity with the given unique name for deletion, so it can be removed in the next refresh.
	/// </summary>
	/// <param name="uniqueName">The unique name used when creating the entity</param>
	/// <returns>True if the entity was found and marked for deletion, False otherwise</returns>
	bool DestroyEntity(const std::string& uniqueName);

	/// <summary>
	/// Marks all the entities for deletion, so they can be removed in the next refresh.
	/// </summary>
	void DestroyAllEntities();

private:
	std::unordered_map<std::string, std::unique_ptr<Entity>> _entitiesByUniqueName;

	// private constructor because of singleton
	EntityManager() = default;
};

/// <summary>
/// Shorthand function to create a new entity using the entity manager.
/// </summary>
/// <param name="uniqueName">The unique name to use when creating the entity</param>
/// <returns>A pointer to the newly created entity</returns>
inline Entity* CreateEntity(const std::string& uniqueName) {
	return EntityManager::GetInstance().CreateEntity(uniqueName);
}

/// <summary>
/// Shorthand function to get an existing entity using the entity manager.
/// </summary>
/// <param name="uniqueName">The unique name used when creating the entity</param>
/// <returns>A pointer to the entity with the given unique name, or nullptr if not found</returns>
inline Entity* GetEntity(const std::string& uniqueName) {
	return EntityManager::GetInstance().GetEntity(uniqueName);
}

/// <summary>
/// Shorthand function to get all entities using the entity manager.
/// </summary>
/// <returns>A vector containing pointers to all entities</returns>
inline std::vector<Entity*> GetAllEntities() {
	return EntityManager::GetInstance().GetAllEntities();
}

/// <summary>
/// Shorthand function to get all entities that have a specific component using the entity manager.
/// </summary>
/// <typeparam name="T">The type of component to look for</typeparam>
/// <returns>A vector containing pointers to all entities that have the specified component</returns>
template <typename T>
inline std::vector<Entity*> GetEntitiesWithComponent() {
	return EntityManager::GetInstance().GetEntitiesWithComponent<T>();
}

/// <summary>
/// Shorthand function to destroy an existing entity using the entity manager.
/// </summary>
/// <param name="uniqueName"> The unique name used when creating the entity</param>
/// <returns>True if the entity was found and marked for deletion, False otherwise</returns>
inline bool DestroyEntity(const std::string& uniqueName) {
	return EntityManager::GetInstance().DestroyEntity(uniqueName);
}

/// <summary>
/// Shorthand function to destroy all entities using the entity manager.
/// </summary>
inline void DestroyAllEntities() {
	EntityManager::GetInstance().DestroyAllEntities();
}

