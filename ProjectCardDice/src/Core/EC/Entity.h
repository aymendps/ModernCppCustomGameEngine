#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"

class Entity
{
	friend class EntityManager;

public:
	/// <summary>
	/// Handles the events of the entity's components like SDL events and inputs.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	void HandleEvents(union SDL_Event& event);

	/// <summary>
	/// Runs every frame and updates the entitiy's components.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	void Update(const float deltaTime);

	/// <summary>
	/// Runs every frame and renders the entity's components and should be called after updating the entity.
	/// </summary>
	void Render();

	/// <summary>
	/// Destroys the entity and all of its components.
	/// </summary>
	void Destroy();

	/// <summary>
	/// Returns whether or not the entity is active.
	/// </summary>
	/// <returns>True if the entity is active, false otherwise</returns>
	bool IsActive() const { return _isActive; }

	/// <summary>
	/// Returns the unique name of the entity that was used when creating it.
	/// </summary>
	/// <returns>A string containing the unique name of the entity</returns>
	std::string GetUniqueName() const { return _uniqueName; }
	
	/// <summary>
	/// Returns whether or not the entity has a component of the given type.
	/// </summary>
	/// <typeparam name="T">The component's type</typeparam>
	/// <returns>True if the entity has a component of the given type, false otherwise</returns>
	template <typename T> requires ComponentType<T>
	bool HasComponent() const { return _componentSignatures[GetComponentTypeID<T>()]; }

	/// <summary>
	/// Adds a component of the given type to the entity.
	/// </summary>
	/// <typeparam name="T">The component's type</typeparam>
	/// <typeparam name="...TArgs">The component's constructor arguments</typeparam>
	/// <param name="...args">The component's constructor arguments excluding the owner entity and component type id which are passed automatically</param>
	/// <returns>A pointer to the newly created component</returns>
	template <typename T, typename... TArgs> requires ComponentType<T>
	T* AddComponent(TArgs&&... args) 
	{
		// Check if the entity already has a component of the given type
		if (HasComponent<T>()) {
			Logger::LogLine(LogType::Warning, "Entity '", _uniqueName, "' already has a component of type: ", typeid(T).name());
			return GetComponent<T>();
		}

		// Mark that the entity has a component of the given type
		ComponentTypeID ID = GetComponentTypeID<T>();
		_componentSignatures[ID] = true;

		// Create the new component, add it to related containers to keep track of it, and initialize it
		_components.push_back(std::make_unique<T>(this, ID, std::forward<TArgs>(args)...));
		_componentIdToPointer[ID] = _components.back().get();
		_components.back()->Init();	

		// Return a reference from _components.back() which is a unique_ptr so can't use static_pointer_cast
		return static_cast<T*>(_components.back().get());
	};

	/// <summary>
	/// Retrieves a pointer to the component of the given type.
	/// </summary>
	/// <typeparam name="T">The component's type</typeparam>
	/// <returns>A pointer to the component of the given type</returns>
	template<typename T> requires ComponentType<T>
	T* GetComponent() const
	{
		return static_cast<T*>(_componentIdToPointer[GetComponentTypeID<T>()]);
	}

	/// <summary>
	/// Removes the component of the given type from the entity.
	/// </summary>
	/// <typeparam name="T">Type of the component to remove</typeparam>
	/// <returns>True if the component was removed, false otherwise</returns>
	template<typename T> requires ComponentType<T>
	bool RemoveComponent()
	{
		if(!HasComponent<T>()) {
			Logger::LogLine(LogType::ComponentRelated, "Cannot remove component because Entity '", _uniqueName, "' does not have a component of type : ", typeid(T).name());
			return false;
		}

		ComponentTypeID ID = GetComponentTypeID<T>();

		_componentSignatures[ID] = false;
		_componentIdToPointer[ID] = nullptr;

		_components.erase(std::remove_if(_components.begin(), _components.end(), [ID](const std::unique_ptr<Component>& component) {
			return component->GetTypeID() == ID;
		}), _components.end());
		
		return true;
	}

private:
	Entity(const std::string& uniqueName);

	std::string _uniqueName;
	std::vector<std::unique_ptr<Component>> _components;
	ComponentArray _componentIdToPointer;
	ComponentBitset _componentSignatures;
	// When this is set to false, the entity will be destroyed in the next refresh.
	bool _isActive;
};