#include "Scene.h"

void Scene::Init()
{
	std::cout << "Initiating Scene: " << GetSceneName() << std::endl;
}

void Scene::HandleEvents(SDL_Event& event)
{
	EntityManager::GetInstance().HandleEvents(event);
}

void Scene::Update(const float deltaTime)
{
	EntityManager::GetInstance().Update(deltaTime);
}

void Scene::Render()
{
	EntityManager::GetInstance().Render();
}

void Scene::Destroy()
{
	EntityManager::GetInstance().DestroyAllEntities();
	std::cout << "Destroying Scene: " << GetSceneName() << std::endl;
}
