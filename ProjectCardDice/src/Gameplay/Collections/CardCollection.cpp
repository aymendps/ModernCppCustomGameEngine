#include "CardCollection.h"
#include "../../Core/Math/Randomizer.h"

void CardCollection::Init()
{
	CardEntityBuilder builder{};

	/* Register test card for each card category */

	builder.CardInfo(CardEntityUniqueID::ALCHEMY_TEST, CardCategory::ALCHEMY, "Alchemy Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::GEO_TEST, CardCategory::GEO, "Geo Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::HEXER_TEST, CardCategory::HEXER, "Hexer Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::HOLY_TEST, CardCategory::HOLY, "Holy Test Card", "This is a test card.")
		.ThumbnailFrom("assets/wind-grasp-air-3.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::NECRO_TEST, CardCategory::NECRO, "Necro Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::NEUTRAL_TEST, CardCategory::NEUTRAL, "Neutral Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::PYRO_TEST, CardCategory::PYRO, "Pyro Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::SHADOW_TEST, CardCategory::SHADOW, "Shadow Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::TEMPEST_TEST, CardCategory::TEMPEST, "Tempest Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();
}

void CardCollection::RegisterCardEntityFactory(CardEntityUniqueID id, std::function<Entity& (std::string)> factory)
{
	// Don't register card factory if card entity ID is already registered
	if (_cardEntityFactories.find(id) != _cardEntityFactories.end())
	{
		std::cout << "\033[31m" << "Card entity factory for ID " << static_cast<int>(id) << " is already registered!" << "\033[0m" << std::endl;
		return;
	}

	std::cout << "\033[32m" << "Registering card entity factory for ID " << static_cast<int>(id) << "\033[0m" << std::endl;
	_cardEntityFactories[id] = factory;
}

Entity& CardCollection::CreateCardEntity(CardEntityUniqueID id, std::string entityName)
{
	return _cardEntityFactories[id](entityName);
}

Entity& CardCollection::CreateRandomCardEntity(std::string entityName)
{
	// Get a random card entity ID from the enum excluding the UNDEFINED value
	int randomID = Randomizer::GetRandomInt() % static_cast<int>(CardEntityUniqueID::UNDEFINED);
	CardEntityUniqueID randomCardEntityID = static_cast<CardEntityUniqueID>(randomID);

	return _cardEntityFactories[randomCardEntityID](entityName);
}
