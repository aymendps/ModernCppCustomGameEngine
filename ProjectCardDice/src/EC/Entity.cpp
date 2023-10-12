#include "Entity.h"

Entity::Entity() : _isActive {true}, _componentPointers {}
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