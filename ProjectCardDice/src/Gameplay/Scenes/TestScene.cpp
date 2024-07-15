#include "TestScene.h"
#include "../../Core/Managers/SceneManager.h"
#include "../Components/SpriteComponent.h"
#include "../Collections/CardCollection.h"
#include "TestScene2.h"



TestScene::TestScene(Vector2D position, float speed) :_testEntity { nullptr }, _cardEntity { nullptr }, _testEntityPosition { position }, 
_testEntitySpeed { speed }
{
}

void TestScene::Init()
{
	Scene::Init();

	_testEntity = CreateEntity("Test Entity");
	_testEntity = CreateEntity("Test Entity");

	_testEntity->AddComponent<TransformComponent>()->position = _testEntityPosition;
	_testEntity->GetComponent<TransformComponent>()->size = _testEntityPosition;

	_testEntity->AddComponent<SpriteComponent>("assets/ignore/Paladin1.png");
	_testEntity->AddComponent<SpriteComponent>("assets/ignore/Paladin1.png");

	Vector2D cardPosition = { 200, 125 };

	for (int i = 0; i < 10; i++)
	{
		_cardEntity = CreateCardEntity(static_cast<CardEntityUniqueID>(i), "Test Card " + std::to_string(i), GetSceneName());
		_cardEntity->GetComponent<TransformComponent>()->position = cardPosition;
		cardPosition.x += 315;

		if (i == 4)
		{
			cardPosition.x = 200;
			cardPosition.y += 440;
		}
	}
}

void TestScene::HandleEvents(SDL_Event& event)
{
	Scene::HandleEvents(event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_s:
			SceneManager::GetInstance().SetActiveScene<TestScene2>(true);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void TestScene::Update(const float deltaTime)
{
	auto t = EntityManager::GetInstance().GetEntity("Test Entity");
	if (t != nullptr) {
		t->GetComponent<TransformComponent>()->position += Vector2D::Right * _testEntitySpeed * deltaTime;
	}

	Scene::Update(deltaTime);
}
