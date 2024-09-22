#include "Scene.h"
#include "../Utils/Logger.h"

void Scene::Init()
{
	Logger::LogLine(LogType::SceneRelated, "Loading Scene: ", GetSceneName());
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
	Logger::LogLine(LogType::SceneRelated, "Destroying Scene: ", GetSceneName());
}
