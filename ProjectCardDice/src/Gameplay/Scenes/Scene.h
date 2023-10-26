#pragma once
#include <unordered_set>
#include <string>

class Entity;
enum class CardEntityUniqueID;

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Init() = 0;
	virtual void HandleEvents(union SDL_Event& event) = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render();
	virtual void Destroy();

protected:
	// Store pointers to entities created in this scene to destroy them when the scene is destroyed
	std::unordered_set<Entity*> _createdEntities;

	Entity& CreateEntity(const std::string name);
	Entity& CreateCardEntity(CardEntityUniqueID uniqueID,  const std::string name);
	Entity& CreateRandomCardEntity(const std::string name);
};