#pragma once
#include "../Components/CardComponent.h"

class CardEntityBuilder
{
public:
	CardEntityBuilder();
	~CardEntityBuilder();

	// Sets the basic information of the card
	CardEntityBuilder& CardInfo(CardEntityUniqueID uniqueID, CardCategory category, std::string name, std::string description);
	// Sets the path to the thumbnail that will be loaded by the texture manager and rendered on the card
	CardEntityBuilder& ThumbnailFrom(const char* thumbnailPath);
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
	CardConfiguration _cardConfiguration;

	// Resets the card configuration to default values. This should be called after the card is registered
	void ResetConfiguration();
};

