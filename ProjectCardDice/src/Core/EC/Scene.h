#pragma once
#include <unordered_set>
#include <string>
#include "../../Core/Managers/EntityManager.h"

class Entity;
enum class CardEntityUniqueID;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	/// <summary>
	/// Initializes the scene. Is called once when the scene is started.
	/// </summary>
	virtual void Init();

	/// <summary>
	/// Handles the events of the scene like SDL events and inputs. Is called every frame.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	virtual void HandleEvents(union SDL_Event& event);

	/// <summary>
	/// Updates the scene. Is called every frame.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	virtual void Update(const float deltaTime);

	/// <summary>
	/// Renders the scene. Is called every frame.
	/// </summary>
	virtual void Render();

	/// <summary>
	/// Destroys the scene. Is called once when the scene is no longer needed.
	/// </summary>
	virtual void Destroy();

	/// <summary>
	/// Returns the name of the scene, which is automatically generated from the class name
	/// </summary>
	virtual std::string GetSceneName() const { return typeid(*this).name(); };
};

template <typename T>
concept SceneType = std::is_base_of<Scene, T>::value;