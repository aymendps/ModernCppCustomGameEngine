#pragma once
#include "Scene.h"
#include "../Managers/EntityManager.h"
#include "../EC/Components/SpriteComponent.h"

class TestScene : public Scene
{
public:
	TestScene(Vector2D position, float speed);
	~TestScene();

	// Inherited via Scene
	void Init() override;
	void HandleEvents(SDL_Event& event) override;
	void Update(const float deltaTime) override;
	void Render() override;
	void Destroy() override;

private:
	Entity* _testEntity;
	Vector2D _testEntityPosition;
	float _testEntitySpeed = 0;
};

