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
	/// <param name="...args">The component's constructor arguments excluding the entity (owner) pointer which is passed automatically</param>
	/// <returns>A pointer to the newly created component</returns>
	template <typename T, typename... TArgs> requires ComponentType<T>
	T* AddComponent(TArgs&&... args) 
	{
		// Check if the entity already has a component of the given type
		if (HasComponent<T>()) {
			std::cout << "\033[31m" << "Entity '" << _uniqueName << "' already has a component of type : " << typeid(T).name() << "\033[0m" << std::endl;
			return GetComponent<T>();
		}

		// Mark that the entity has a component of the given type
		ComponentTypeID ID = GetComponentTypeID<T>();
		_componentSignatures[ID] = true;

		// Create the new component, add it to related containers to keep track of it, and initialize it
		_components.push_back(std::make_unique<T>(this, std::forward<TArgs>(args)...));
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

private:
	Entity(const std::string& uniqueName);

	std::string _uniqueName;
	std::vector<std::unique_ptr<Component>> _components;
	ComponentArray _componentIdToPointer;
	ComponentBitset _componentSignatures;
	// When this is set to false, the entity will be destroyed in the next refresh.
	bool _isActive;
};