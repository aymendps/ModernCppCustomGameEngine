#include "BattleScene.h"
#include "../Components/SpriteComponent.h"
#include "../../Core/EC/Entity.h"
#include "../../Game.h"

void BattleScene::Init()
{
	// Create background image
	Entity& bg = CreateEntity("Background");
	bg.AddComponent<TransformComponent>(0.0f, 0.0f, static_cast<float>(Game::GAME_WIDTH), static_cast<float>(Game::GAME_HEIGHT));
	bg.AddComponent<SpriteComponent>("assets/ignore/battleback1.png");
}

void BattleScene::HandleEvents(SDL_Event& event)
{
}

void BattleScene::Update(const float deltaTime)
{
}

void BattleScene::Render()
{
}

void BattleScene::Destroy()
{
	Scene::Destroy();
	std::cout << "Destroying Scene: class TestScene" << std::endl;
}
