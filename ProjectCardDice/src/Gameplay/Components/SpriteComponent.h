#pragma once
#include "../../Core/EC/Entity.h"
#include "TransformComponent.h"
#include "../../Core/Managers/TextureManager.h"
#include "../../Core/CustomDestroyers/SDL_TextureDestroyer.h"


class SpriteComponent : public Component
{
public:
	SpriteComponent(const char* filePath);
	~SpriteComponent();

	// Inherited via Component
	virtual void Init() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	/// <summary>
	/// Set the texture of the sprite to the one at the given file path
	/// </summary>
	/// <param name="filePath">The file path of the texture</param>
	SpriteComponent& SetTexture(const char* filePath);

private:
	TransformComponent* _transform;
	std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> _texture;
	SDL_Rect _destinationRect;
};

