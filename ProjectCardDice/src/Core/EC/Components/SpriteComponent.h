#pragma once
#include "../Entity.h"
#include "TransformComponent.h"
#include "../../TextureManager.h"
#include "../../../CustomDestroyers/SDL_TextureDestroyer.h"

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
	void SetTexture(const char* filePath);

private:
	TransformComponent* _transform;
	std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> _texture;
	SDL_Rect _sourceRect, _destinationRect;
};

