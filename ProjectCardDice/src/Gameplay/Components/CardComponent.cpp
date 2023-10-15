#include "CardComponent.h"

CardComponent::CardComponent(CardConfiguration cardConfiguration) : _cardConfiguration(cardConfiguration)
{
}

CardComponent::~CardComponent()
{
}

void CardComponent::Init()
{
	std::cout << *this << std::endl;
}

void CardComponent::Update(const float deltaTime)
{
}

void CardComponent::Render()
{
}

std::ostream& operator<<(std::ostream& os, const CardComponent& card)
{
	// Print all in same line
	os << "CardComponent: " << card._cardConfiguration.name << " | " << card._cardConfiguration.description << " | " <<
		card._cardConfiguration.diceRoll.first << "d" << card._cardConfiguration.diceRoll.second << " + " <<
		card._cardConfiguration.diceModifiers.first << "d" << card._cardConfiguration.diceModifiers.second << " | " << "CardType: " <<
		static_cast<int>(card._cardConfiguration.cardType) << " | " << "TargetType: " << static_cast<int>(card._cardConfiguration.targetType) 
		<< " | " << "Costs: " << card._cardConfiguration.cost;

	return os;
}
