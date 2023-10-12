#include "SceneManager.h"
#include "../Scenes/TestScene.h"

SceneManager::SceneManager()
{
	_activeScene.reset(new TestScene({100, 100}, 10.0f));
}

void SceneManager::Init()
{
	_activeScene->Init();
}

void SceneManager::HandleEvents(SDL_Event& event) const
{
	if (!_isTransitioning)
	{
		_activeScene->HandleEvents(event);
	}
}

void SceneManager::Update(const float deltaTime) const
{
	if (!_isTransitioning)
	{
		_activeScene->Update(deltaTime);
	}
}

void SceneManager::Render() const
{
	if (!_isTransitioning)
	{
		_activeScene->Render();
	}
}
