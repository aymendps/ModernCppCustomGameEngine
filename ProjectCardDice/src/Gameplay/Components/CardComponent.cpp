#include "CardComponent.h"

CardComponent::CardComponent() : _uniqueID {CardEntityUniqueID::UNDEFINED}, _name { "Undefined" }, _description { "Undefined" }, 
_diceRoll { 0, 0 }, _diceModifiers { 0, 0 }, _cardType { CardType::UNDEFINED }, _targetType { CardTargetType::UNDEFINED }, _cost { 0 }, 
_effect { []() {} }
{
}

CardComponent::CardComponent(CardEntityUniqueID uniqueID, std::string name, std::string description, std::pair<int, int> diceRoll, 
	std::pair<int, int> diceModifiers, CardType cardType, CardTargetType targetType, int cost, std::function<void()> effect)
	: _uniqueID { uniqueID }, _name { name }, _description { description }, _diceRoll { diceRoll }, _diceModifiers { diceModifiers },
	_cardType { cardType }, _targetType { targetType }, _cost { cost }, _effect { effect }
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
	os << "ID: " << static_cast<int>(card._uniqueID) << " | " << "Name: " << card._name << " | " << "Desc: " << card._description << " | " << "Total Dice: "
		<< card._diceRoll.first + card._diceModifiers.first << "d" << card._diceRoll.second + card._diceModifiers.second << " | " << "Cost: " << card._cost
		<< " | " << "Card Type: " << static_cast<int>(card._cardType) << " | " << "Target Type: " << static_cast<int>(card._targetType);

	return os;
}
