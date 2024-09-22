#include "Game.h"
#include "Core/Managers/SceneManager.h"
#include "Gameplay/Collections/CardCollection.h"
#include "Gameplay/Scenes/TestScene.h"
#include "Core/Utils/Logger.h"

SDL_Renderer* Game::_renderer = nullptr;

Game::Game() : _isRunning {false}, _window {nullptr}
{
}

void Game::Init()
{
	Logger::LogLine(LogType::EngineRelated, "Initializing SDL...");

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {
		Logger::LogLine(LogType::EngineRelated, "SDL was initialized!");

		Logger::LogLine(LogType::EngineRelated, "Creating Game Window...");

		_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			GAME_WIDTH, GAME_HEIGHT, GAME_FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

		if (_window) {
			Logger::LogLine(LogType::EngineRelated, "Game Window was created!");
		}

		Logger::LogLine(LogType::EngineRelated, "Creating Game Renderer...");

		_renderer = SDL_CreateRenderer(_window, -1, 0);

		if (_renderer) {
			Logger::LogLine(LogType::EngineRelated, "Game Renderer was created!");
			SDL_RenderSetLogicalSize(_renderer, GAME_WIDTH, GAME_HEIGHT);
			SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
		}

		Logger::LogLine(LogType::Warning, "Allowing a maximum of ", maxComponentTypes, " component types per entity");
		Logger::LogLine(LogType::Warning, "Allowing only 1 instance of each component type per entity");

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

	Logger::LogLine(LogType::EngineRelated, "Destroying Game Window...");
	SDL_DestroyWindow(_window);
	Logger::LogLine(LogType::EngineRelated, "Game Window was destroyed!");

	Logger::LogLine(LogType::EngineRelated, "Destroying Game Renderer...");
	SDL_DestroyRenderer(_renderer);
	Logger::LogLine(LogType::EngineRelated, "Game Renderer was destroyed!");

	Logger::LogLine(LogType::EngineRelated, "Destroying SDL_TTF...");
	TTF_Quit();
	Logger::LogLine(LogType::EngineRelated, "SDL_TTF was destroyed!");

	Logger::LogLine(LogType::EngineRelated, "Destroying SDL...");
	SDL_Quit();
	Logger::LogLine(LogType::EngineRelated, "SDL was destroyed!");
}
