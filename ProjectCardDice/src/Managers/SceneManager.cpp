#include "SceneManager.h"
#include "../Scenes/TestScene.h"
#include "../Game.h"

SceneManager::SceneManager()
{
	std::cout << "Creating the initial Scene..." << std::endl;
	_activeScene.reset(new TestScene({100, 100}, 10.0f));
	std::cout << "Initial Scene created!" << std::endl;

}

void SceneManager::Init()
{
	_activeScene->Init();
}

void SceneManager::HandleEvents(SDL_Event& event) const
{
	if (!_isTransitioning && _fadeDirection == FadeDirection::None)
	{
		_activeScene->HandleEvents(event);
	}
}

void SceneManager::Update(const float deltaTime)
{
	if (!_isTransitioning)
	{
		EntityManager::GetInstance().Refresh();

		_activeScene->Update(deltaTime);
		EntityManager::GetInstance().Update(deltaTime);

		if (_fadeDirection != FadeDirection::None) {
			SceneManager::UpdateFadeScreen(deltaTime);
		}
	}
	else {
		// Listen for when the switch scene thread wants to init the new scene and destroy the old scene
		// Once the new scene is initialized, the switch scene thread will set _isTransitioning back to false
		// The new scene will start updating and rendering in the next frame
		if (_shouldInitNewScene) {
			_initNewScene();
			_shouldInitNewScene = false;
		}
	}
}

void SceneManager::Render() const
{
	if (!_isTransitioning)
	{
		_activeScene->Render();
		EntityManager::GetInstance().Render();

		if (_fadeDirection != FadeDirection::None) {
			SceneManager::RenderFadeScreen();
		}
	}
}

void SceneManager::UpdateFadeScreen(const float deltaTime)
{
	if (_fadeDirection == FadeDirection::Out) {
		_fadeScreenAlpha += deltaTime * 255 / _fadeDuration;
		if (_fadeScreenAlpha >= 255) {
			_fadeScreenAlpha = 255;
			_fadeDirection = FadeDirection::None;
			//std::cout << "Fade out complete" << std::endl;
		}
	}
	else if (_fadeDirection == FadeDirection::In) {
		_fadeScreenAlpha -= deltaTime * 255 / _fadeDuration;
		if (_fadeScreenAlpha <= 0) {
			_fadeScreenAlpha = 0;
			_fadeDirection = FadeDirection::None;
			//std::cout << "Fade in complete" << std::endl;
		}
	}
}

void SceneManager::RenderFadeScreen() const
{
	// Render a black rectangle=screen with alpha value of _fadeScreenAlpha to create a fade effect
	SDL_SetRenderDrawColor(Game::renderer, _fadeScreenColor.r, _fadeScreenColor.g, _fadeScreenColor.b,
		static_cast<Uint8>(_fadeScreenAlpha));
	SDL_Rect rect{ 0, 0, Game::GAME_WIDTH, Game::GAME_HEIGHT };
	SDL_RenderFillRect(Game::renderer, &rect);

	// Reset the render draw color and blend mode
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}
