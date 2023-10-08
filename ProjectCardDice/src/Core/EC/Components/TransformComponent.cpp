#include "TransformComponent.h"

TransformComponent::TransformComponent() : _position {0, 0}, _size {0, 0}, _scale {1}
{
}

TransformComponent::TransformComponent(const float x, const float y, const float w, const float h, const float scale)
	: _position {x, y}, _size {w, h}, _scale {scale}
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetPosition(const float x, const float y)
{
	_position.x = x;
	_position.y = y;
}

void TransformComponent::SetPosition(const Vector2D& vec)
{
	_position = vec;
}

void TransformComponent::SetSize(const float w, const float h)
{
	_size.x = w;
	_size.y = h;
}

void TransformComponent::SetSize(const Vector2D& vec)
{
	_size = vec;
}

void TransformComponent::SetScale(const float scale)
{
	this->_scale = scale;
}

const Vector2D& TransformComponent::GetPosition() const
{
	return _position;
}

const Vector2D& TransformComponent::GetSize() const
{
	return _size;
}

const float TransformComponent::GetScale() const
{
	return _scale;
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
