#pragma once
#include <bitset>
#include <iostream>
#include <array>
#include <concepts>

class Component;

template <typename T>
concept ComponentType = std::is_base_of<Component, T>::value;

// Represents the unique ID of a component type.
using ComponentTypeID = size_t;
 
// Returns the next ID each time it is called (starting at 0).
inline ComponentTypeID GetComponentTypeID() {
	static ComponentTypeID lastID = 0;
	return lastID++;
}

// Returns the unique ID of the component type represented by T. This works because each version of the templated function has its own instance of the static variables.
template <typename T> requires ComponentType<T>
inline ComponentTypeID GetComponentTypeID() noexcept {
	static ComponentTypeID uniqueTypeID = GetComponentTypeID();
	static bool ShouldLog = true;

	if (ShouldLog) {
		std::cout << "\033[36m" << "Registered component " << typeid(T).name() << " with unique ID of " << uniqueTypeID << "\033[0m" << std::endl;
		ShouldLog = false;
	}

	return uniqueTypeID;
}

// The maximum number of component types that can be added to a single entity.
constexpr size_t maxComponentTypes = 32;

// When a component is added to an entity, the bit at its index (ID) in the bitset is set to 1, otherwise it is 0.
// This allows us to quickly check if an entity has a component or not.
using ComponentBitset = std::bitset<maxComponentTypes>;

// Using the index (ID) of the component type, we can access the component from the array.
using ComponentArray = std::array<Component*, maxComponentTypes>;

class Entity;

class Component
{
	friend class Entity;

public:
	Component(Entity* owner, ComponentTypeID typeID);
	virtual ~Component() = default;

	/// <summary>
	/// Initializes the necessary data for the component.
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// Handles events like SDL events and inputs.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	virtual void HandleEvents(union SDL_Event& event) = 0;

	/// <summary>
	/// Runs every frame and updates the component's data.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	virtual void Update(const float deltaTime) = 0;

	/// <summary>
	/// Runs every frame and renders the component and should be called after updating the component's data.
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// Returns the entity that owns this component.
	/// </summary>
	/// <returns>A pointer to the entity that owns this component</returns>
	Entity* GetOwner() const { return _owner; }

	/// <summary>
	/// Returns the unique ID that this component type is associated with.
	/// </summary>
	ComponentTypeID GetTypeID() const { return _typeID; }

	/// <summary>
	/// Returns whether or not the component is enabled. When disabled, the component is not updated or rendered and does not handle events.
	/// </summary>
	/// <returns>True if the component is enabled, false otherwise</returns>
	bool IsEnabled() const { return _enabled; }

	/// <summary>
	/// Sets whether or not the component is enabled. When disabled, the component is not updated or rendered and does not handle events.
	/// </summary>
	/// <param name="enabled">True to enable the component, false to disable it</param>
	void SetEnabled(bool enabled) { _enabled = enabled; }

protected:
	// The entity that owns this component, and possibly other components.
	Entity* const _owner;
	// The unique ID that this component type is associated with.
	const ComponentTypeID _typeID;
	// Whether the component is enabled or not. When disabled, the component is not updated or rendered and does not handle events.
	bool _enabled;
};

