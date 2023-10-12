#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>
#include <iomanip>

class Game {
	friend struct GameDestroyer;
public:
	static SDL_Renderer* renderer;

	Game();
	~Game();

	/// <summary>
	/// Initializes the necessary resources for the game, creating the game window and renderer in the process
	/// </summary>
	/// <param name="title">Title of the game window</param>
	/// <param name="xpos">Can be SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED</param>
	/// <param name="ypos">Can be SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED</param>
	/// <param name="width">Width of the game window</param>
	/// <param name="height">Height of the game window</param>
	/// <param name="isFullscreen">Whether to start the game window in fullscreen</param>
	void Init(const char* title, int xpos, int ypos, int width, int height, bool isFullscreen);

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

private:
	SDL_Window* _window;
	bool _isRunning;
};

