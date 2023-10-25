#include "TransformComponent.h"

TransformComponent::TransformComponent() : position {0, 0}, size {0, 0}, scale {1}
{
}

TransformComponent::TransformComponent(float x, float y, float w, float h, float scale)
	: position {x, y}, size {w, h}, scale {scale}
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

void TransformComponent::Update(const float deltaTime)
{
}

void TransformComponent::Render()
{
}
