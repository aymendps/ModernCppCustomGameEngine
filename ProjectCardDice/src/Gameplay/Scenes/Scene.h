#pragma once
#include <iostream>
#include "../../Core/EC/Entity.h"

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Init() = 0;
	virtual void HandleEvents(union SDL_Event& event) = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Destroy();

protected:
	// Store pointers to entities created in this scene to destroy them when the scene is destroyed
	std::vector<Entity*> _createdEntities;
};