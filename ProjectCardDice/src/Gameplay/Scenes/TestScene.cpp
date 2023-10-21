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

	_testEntity->AddComponent<SpriteComponent>("assets/pic.jpg");
	_testEntity->AddComponent<SpriteComponent>("assets/pic.jpg");

	_cardEntity = &CreateRandomCardEntity("Test Card Entity");
	_cardEntity->GetComponent<TransformComponent>().position = Vector2D{ 100, 100 };
	_createdEntities.insert(_cardEntity);
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
