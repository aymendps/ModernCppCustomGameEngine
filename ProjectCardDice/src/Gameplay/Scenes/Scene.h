#pragma once
#include <iostream>

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Init() = 0;
	virtual void HandleEvents(union SDL_Event& event) = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};