#include "CardEntityBuilder.h"
#include "../../Core/Managers/EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Collections/CardCollection.h"

CardEntityBuilder::CardEntityBuilder() : _uniqueID{ CardEntityUniqueID::UNDEFINED }, _name{ "Undefined" }, _description{ "Undefined" },
_diceRoll{ 0, 0 }, _diceModifiers{ 0, 0 }, _cardType{ CardType::UNDEFINED }, _targetType{ CardTargetType::UNDEFINED }, _cost{ 0 },
_effect{ []() {} }
{
}

CardEntityBuilder::~CardEntityBuilder()
{
}

CardEntityBuilder& CardEntityBuilder::CardInfo(CardEntityUniqueID uniqueID, CardType type, std::string name, std::string description)
{
	_uniqueID = uniqueID;
	_cardType = type;
	_name = name;
	_description = description;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::DiceRoll(int numberOfDices, int numberOfSides)
{
	_diceRoll = { numberOfDices, numberOfSides };
	return *this;
}

CardEntityBuilder& CardEntityBuilder::DiceModifiers(int numberOfDices, int numberOfSides)
{
	_diceModifiers = { numberOfDices, numberOfSides };
	return *this;
}

CardEntityBuilder& CardEntityBuilder::Costs(int cost)
{
	_cost = cost;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::Targets(CardTargetType targetType)
{
	_targetType = targetType;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::ApplyEffect(std::function<void()> effect)
{
	_effect = effect;
	return *this;	
}

void CardEntityBuilder::Register()
{
	// Copy the fields to local variables so they can be captured by the lambda without having to capture the whole builder
	// Can't capture by reference because the builder will be destroyed eventually
	auto uniqueID { _uniqueID };
	auto name { _name };
	auto description { _description };
	auto diceRoll { _diceRoll };
	auto diceModifiers { _diceModifiers };
	auto cardType { _cardType };
	auto targetType { _targetType };
	auto cost { _cost };
	auto effect { _effect };

	// Factory function for creating the card entity
	auto factory = [uniqueID, name, description, diceRoll, diceModifiers, cardType, targetType, cost, effect]
	(std::string entityName)->Entity& {
		Entity& entity = EntityManager::GetInstance().CreateEntity(entityName);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<CardComponent>(uniqueID, name, description, diceRoll, diceModifiers, cardType, targetType, cost, effect);
		return entity;
	};

	CardCollection::GetInstance().RegisterCardEntityFactory(_uniqueID, factory);

	ResetFields();
}

void CardEntityBuilder::ResetFields()
{
	// Reset the fields to their default values

	_uniqueID = CardEntityUniqueID::UNDEFINED;
	_name = "Undefined";
	_description = "Undefined";
	_diceRoll = { 0, 0 };
	_diceModifiers = { 0, 0 };
	_cardType = CardType::UNDEFINED;
	_targetType = CardTargetType::UNDEFINED;
	_cost = 0;
	_effect = []() {};
}
