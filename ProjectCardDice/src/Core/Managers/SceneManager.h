#pragma once
#include <memory>
#include <thread>
#include <concepts>
#include <SDL.h>
#include <functional>
#include "../../Core/EC/Scene.h"
#include "../../Core/Managers/EntityManager.h"

enum class SceneFadeDirection {
	In, // Used when entering a new scene if fading is desired
	Out, // Used when exiting an old scene if fading is desired
	None // Used when there is no fading desired during scene transition
};

class SceneManager
{
public:
	//Delete copy/move of singleton instance
	SceneManager(SceneManager& other) = delete;
	void operator=(const SceneManager&) = delete;

	// Singleton instance
	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}

	/// <summary>
	/// Initializes the scene manager, with the initially active scene being of the given T class.
	/// </summary>
	/// <typeparam name="T">The class of the initial scene</typeparam>
	/// <typeparam name="...TArgs">Constructor args of the initial scene</typeparam>
	/// <param name="...args">Constructor args of the initial scene</param>
	template <typename T, typename... TArgs> requires SceneType<T>
	void Init(TArgs&&... args) {
		Logger::LogLine(LogType::SceneRelated, "Creating the initial Scene...");
		_activeScene = std::make_unique<T>(std::forward<TArgs>(args)...);
		Logger::LogLine(LogType::SceneRelated, "Initial Scene of ", typeid(T).name(), " was created successfully!");

		_activeScene->Init();
	}

	/// <summary>
	/// Handles events such as SDL events and inputs for the active scene.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	void HandleEvents(union SDL_Event& event) const;

	/// <summary>
	/// Updates the active scene.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds between the current and previous frame</param>
	void Update(const float deltaTime);

	/// <summary>
	/// Renders the active scene.
	/// </summary>
	void Render() const;

	/// <summary>
	/// Destroys the active scene & its entities and refreshes the entity manager.
	/// </summary>
	void Destroy();

	/// <summary>
	/// Changes the active scene to the given scene class.
	/// A new scene will be constructed of that class and the old scene will be destroyed.
	/// </summary>
	/// <typeparam name="T">The class of new active scene</typeparam>
	/// <typeparam name="...Args">Constructor args of the new active scene</typeparam>
	/// <param name="shouldFadeScreen">Whether the screen should use fade out then in when switching scenes</param>
	/// <param name="...args">Constructor args of the new active scene</param>
	template <typename T, typename... Args> requires SceneType<T>
	void SetActiveScene(bool shouldFadeScreen, Args&&... args) {
		// Start fading out the screen if needed
		_fadeDirection = shouldFadeScreen ? SceneFadeDirection::Out : SceneFadeDirection::None;

		// Switch scenes in a new thread to let the game loop continue so that the fade animation can run
		std::thread t (&SceneManager::SwitchScenes<T, Args...>, &SceneManager::GetInstance(), shouldFadeScreen, args...);
		t.detach();
	}

	/// <summary>
	/// Returns whether the scene manager is currently transitioning between scenes
	/// </summary>
	bool IsTransitioning() const { return _isTransitioning; }

private:
	std::unique_ptr<Scene> _activeScene;
	bool _isTransitioning = false;
	bool _shouldInitNewScene = false;
	SceneFadeDirection _fadeDirection = SceneFadeDirection::None;
	SDL_Color _fadeScreenColor = { 100, 100, 100, 255 };
	float _fadeDuration = 1.0f;
	float _fadeScreenAlpha = 0.0f;
	std::function<void()> _initNewScene;

	// private constructor because of singleton
	SceneManager() = default;

	// Updates the alpha value of the fade screen
	void UpdateFadeScreen(const float deltaTime);

	// Renders the fade screen
	void RenderFadeScreen() const;

	// Will be called in a new thread to switch scenes internally
	template <typename T, typename... Args> requires SceneType<T>
	void SwitchScenes(bool shouldFadeScreen, Args&&... args) {
		// Wait until the fade out animation is done
		// If there is no fade out animation, this will be skipped
		while (_fadeDirection != SceneFadeDirection::None);

		// Set the flag below to true so that the game loop will not update nor render the old scene
		_isTransitioning = true;

		// Assign the function needed to initialize the new scene and destroy the old one
		// This way, the function can be called in the main thread
		// This is needed because SDL Render functions can only work properly in the main thread
		 _initNewScene = [&]() {
			 Logger::LogLine(LogType::SceneRelated, "Switching Scenes from ", typeid(*_activeScene).name(), " to ", typeid(T).name());
			// Destroy the old scene
			_activeScene->Destroy();
			// Make sure all entities related to old scene are destroyed
			EntityManager::GetInstance().Refresh();
			// Create the new scene
			_activeScene.reset(new T(std::forward<Args>(args)...));
			// Initialize the new scene
			Logger::LogLine(LogType::SceneRelated, "Initializing Scene: ", typeid(T).name());
			_activeScene->Init();
		};

		 // Tell the main thread to call the function above by setting the flag below to true
		 _shouldInitNewScene = true;

		 // Wait until the main thread has performed the function above
		 while (_shouldInitNewScene);

		 // If we used fade out animation, we need to fade in the screen now
		 // Otherwise, we can just skip this step
		_fadeDirection = shouldFadeScreen ? SceneFadeDirection::In : SceneFadeDirection::None;

		// Set the flag below to false so that the game loop will update and render the newly created scene
		_isTransitioning = false;
	}
};

