#include "Entity.h"
#include "../Utils/Logger.h"

Entity::Entity(const std::string& uniqueName) : _uniqueName{ uniqueName }, _isActive{ true }, _componentIdToPointer{}
{
}

void Entity::HandleEvents(SDL_Event& event)
{
	for (auto& component : _components) {
		if (component->IsEnabled()) {
			component->HandleEvents(event);
		}
	}
}

void Entity::Update(const float deltaTime)
{
	for (auto& component : _components) {
		if(component->IsEnabled()) {
			component->Update(deltaTime);
		}
	}
}

void Entity::Render()
{
	for (auto& component : _components) {
		if (component->IsEnabled()) {
			component->Render();
		}
	}
}

void Entity::Destroy()
{
	_isActive = false;
	Logger::LogLine(LogType::EntityRelated, "Destroying Entity: ", "'", _uniqueName, "'");
}