#include "CardEntityBuilder.h"
#include "../../Core/Managers/EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Collections/CardCollection.h"

CardEntityBuilder::CardEntityBuilder()
{
	ResetConfiguration();
}

CardEntityBuilder::~CardEntityBuilder()
{
}

CardEntityBuilder& CardEntityBuilder::CardInfo(CardEntityUniqueID uniqueID, CardCategory category, std::string name, std::string description)
{
	_cardConfiguration.uniqueID = uniqueID;
	_cardConfiguration.cardCategory = category;
	_cardConfiguration.name = name;
	_cardConfiguration.description = description;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::ThumbnailFrom(const char* thumbnailPath)
{
	_cardConfiguration.thumbnailPath = thumbnailPath;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::DiceRoll(int numberOfDices, int numberOfSides)
{
	_cardConfiguration.diceRoll = { numberOfDices, numberOfSides };
	return *this;
}

CardEntityBuilder& CardEntityBuilder::DiceModifiers(int numberOfDices, int numberOfSides)
{
	_cardConfiguration.diceModifiers = { numberOfDices, numberOfSides };
	return *this;
}

CardEntityBuilder& CardEntityBuilder::Costs(int cost)
{
	_cardConfiguration.cost = cost;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::Targets(CardTargetType targetType)
{
	_cardConfiguration.targetType = targetType;
	return *this;
}

CardEntityBuilder& CardEntityBuilder::ApplyEffect(std::function<void()> effect)
{
	_cardConfiguration.effect = effect;
	return *this;	
}

void CardEntityBuilder::Register()
{
	// Can't capture by reference because the builder will be destroyed eventually or the configuration will be reset
	auto cardConfiguration { _cardConfiguration };

	// Factory function for creating the card entity
	auto factory = [cardConfiguration]
	(std::string entityName)->Entity& {
		Entity& entity = EntityManager::GetInstance().CreateEntity(entityName);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<CardComponent>(cardConfiguration);
		return entity;
	};

	CardCollection::GetInstance().RegisterCardEntityFactory(_cardConfiguration.uniqueID, factory);

	ResetConfiguration();
}

void CardEntityBuilder::ResetConfiguration()
{
	_cardConfiguration = CardConfiguration();
}
