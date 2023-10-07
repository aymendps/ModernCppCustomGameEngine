#include "Entity.h"

Entity::Entity() : _isActive {true}
{
}

Entity::~Entity()
{
}

void Entity::Update(const float deltaTime)
{
	for (auto& component : _components) {
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (auto& component : _components) {
		component->Render();
	}
}

template<typename T, typename ...TArgs>
T& Entity::AddComponent(TArgs && ...args)
{
	// Create a new component and set it's owner to this entity
	std::unique_ptr<Component> componentPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
	componentPtr->_owner = this;

	// Set signature to true to indicate that this entity has this component
	ComponentTypeID ID = GetComponentTypeID<T>();
	_componentPointers[ID] = componentPtr.get();
	_componentSignatures[ID] = true;

	componentPtr->Init();

	// Add the component to the vector of components and return a reference to it
	_components.push_back(std::move(componentPtr));
	return *_components.back();
}

template<typename T>
T& Entity::GetComponent() const
{
	// Get the component and cast it to the correct type
	auto ptr { _componentPointers[GetComponentTypeID<T>()] };
	return *static_cast<T*>(ptr);
}
