#include "BattleScene.h"
#include "../Components/SpriteComponent.h"
#include "../../Core/EC/Entity.h"
#include "../../Game.h"
#include "../../Core/Math/Randomizer.h"
#include "../Components/CharacterComponent.h"
#include "../../Core/Managers/EntityManager.h"

void BattleScene::Init()
{
	// Create background image
	Entity& bg = CreateEntity("Background");
	bg.AddComponent<TransformComponent>(0.0f, 0.0f, static_cast<float>(Game::GAME_WIDTH), static_cast<float>(Game::GAME_HEIGHT));
	bg.AddComponent<SpriteComponent>("assets/ignore/battleback1.png");

	// Create player entity
	Entity& player = CreateEntity("Player");
	player.AddComponent<TransformComponent>(550.f, 500.f, 100.f, 100.f);
	player.AddComponent<SpriteComponent>("assets/ignore/placeholder.png");
	player.AddComponent<CharacterComponent>(CharacterConfiguration{ "Player Character", 50, 50, 0 });

	// Create two enemy entities
	Entity& enemy1 = CreateEntity("Enemy 1");
	enemy1.AddComponent<TransformComponent>(1150.f, 500.f, 100.f, 100.f);
	enemy1.AddComponent<SpriteComponent>("assets/ignore/placeholder.png");
	enemy1.AddComponent<CharacterComponent>(CharacterConfiguration{ "Enemy Character", 50, 50, 0 });

	Entity& enemy2 = CreateEntity("Enemy 2");
	enemy2.AddComponent<TransformComponent>(1350.f, 300.f, 300.f, 300.f);
	enemy2.AddComponent<SpriteComponent>("assets/ignore/placeholder.png");
	enemy2.AddComponent<CharacterComponent>(CharacterConfiguration{ "Enemy Character", 50, 50, 10 });
}

void BattleScene::HandleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_s:
			EntityManager::GetInstance().GetEntity("Enemy 2")->GetComponent<CharacterComponent>().TakeDamage(7);
			break;
		case SDLK_r:
			EntityManager::GetInstance().GetEntity("Enemy 2")->GetComponent<CharacterComponent>().HealDamage(7);
			break;
		case SDLK_e:
			EntityManager::GetInstance().GetEntity("Enemy 2")->GetComponent<CharacterComponent>().AddShield(10);
			break;
		case SDLK_z:
			EntityManager::GetInstance().GetEntity("Enemy 2")->GetComponent<CharacterComponent>().RemoveShield(10);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void BattleScene::Update(const float deltaTime)
{
}

void BattleScene::Render()
{
	Scene::Render();

	// Draw filled rect that represents area that player and allies can be placed
	SDL_Rect rect { 300, 450, 600, 200 };
	SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &rect);

	// Draw filled rect that represents area that enemies can be placed
	rect = { 1000, 450, 600, 200 };
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &rect);
}

void BattleScene::Destroy()
{
	Scene::Destroy();
	std::cout << "Destroying Scene: class TestScene" << std::endl;
}
