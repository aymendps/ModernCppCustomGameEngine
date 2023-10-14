#pragma once
#include <string>
#include <iostream>
#include <functional>
#include "../../Core/EC/Component.h"

enum class CardEntityUniqueID {
	TEST_CARD,
	TEST_CARD_2,
	// It's important to keep this one at the end. The order matters to a function that creates a random card entity using a random ID
	UNDEFINED
};

enum class CardTargetType
{
	SELF,
	ENEMY,
	ALL_ENEMIES,
	ALL,
	UNDEFINED
};

enum class CardType
{
	ATTACK,
	DEFENSE,
	BUFF,
	DEBUFF,
	UNDEFINED
};

class CardComponent : public Component
{
	friend class CardEntityBuilder;

public:
	CardComponent();
	CardComponent(CardEntityUniqueID uniqueID, std::string name, std::string description, std::pair<int, int> diceRoll, 
		std::pair<int, int> diceModifiers, CardType cardType, CardTargetType targetType, int cost, std::function<void()> effect);
	~CardComponent();

	// Inherited via Component
	void Init() override;
	void Update(const float deltaTime) override;
	void Render() override;

	friend std::ostream& operator<<(std::ostream& os, const CardComponent& card);

private:
	CardEntityUniqueID _uniqueID;
	std::string _name;
	std::string _description;
	// first int is the number of dices to roll, second int is the number of sides on the dices
	std::pair <int, int> _diceRoll;
	// first int is the modifier to add to number of dices, second int is the modifier to add to number of sides on the dices
	std::pair <int, int> _diceModifiers;
	CardType _cardType;
	CardTargetType _targetType;
	int _cost;
	std::function<void()> _effect;
};

