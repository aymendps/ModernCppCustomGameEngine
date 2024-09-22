#include "CharacterComponent.h"
#include "../../Core/EC/Entity.h"
#include "../../Core/Events/MouseEvents.h"
#include "../../Core/Managers/TextureManager.h"
#include "../../Game.h"
#include "../../Core/Utils/Logger.h"

CharacterComponent::CharacterComponent(Entity* owner, ComponentTypeID typeID, CharacterConfiguration configuration) : Component(owner, typeID), _configuration{ configuration }, _isDead{ false }, _transform{ nullptr },
_destinationRect { 0, 0, 0, 0 }, _lastHealth { configuration.currentHealth }, _lastShield { configuration.currentShield }
{
}

CharacterComponent::~CharacterComponent()
{
}

void CharacterComponent::Init()
{
	_transform = _owner->GetComponent<TransformComponent>();

	// Create textures and fonts for the character
	_nameFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 30, _configuration.name.c_str()));
	_healthAndShieldFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 24, HealthAndShieldToString().c_str()));
}

void CharacterComponent::HandleEvents(SDL_Event& event)
{
	// Testing mouse events

	_destinationRect = _transform->GetDestinationRect();

	if (MouseEvents::IsLeftClicked(event, _destinationRect))
	{
		Logger::LogLine(GetOwner()->GetUniqueName(), LogType::Log, _configuration.name, " was left clicked!");
	}

	if (MouseEvents::IsRightClicked(event, _destinationRect))
	{
		Logger::LogLine(GetOwner()->GetUniqueName(), LogType::Log, _configuration.name, " was right clicked!");
	}

	if (MouseEvents::IsLeftDoubleClicked(event, _destinationRect))
	{
		Logger::LogLine(GetOwner()->GetUniqueName(), LogType::Log, _configuration.name, " was left double clicked!");
	}

	if (MouseEvents::IsRightDoubleClicked(event, _destinationRect))
	{
		Logger::LogLine(GetOwner()->GetUniqueName(), LogType::Log, _configuration.name, " was right double clicked!");
	}

	Vector2D mousePosition;

	if (MouseEvents::IsLeftPressed(event, _destinationRect, mousePosition))
	{
		Logger::LogLine(GetOwner()->GetUniqueName(), LogType::Log, _configuration.name, " was left pressed at ", mousePosition, "!");
		_transform->position.x = mousePosition.x - _destinationRect.w / 2;
	}

	if (MouseEvents::IsRightPressed(event, _destinationRect, mousePosition))
	{
		Logger::LogLine(GetOwner()->GetUniqueName(), LogType::Log, _configuration.name, " was right pressed at ", mousePosition, "!");
		_transform->position.y = mousePosition.y - _destinationRect.h / 2;
	}
}

void CharacterComponent::Update(const float deltaTime)
{
	_destinationRect = _transform->GetDestinationRect();

	// Update health and shield font if the health or shield has changed
	if (_lastHealth != _configuration.currentHealth || _lastShield != _configuration.currentShield)
	{
		_healthAndShieldFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 24, HealthAndShieldToString().c_str()));

		_lastHealth = _configuration.currentHealth;
		_lastShield = _configuration.currentShield;
	}	
}

void CharacterComponent::Render()
{
	RenderName();
	RenderHealthAndShieldBar();
}

void CharacterComponent::RenderName()
{
	// Display the name of the character above the character if it's hovered
	if (MouseEvents::IsHovered(_destinationRect))
	{
		SDL_Rect nameRect = {
		_destinationRect.x + (_destinationRect.w / 2) - static_cast<int>(_nameFont->width * _transform->scale / 2),
		_destinationRect.y - static_cast<int>(40 * _transform->scale),
		static_cast<int>(_nameFont->width * _transform->scale),
		static_cast<int>(_nameFont->height * _transform->scale)
		};

		TextureManager::RenderTexture(_nameFont->texture, &nameRect);
	}
}

