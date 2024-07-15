#pragma once
#include "../../Core/EC/Scene.h"

class TestScene2 : public Scene
{
	// Inherited via Scene
	void Init() override;
	void HandleEvents(SDL_Event& event) override;
	void Update(const float deltaTime) override;
	void Render() override;
};

