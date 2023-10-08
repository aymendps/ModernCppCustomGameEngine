#pragma once
#include "../Component.h"
class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	// Inherited via Component
	virtual void Init() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;
};

