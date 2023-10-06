#include "Game.h"

Game::Game() : _isRunning {false}, _window {nullptr}, _renderer {nullptr}
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool isFullscreen)
{
	std::cout << "Initializing SDL..." << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL was initialized!" << std::endl;

		std::cout << "Creating Game Window..." << std::endl;

		_window = SDL_CreateWindow(title, xpos, ypos, width, height,
			isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

		if (_window) {
			std::cout << "Game Window was created!" << std::endl;
		}

		std::cout << "Creating Game Renderer..." << std::endl;

		_renderer = SDL_CreateRenderer(_window, -1, 0);

		if (_renderer) {
			SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
			std::cout << "Game Renderer was created!" << std::endl;
		}

		_isRunning = true;
	}
	else {
		_isRunning = false;
	}
}


void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
	case SDL_KEYDOWN:
		_isRunning = false;
		break;

	default:
		break;
	}
}

void Game::Update(float deltaTime)
{
	std::cout << "Updating... (deltaTime = " << deltaTime << ")" << std::endl;
}

void Game::Render()
{
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

void Game::Destroy()
{
	std::cout << "Destroying Game Window..." << std::endl;
	SDL_DestroyWindow(_window);
	std::cout << "Game Window was destroyed!" << std::endl;

	std::cout << "Destroying Game Renderer..." << std::endl;
	SDL_DestroyRenderer(_renderer);
	std::cout << "Game Renderer was destroyed!" << std::endl;

	std::cout << "Destroying SDL..." << std::endl;
	SDL_Quit();
	std::cout << "SDL was destroyed!" << std::endl;
}
