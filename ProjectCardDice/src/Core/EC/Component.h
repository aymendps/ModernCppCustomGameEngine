#pragma once
#include <bitset>
#include <iostream>
#include <array>

class Component;

using ComponentTypeID = size_t;
 
// Returns the next ID each time it is called (starting at 0)
inline ComponentTypeID GetComponentTypeID() {
	static ComponentTypeID lastID = 0;
	return lastID++;
}

// Returns the unique ID for each type of component
template <typename T> 
inline ComponentTypeID GetComponentTypeID() noexcept {
	static_assert (std::is_base_of<Component, T>::value, "T must be a subclass of Component");
	static ComponentTypeID uniqueTypeID = GetComponentTypeID();
	static bool ShouldLog = true;

	if (ShouldLog) {
		std::cout << "Registered component " << typeid(T).name() << " with unique ID of " << uniqueTypeID << std::endl;
		ShouldLog = false;
	}

	return uniqueTypeID;
}

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
	Component();
	virtual ~Component();

	/// <summary>
	/// Initializes the necessary data for the component.
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// Runs every frame and updates the component's data.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	virtual void Update(const float deltaTime) = 0;

	/// <summary>
	/// Runs every frame and renders the component and should be called after updating the component's data.
	/// </summary>
	virtual void Render() = 0;

protected:
	Entity* _owner;
};