void CharacterComponent::RenderHealthAndShieldBar()
{
	// Render a healthbar background related to max health
	SDL_Rect maxHealthBarRect = {
		_destinationRect.x,
		_destinationRect.y + _destinationRect.h + static_cast<int>(20 * _transform->scale),
		_destinationRect.w,
		static_cast<int>(20 * _transform->scale)
	};
	SDL_SetRenderDrawColor(Game::GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Game::GetRenderer(), &maxHealthBarRect);

	// Render a healthbar foreground related to current health
	SDL_Rect currentHealthBarRect = {
		_destinationRect.x,
		_destinationRect.y + _destinationRect.h + static_cast<int>(20 * _transform->scale),
		_destinationRect.w * _configuration.currentHealth / _configuration.maxHealth,
		static_cast<int>(20 * _transform->scale)
	};

	// If the character has a shield, render the healthbar in grey, otherwise render it in red
	if(_configuration.currentShield > 0) { 
		SDL_SetRenderDrawColor(Game::GetRenderer(), 100, 100, 100, 255);
	}
	else {
		SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 0, 0, 255);
	}
	SDL_RenderFillRect(Game::GetRenderer(), &currentHealthBarRect);

	// Render font that displays current health and current shield in the middle of the healthbar
	SDL_Rect healthFontRect = {
		_destinationRect.x + (_destinationRect.w / 2) - static_cast<int>(_healthAndShieldFont->width * _transform->scale / 2),
		_destinationRect.y + _destinationRect.h + static_cast<int>(17 * _transform->scale),
		static_cast<int>(_healthAndShieldFont->width * _transform->scale),
		static_cast<int>(_healthAndShieldFont->height * _transform->scale)
	};
	TextureManager::RenderTexture(_healthAndShieldFont->texture, &healthFontRect);
}

void CharacterComponent::TakeDamage(int amount)
{
	// If the damage is 0 or below, do nothing
	if (amount <= 0)
	{
		return;
	}

	// If the character has a shield, remove the damage from the shield first
	if (_configuration.currentShield > 0)
	{
		_configuration.currentShield -= amount;

		// If the shield is now below 0, remove the remaining damage from the character's health
		if (_configuration.currentShield < 0)
		{
			_configuration.currentHealth += _configuration.currentShield;
			_configuration.currentShield = 0;
		}
	}
	// If the character does not have a shield, remove the damage from the character's health directly
	else
	{
		_configuration.currentHealth -= amount;
	}

	// If the character's health is now below 0, flag it as dead
	if (_configuration.currentHealth <= 0)
	{
		_configuration.currentHealth = 0;
		_isDead = true;
	}
}

void CharacterComponent::HealDamage(int amount)
{
	// If the amount is 0 or below, do nothing
	if (amount <= 0)
	{
		return;
	}

	_configuration.currentHealth += amount;

	// If the character's health is now above the maximum health, set it to the maximum health
	if (_configuration.currentHealth > _configuration.maxHealth)
	{
		_configuration.currentHealth = _configuration.maxHealth;
	}
}

void CharacterComponent::AddShield(int amount)
{
	// If the amount is 0 or below, do nothing
	if (amount <= 0)
	{
		return;
	}

	_configuration.currentShield += amount;
}

void CharacterComponent::RemoveShield(int amount)
{
	// If the amount is 0 or below, do nothing
	if (amount <= 0)
	{
		return;
	}

	_configuration.currentShield -= amount;

	// If the shield is now below 0, set it to 0
	if (_configuration.currentShield < 0)
	{
		_configuration.currentShield = 0;
	}	
}

std::string CharacterComponent::HealthAndShieldToString() const
{
	std::string result{std::to_string(_configuration.currentHealth) + "/" + std::to_string(_configuration.maxHealth)};
	if (_configuration.currentShield > 0)
	{
		result += " (" + std::to_string(_configuration.currentShield) + ")";
	}

	return result;
}

