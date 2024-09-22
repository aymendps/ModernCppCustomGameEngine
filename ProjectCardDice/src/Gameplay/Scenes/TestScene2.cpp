#include "TestScene2.h"
#include "../Components/SpriteComponent.h"
#include "../../Core/EC/Entity.h"
#include "../../Game.h"
#include "../Components/CharacterComponent.h"
#include "../../Core/Managers/EntityManager.h"
#include "../Components/CardComponent.h"

void TestScene2::Init()
{
	Scene::Init();

	// Create background image
	Entity* bg = CreateEntity("Background");
	bg->AddComponent<TransformComponent>(0.0f, 0.0f, static_cast<float>(Game::GAME_WIDTH), static_cast<float>(Game::GAME_HEIGHT));
	bg->AddComponent<SpriteComponent>("assets/ignore/battleback1.png");

	// Create player entity
	Entity* player = CreateEntity("Player");
	player->AddComponent<TransformComponent>(550.f, 500.f, 100.f, 100.f);
	player->AddComponent<SpriteComponent>("assets/ignore/placeholder.png");
	player->AddComponent<CharacterComponent>(CharacterConfiguration{ "Player Character", 50, 50, 0 });

	// Create two enemy entities
	Entity* enemy1 = CreateEntity("Enemy 1");
	enemy1->AddComponent<TransformComponent>(1150.f, 500.f, 100.f, 100.f);
	enemy1->AddComponent<SpriteComponent>("assets/ignore/placeholder.png");
	enemy1->AddComponent<CharacterComponent>(CharacterConfiguration{ "Enemy Character", 50, 50, 0 });

	Entity* enemy2 = CreateEntity("Enemy 2");
	enemy2->AddComponent<TransformComponent>(1350.f, 300.f, 300.f, 300.f);
	enemy2->AddComponent<SpriteComponent>("assets/ignore/placeholder.png");
	enemy2->AddComponent<CharacterComponent>(CharacterConfiguration{ "Enemy Character", 50, 50, 10 });
}

void TestScene2::HandleEvents(SDL_Event& event)
{
	Scene::HandleEvents(event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_b:
		{
			auto y = GetEntity("Background")->GetComponent<SpriteComponent>();
			if (y) y->SetEnabled(!y->IsEnabled());
			break;
		}
		case SDLK_n:
		{
			auto y = GetEntity("Background");
			if (y->GetComponent<SpriteComponent>()) 
			{
				y->RemoveComponent<SpriteComponent>();
			}
			else 
			{
				y->AddComponent<SpriteComponent>("assets/ignore/battleback1.png");
			}
			break;
		}
		case SDLK_x: 
		{
			DestroyEntitiesWithComponent<CharacterComponent>();
			break;
		}
		case SDLK_s:
		{
			if (auto y = GetEntity("Enemy 2")) {
				y->GetComponent<CharacterComponent>()->TakeDamage(7);
			}
			break;
		}
		case SDLK_r:
		{
			if (auto y = GetEntity("Enemy 2")) {
				y->GetComponent<CharacterComponent>()->HealDamage(7);
			}
			break;
		}
		case SDLK_e:
		{
			if (auto y = GetEntity("Enemy 2")) {
				y->GetComponent<CharacterComponent>()->AddShield(10);
			}
			break;
		}
		case SDLK_z:
		{
			if (auto y = GetEntity("Enemy 2")) {
				y->GetComponent<CharacterComponent>()->RemoveShield(10);
			}
			break;
		}
		}
		break;
	}
}

void TestScene2::Update(const float deltaTime)
{
	std::vector<Entity*> characterEntities = EntityManager::GetInstance().GetEntitiesWithComponent<CharacterComponent>();
	for (auto& i : characterEntities)
	{
		if (i->GetComponent<CharacterComponent>()->IsDead()) {
			i->Destroy();
		}
		else {
			i->GetComponent<TransformComponent>()->scale += 0.01f * deltaTime;
		}
	}
	Scene::Update(deltaTime);
}

void TestScene2::Render()
{
	Scene::Render();

	// Draw filled rect that represents area that player and allies can be placed
	SDL_Rect rect { 100, 250, 800, 500};
	SDL_SetRenderDrawColor(Game::GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(Game::GetRenderer(), &rect);

	// Draw filled rect that represents area that enemies can be placed
	rect = { 1000, 250, 800, 500 };
	SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Game::GetRenderer(), &rect);
}
