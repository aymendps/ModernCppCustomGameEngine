#pragma once
#include <string>
#include <iostream>
#include <functional>
#include "../../Core/EC/Component.h"
#include "TransformComponent.h"

// ID for each card entity that can be created in the game. Cards are configured in CardEntityBuilder.
enum class CardEntityUniqueID {
	PYRO_TEST,
	GEO_TEST,
	TEMPEST_TEST,
	SHADOW_TEST,
	ALCHEMY_TEST,
	HOLY_TEST,
	NECRO_TEST,
	HEXER_TEST,
	NEUTRAL_TEST,
	// It's important to keep this one at the end. The order matters to a function that creates a random card entity using a random ID.
	UNDEFINED
};

// What the card targets when used.
enum class CardTargetType
{
	SELF,
	ENEMY,
	ALL_ENEMIES,
	ALL,
	UNDEFINED
};

// Each card belongs to a category. The category determines the color of the card and modifiers that can be applied to it.
enum class CardCategory
{
	PYRO,
	GEO,
	TEMPEST,
	SHADOW,
	ALCHEMY,
	HOLY,
	NECRO,
	HEXER,
	NEUTRAL
};

struct CardConfiguration {
	CardEntityUniqueID uniqueID = CardEntityUniqueID::UNDEFINED;
	std::string name = "UNDEFINED";
	std::string description = "UNDEFINED";
	// first int is the number of dices to roll, second int is the number of sides on the dices
	std::pair <int, int> diceRoll = { 0, 0 };
	// first int is the modifier to add to number of dices, second int is the modifier to add to number of sides on the dices
	std::pair <int, int> diceModifiers = { 0, 0 };
	CardCategory cardCategory = CardCategory::NEUTRAL;
	CardTargetType targetType = CardTargetType::UNDEFINED;
	int cost = 0;
	std::function<void()> effect = []() {};
};

class CardComponent : public Component
{
	friend class CardEntityBuilder;

public:
	static const Vector2D DEFAULT_CARD_SIZE; // = { 200, 300 };
	static constexpr SDL_Color DEFAULT_CARD_BACKGROUND_COLOR = { 50, 50, 50, 255 };
	static const std::unordered_map<CardCategory, SDL_Color> CARD_CATEGORY_COLORS;

	CardComponent(CardConfiguration cardConfiguration);
	~CardComponent();

	// Inherited via Component
	void Init() override;
	void Update(const float deltaTime) override;
	void Render() override;

	friend std::ostream& operator<<(std::ostream& os, const CardComponent& card);

private:
	CardConfiguration _cardConfiguration;
	TransformComponent* _transform;
	SDL_Rect _destinationRect;
	SDL_Color _cardCategoryColor;

	/* Render card elements in the following order */

	void RenderCardBackground() const;
	void RenderCardThumbnail() const;
	void RenderCardName() const;
	void RenderCardCost() const;
	void RenderCardDescription() const;
};

