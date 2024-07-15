#include "Game.h"
#include "Core/Managers/SceneManager.h"
#include "Gameplay/Collections/CardCollection.h"
#include "Gameplay/Scenes/TestScene.h"

SDL_Renderer* Game::_renderer = nullptr;

Game::Game() : _isRunning {false}, _window {nullptr}
{
}

void Game::Init()
{
	std::cout << "Initializing SDL..." << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {
		std::cout << "SDL was initialized!" << std::endl;

		std::cout << "Creating Game Window..." << std::endl;

		_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			GAME_WIDTH, GAME_HEIGHT, GAME_FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

		if (_window) {
			std::cout << "Game Window was created!" << std::endl;
		}

		std::cout << "Creating Game Renderer..." << std::endl;

		_renderer = SDL_CreateRenderer(_window, -1, 0);

		if (_renderer) {
			std::cout << "Game Renderer was created!" << std::endl;
			SDL_RenderSetLogicalSize(_renderer, GAME_WIDTH, GAME_HEIGHT);
			SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		}

		std::cout << "\033[33m" << "Allowing a maximum of " << maxComponentTypes << " component types per entity" << "\033[0m" << std::endl;
		std::cout << "\033[33m" << "Allowing only 1 instance of each component type per entity" << "\033[0m" << std::endl;

		CardCollection::GetInstance().Init();
		SceneManager::GetInstance().Init<TestScene>(Vector2D{ 100.0f, 100.0f }, 40.0f);

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
	case SDL_KEYDOWN:
		_isRunning = event.key.keysym.sym != SDLK_ESCAPE;
		break;
	default:
		break;
	}
	SceneManager::GetInstance().HandleEvents(event);
}

void Game::Update(const float deltaTime)
{
	SceneManager::GetInstance().Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(Game::_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
	SceneManager::GetInstance().Render();
	SDL_RenderPresent(_renderer);
}

void Game::Destroy()
{
	SceneManager::GetInstance().Destroy();

	std::cout << "Destroying Game Window..." << std::endl;
	SDL_DestroyWindow(_window);
	std::cout << "Game Window was destroyed!" << std::endl;

	std::cout << "Destroying Game Renderer..." << std::endl;
	SDL_DestroyRenderer(_renderer);
	std::cout << "Game Renderer was destroyed!" << std::endl;

	std::cout << "Destroying SDL_TTF..." << std::endl;
	TTF_Quit();
	std::cout << "SDL_TTF was destroyed!" << std::endl;

	std::cout << "Destroying SDL..." << std::endl;
	SDL_Quit();
	std::cout << "SDL was destroyed!" << std::endl;
}
