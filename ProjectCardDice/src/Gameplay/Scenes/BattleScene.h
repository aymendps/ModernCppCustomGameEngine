#pragma once
#include "Scene.h"

class BattleScene : public Scene
{
	// Inherited via Scene
	void Init() override;
	void HandleEvents(SDL_Event& event) override;
	void Update(const float deltaTime) override;
	void Render() override;
	void Destroy() override;
};

