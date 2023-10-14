#pragma once
#include "../Components/CardComponent.h"

class CardEntityBuilder
{
public:
	CardEntityBuilder();
	~CardEntityBuilder();

	// Sets the basic information of the card
	CardEntityBuilder& CardInfo(CardEntityUniqueID uniqueID, CardType type, std::string name, std::string description);
	// Sets the dice roll values of the card (number of dices and number of sides)
	CardEntityBuilder& DiceRoll(int numberOfDices, int numberOfSides);
	// Sets the dice modifiers of the card. These are added to the dice roll values
	CardEntityBuilder& DiceModifiers(int numberOfDices, int numberOfSides);
	// Sets the cost of the card (how many action points it costs to play)
	CardEntityBuilder& Costs(int cost);
	// Sets the target type of the card (who can be targeted by the card)
	CardEntityBuilder& Targets(CardTargetType targetType);
	// Sets the effect of the card (what happens when the card is played)
	CardEntityBuilder& ApplyEffect(std::function<void()> effect);

	// Registers the card in the card collection. This should be called at the end of the card creation
	void Register();

private:
	// The fields of the card

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

	// Resets the fields of the builder to their default values. This is called after registering the card.
	void ResetFields();
};

