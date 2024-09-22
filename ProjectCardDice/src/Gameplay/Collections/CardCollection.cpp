#include "CardCollection.h"
#include "../../Core/Math/Randomizer.h"
#include "../../Core/Utils/Logger.h"

void CardCollection::Init()
{
	CardEntityBuilder builder{};

	/* Register test card for each card category */

	builder.CardInfo(CardEntityUniqueID::ALCHEMY_TEST, CardCategory::ALCHEMY, "Alchemy Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Hunter7.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::GEO_TEST, CardCategory::GEO, "Geo Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Geomancer2.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::HEXER_TEST, CardCategory::HEXER, "Hexer Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Arcanist19.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::HOLY_TEST, CardCategory::HOLY, "Holy Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Priest19.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::NECRO_TEST, CardCategory::NECRO, "Necro Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Necromancer2.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::NEUTRAL_TEST, CardCategory::NEUTRAL, "Neutral Test Card", "This is a test card.")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::PYRO_TEST, CardCategory::PYRO, "Pyro Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Pyromancer2.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::HYDRO_TEST, CardCategory::HYDRO, "Hydro Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Cryomancer9.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::SHADOW_TEST, CardCategory::SHADOW, "Shadow Test Card", "This is a test card.")
		.ThumbnailFrom("assets/ignore/Ranger7.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(1)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();

	builder.CardInfo(CardEntityUniqueID::TEMPEST_TEST, CardCategory::TEMPEST, "Tempest Test Card", "This is a test cardaaaaa This is a test card.")
		.ThumbnailFrom("assets/ignore/Electromancer1.png")
		.DiceRoll(1, 6)
		.DiceModifiers(0, 0)
		.Costs(2)
		.Targets(CardTargetType::ENEMY)
		.ApplyEffect([]() { Logger::LogLine(LogType::Log, "Test Card Effect"); })
		.Register();
}

void CardCollection::RegisterCardEntityFactory(CardEntityUniqueID id, std::function<Entity* (std::string, std::string)> factory)
{
	// Don't register card factory if card entity ID is already registered
	if (_cardEntityFactories.find(id) != _cardEntityFactories.end())
	{
		Logger::LogLine(LogType::Warning, "Card entity factory for ID ", static_cast<int>(id), " is already registered!");
		return;
	}

	Logger::LogLine(LogType::Success, "Registering card entity factory for ID ", static_cast<int>(id));
	_cardEntityFactories[id] = factory;
}

Entity* CardCollection::CreateCardEntity(CardEntityUniqueID id, std::string entityName, std::string sceneName)
{
	return _cardEntityFactories[id](entityName, sceneName);
}

Entity* CardCollection::CreateRandomCardEntity(std::string entityName, std::string sceneName)
{
	// Get a random card entity ID from the enum excluding the UNDEFINED value
	int randomID = Randomizer::GetRandomInt() % static_cast<int>(CardEntityUniqueID::UNDEFINED);
	CardEntityUniqueID randomCardEntityID = static_cast<CardEntityUniqueID>(randomID);

	return _cardEntityFactories[randomCardEntityID](entityName, sceneName);
}
