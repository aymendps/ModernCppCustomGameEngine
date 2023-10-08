#pragma once
#include "../Component.h"
#include "../../Math/Vector2D.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(const float x, const float y, const float w, const float h, const float scale = 1);
	~TransformComponent();

	// Inherited via Component
	virtual void Init() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	void SetPosition(const float x, const float y);
	void SetPosition(const Vector2D& vec);
	void SetSize(const float w, const float h);
	void SetSize(const Vector2D& vec);
	void SetScale(const float scale);

	const Vector2D& GetPosition() const;
	const Vector2D& GetSize() const;
	const float GetScale() const;

private:
	Vector2D _position;
	// x represents width, y represents height
	Vector2D _size;
	float _scale;
};

