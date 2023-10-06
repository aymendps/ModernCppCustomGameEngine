#include "Game.h"

Game::Game() : _isRunning {false}
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

		_window = std::unique_ptr<SDL_Window, SDLWindowDestroyer>(SDL_CreateWindow(title, xpos, ypos, width, height,
			isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));

		if (_window) {
			std::cout << "Game Window was created!" << std::endl;
		}

		std::cout << "Creating Game Renderer..." << std::endl;

		_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDestroyer>(SDL_CreateRenderer(_window.get(), -1, 0));

		if (_renderer) {
			SDL_SetRenderDrawColor(_renderer.get(), 0, 255, 0, 255);
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

void Game::Update()
{
	std::cout << "Updating..." << std::endl;
}

void Game::Render()
{
	SDL_RenderClear(_renderer.get());
	SDL_RenderPresent(_renderer.get());
}

void Game::Clean()
{
	std::cout << "Cleaning game..." << std::endl;
	SDL_Quit();
	std::cout << "Game was cleaned!" << std::endl;
}
