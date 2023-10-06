#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>
#include "../CustomDestroyers/SDLWindowDestroyer.h"
#include "../CustomDestroyers/SDLRendererDestroyer.h"

class Game {
	friend struct GameDestroyer;
public:
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
	/// 
	/// </summary>
	void HandleEvents();

	/// <summary>
	/// 
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	void Render();

	/// <summary>
	/// 
	/// </summary>
	void Clean();

	/// <summary>
	/// Returns true if the game is running, otherwise false
	/// </summary>
	bool IsRunning() const { return _isRunning; }

private:
	std::unique_ptr<SDL_Window, SDLWindowDestroyer> _window;
	std::unique_ptr<SDL_Renderer, SDLRendererDestroyer> _renderer;
	bool _isRunning;
};

