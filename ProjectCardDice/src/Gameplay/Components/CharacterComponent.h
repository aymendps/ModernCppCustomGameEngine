#pragma once
#include "../../Core/EC/Component.h"
#include "TransformComponent.h"
#include "../../Core/CustomDestroyers/SDL_FontDestroyer.h"

struct CharacterConfiguration {
	std::string name = "UNDEFINED";
	int maxHealth = 0;
	int currentHealth = 0;
	int currentShield = 0;
};

class CharacterComponent : public Component
{
public:
	CharacterComponent(Entity* owner, CharacterConfiguration configuration);
	~CharacterComponent();

	// Inherited via Component
	virtual void Init() override;
	virtual void HandleEvents(SDL_Event& event) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	void TakeDamage(int amount);
	void HealDamage(int amount);
	void AddShield(int amount);
	void RemoveShield(int amount);

	bool IsDead() const { return _isDead; }

	std::string HealthAndShieldToString() const;

private:
	CharacterConfiguration _configuration;
	bool _isDead;
	TransformComponent* _transform;
	SDL_Rect _destinationRect;
	std::unique_ptr<SDL_Font, SDL_FontDestroyer> _nameFont;
	std::unique_ptr<SDL_Font, SDL_FontDestroyer> _healthAndShieldFont;
	int _lastHealth;
	int _lastShield;

	/* Render elements in the following order */

	void RenderName();
	void RenderHealthAndShieldBar();
};

