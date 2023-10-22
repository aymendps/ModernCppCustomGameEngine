#include "SpriteComponent.h"
#include "../../Core/Managers/TextureManager.h"
#include "../../Core/EC/Entity.h"


SpriteComponent::SpriteComponent(const char* filePath)
	: _transform{ nullptr }, _destinationRect{ 0, 0, 0, 0 }
{
	SetTexture(filePath);
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
	_destinationRect = _transform->GetDestinationRect();
}

void SpriteComponent::Render()
{
	TextureManager::RenderTexture(_texture.get(), &_destinationRect);
}

void SpriteComponent::SetTexture(const char* filePath)
{
	_texture.reset(TextureManager::LoadTexture(filePath));
}
