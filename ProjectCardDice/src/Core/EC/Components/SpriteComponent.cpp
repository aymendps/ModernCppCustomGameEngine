#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* filePath)
	: _transform{ nullptr }, _destinationRect{ 0, 0, 0, 0 }
{
	_texture.reset(TextureManager::LoadTexture(filePath));
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Init()
{
	_transform = &_owner->GetComponent<TransformComponent>();
}

void SpriteComponent::Update(const float deltaTime)
{
	auto& size = _transform->GetSize();
	auto& position = _transform->GetPosition();
	auto scale = _transform->GetScale();

	_destinationRect.x = static_cast<int>(position.x);
	_destinationRect.y = static_cast<int>(position.y);
	_destinationRect.w = static_cast<int>(size.x * scale);
	_destinationRect.h = static_cast<int>(size.y * scale);
}

void SpriteComponent::Render()
{
	TextureManager::RenderTexture(_texture.get(), &_destinationRect);
}

void SpriteComponent::SetTexture(const char* filePath)
{
	_texture.reset(TextureManager::LoadTexture(filePath));
}
