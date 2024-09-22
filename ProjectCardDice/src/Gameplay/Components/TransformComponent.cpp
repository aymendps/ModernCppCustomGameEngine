#include "TransformComponent.h"

TransformComponent::TransformComponent(Entity* owner, ComponentTypeID typeID) : Component(owner, typeID), position {0, 0}, size {0, 0}, scale {1}
{
}

TransformComponent::TransformComponent(Entity* owner, ComponentTypeID typeID, float x, float y, float w, float h, float scale) : Component(owner, typeID), position {x, y}, size {w, h}, scale {scale}
{
}

TransformComponent::~TransformComponent()
{
}

SDL_Rect TransformComponent::GetDestinationRect() const
{
	return { static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x * scale), static_cast<int>(size.y * scale) };
}

void TransformComponent::Init()
{
}

void TransformComponent::HandleEvents(SDL_Event& event)
{
}

void TransformComponent::Update(const float deltaTime)
{
}

void TransformComponent::Render()
{
}
