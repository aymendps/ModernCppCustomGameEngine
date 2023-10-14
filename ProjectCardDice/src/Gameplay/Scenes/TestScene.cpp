#include "TestScene.h"
#include "SceneManager.h"
#include "../../Core/Managers/EntityManager.h"
#include "../Components/SpriteComponent.h"
#include "../Collections/CardCollection.h"


TestScene::TestScene(Vector2D position, float speed) :_testEntity { nullptr }, _cardEntity { nullptr }, _testEntityPosition { position }, 
_testEntitySpeed { speed }
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	_testEntity = &EntityManager::GetInstance().CreateEntity("Test Entity");
	_createdEntities.push_back(_testEntity);
	// Second call to test what happens when we create an entity with the same name (should return reference to entity above)
	_testEntity->AddComponent<TransformComponent>().SetPosition(_testEntityPosition).SetSize(_testEntityPosition);
	_testEntity->AddComponent<SpriteComponent>("assets/pic.jpg");

	_cardEntity = &CardCollection::GetInstance().CreateRandomCardEntity("Random Card Entity");
	_createdEntities.push_back(_cardEntity);
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
	auto position = _testEntity->GetComponent<TransformComponent>().GetPosition();
	// using lerp, we move the entity from its current position to target position
	_testEntity->GetComponent<TransformComponent>().SetPosition(position + Vector2D::Right * _testEntitySpeed * deltaTime);
}

void TestScene::Render()
{
}

void TestScene::Destroy()
{
	Scene::Destroy();
	std::cout << "Destroying Scene: class TestScene" << std::endl;
}
