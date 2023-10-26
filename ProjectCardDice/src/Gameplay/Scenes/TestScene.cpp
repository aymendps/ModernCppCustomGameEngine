#include "TestScene.h"
#include "SceneManager.h"
#include "../Components/SpriteComponent.h"
#include "BattleScene.h"


TestScene::TestScene(Vector2D position, float speed) :_testEntity { nullptr }, _cardEntity { nullptr }, _testEntityPosition { position }, 
_testEntitySpeed { speed }
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	_testEntity = &CreateEntity("Test Entity");
	_testEntity = &CreateEntity("Test Entity");

	_testEntity->AddComponent<TransformComponent>().position = _testEntityPosition;
	_testEntity->GetComponent<TransformComponent>().size = _testEntityPosition;

	_testEntity->AddComponent<SpriteComponent>("assets/placeholder.png");
	_testEntity->AddComponent<SpriteComponent>("assets/placeholder.png");

	Vector2D cardPosition = { 200, 125 };

	for (int i = 0; i < 10; i++)
	{
		_cardEntity = &CreateCardEntity(static_cast<CardEntityUniqueID>(i), "Test Card " + std::to_string(i));
		_cardEntity->GetComponent<TransformComponent>().position = cardPosition;
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
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_s:
			SceneManager::GetInstance().SetActiveScene<BattleScene>(true);
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
	_testEntity->GetComponent<TransformComponent>().position += Vector2D::Right * _testEntitySpeed * deltaTime;
}

void TestScene::Destroy()
{
	Scene::Destroy();
	std::cout << "Destroying Scene: class TestScene" << std::endl;
}
