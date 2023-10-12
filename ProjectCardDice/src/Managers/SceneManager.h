#pragma once
#include <memory>
#include <SDL.h>
#include "../CustomDestroyers/SceneDestroyer.h"


class SceneManager
{
public:
	// Delete copy/move of singleton instance
	SceneManager(SceneManager& other) = delete;
	void operator=(const SceneManager&) = delete;

	// Singleton instance
	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}

	void Init();
	void HandleEvents(union SDL_Event& event) const;
	void Update(const float deltaTime) const;
	void Render() const;

	/// <summary>
	/// Switches the active scene to the given scene. The old scene will be destroyed.
	/// </summary>
	/// <typeparam name="T">The class of new active scene</typeparam>
	/// <typeparam name="...Args">Constructor args of the new active scene</typeparam>
	/// <param name="...args">Constructor args of the new active scene</param>
	template <typename T, typename... Args>
	void SetActiveScene(Args&&... args) {
		static_assert(std::is_base_of<Scene, T>::value, "T must be a subclass of Scene");

		_isTransitioning = true;

		// Destroy the old scene and create a new one
		_activeScene.reset(new T(std::forward<Args>(args)...));
		// Initialize the new scene
		std::cout << "Initializing Scene: " << typeid(T).name() << std::endl;
		_activeScene->Init();

		_isTransitioning = false;
	}

	bool IsTransitioning() const { return _isTransitioning; }

private:
	std::unique_ptr<Scene, SceneDestroyer> _activeScene;
	bool _isTransitioning = false;

	// private constructor because of singleton
	SceneManager();
};

