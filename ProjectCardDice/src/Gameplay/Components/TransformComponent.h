#pragma once
#include "../../Core/EC/Component.h"
#include "../../Core/Math/Vector2D.h"
#include <SDL_rect.h>

class TransformComponent : public Component
{
public:
	Vector2D position;
	// x represents width, y represents height
	Vector2D size;
	float scale;

	TransformComponent(Entity* owner, ComponentTypeID typeID);
	TransformComponent(Entity* owner, ComponentTypeID typeID, float x, float y, float w, float h, float scale = 1.0f);
	~TransformComponent();

	// Inherited via Component
	virtual void Init() override;
	virtual void HandleEvents(SDL_Event& event) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	/// <summary>
	/// Returns a rect that can be used to render something depending on this component's position, size and scale
	/// </summary>
	SDL_Rect GetDestinationRect() const;
};

