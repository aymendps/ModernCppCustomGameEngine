#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class Game {
	friend struct GameDestroyer;
public:
	static constexpr const char* GAME_TITLE = "Project Card Dice";
	static constexpr int GAME_HEIGHT = 1080;
	static constexpr int GAME_WIDTH = 1920;
	static constexpr bool GAME_FULLSCREEN = true;

	Game();
	~Game() = default;

	/// <summary>
	/// Initializes the necessary resources for the game, creating the game window and renderer in the process
	/// </summary>
	/// <param name="title">Title of the game window</param>
	/// <param name="xpos">Can be SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED</param>
	/// <param name="ypos">Can be SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED</param>
	/// <param name="width">Width of the game window</param>
	/// <param name="height">Height of the game window</param>
	/// <param name="isFullscreen">Whether to start the game window in fullscreen</param>
	void Init();

	/// <summary>
	/// Handles the events of the game, such as user input and window events
	/// </summary>
	void HandleEvents();

	/// <summary>
	/// Runs every frame and updates the data of the game
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	void Update(const float deltaTime);

	/// <summary>
	/// Runs every frame and renders the game and should be called after updating the game's data
	/// </summary>
	void Render();

	/// <summary>
	/// Cleans up the resources used by the game, destroying the game window and renderer in the process
	/// </summary>
	void Destroy();

	/// <summary>
	/// Returns true if the game is running, otherwise false
	/// </summary>
	bool IsRunning() const { return _isRunning; }

	/// <summary>
	/// Returns a pointer to the game's renderer. Use this to render elements using SDL.
	/// </summary>
	static SDL_Renderer* const GetRenderer() { return _renderer; }

private:
	static SDL_Renderer* _renderer;
	SDL_Window* _window;
	bool _isRunning;

};

