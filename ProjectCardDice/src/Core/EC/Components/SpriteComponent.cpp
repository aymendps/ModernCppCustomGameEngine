#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* filePath)
	: _transform { nullptr }, _sourceRect {0, 0, 0, 0}, _destinationRect {0, 0, 0, 0}
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
	
}

void SpriteComponent::Render()
{
	TextureManager::RenderTexture(_texture.get(), &_sourceRect, &_destinationRect);
}

void SpriteComponent::SetTexture(const char* filePath)
{
	_texture.reset(TextureManager::LoadTexture(filePath));
}
