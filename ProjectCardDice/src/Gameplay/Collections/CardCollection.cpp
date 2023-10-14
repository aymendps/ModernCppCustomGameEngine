#include "CardCollection.h"
#include "../../Core/Math/Randomizer.h"

void CardCollection::Init()
{
	CardEntityBuilder builder{};

	builder.CardInfo(CardEntityUniqueID::TEST_CARD, CardType::ATTACK, "Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card Effect" << std::endl; })
		.Register();

	builder.CardInfo(CardEntityUniqueID::TEST_CARD_2, CardType::ATTACK, "Test Card 2", "This is a test card 2.")
		.DiceRoll(1, 6)
		.DiceModifiers(1, 1)
		.Costs(2)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { std::cout << "Test Card 2 Effect" << std::endl; })
		.Register();
}

void CardCollection::RegisterCardEntityFactory(CardEntityUniqueID id, std::function<Entity& (std::string)> factory)
{
	// check if the id is already registered
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
