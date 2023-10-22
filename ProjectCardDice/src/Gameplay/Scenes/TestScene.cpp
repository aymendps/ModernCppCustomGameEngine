#include "TestScene.h"
#include "SceneManager.h"
#include "../Components/SpriteComponent.h"


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

	Vector2D cardPosition = { 150, 100 };

	for (int i = 0; i < 10; i++)
	{
		_cardEntity = &CreateCardEntity(static_cast<CardEntityUniqueID>(i), "Test Card " + i);
		_cardEntity->GetComponent<TransformComponent>().position = cardPosition;
		cardPosition.x += 250;

		if (i == 4)
		{
			cardPosition.x = 150;
			cardPosition.y += 350;
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
			SceneManager::GetInstance().SetActiveScene<TestScene>(true, Vector2D{ 100, 100 }, _testEntitySpeed * 2.0f);
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

void TestScene::Render()
{
}

void TestScene::Destroy()
{
	Scene::Destroy();
	std::cout << "Destroying Scene: class TestScene" << std::endl;
}
