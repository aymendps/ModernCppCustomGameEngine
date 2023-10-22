#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include "../Builders/CardEntityBuilder.h"

class Entity;

class CardCollection
{
public:
	// Delete copy constructor and assignment operator for singleton pattern
	CardCollection(CardCollection& other) = delete;
	void operator=(const CardCollection&) = delete;

	// Singleton instance
	static CardCollection& GetInstance() {
		static CardCollection instance;
		return instance;
	}

	/// <summary>
	/// Initializes the card collection, registering all card entity factories
	/// </summary>
	void Init();

	/// <summary>
	/// Registers a card entity factory for a specific card entity ID if it's not already registered
	/// </summary>
	/// <param name="id">The card entity unique ID</param>
	/// <param name="factory">The card entity factory function</param>
	void RegisterCardEntityFactory(CardEntityUniqueID id, std::function<Entity& (std::string)> factory);

	/// <summary>
	/// Creates a card entity with the specified ID and gives it the specified name
	/// </summary>
	/// <param name="id">The card entity unique ID</param>
	/// <param name="entityName">The name of the card entity</param>
	/// <returns>Reference to the created card entity</returns>
	Entity& CreateCardEntity(CardEntityUniqueID id, std::string entityName);

	/// <summary>
	/// Creates a random card entity and gives it the specified name
	/// </summary>
	/// <param name="entityName">The name of the card entity</param>
	/// <returns>Reference to the created card entity</returns>
	Entity& CreateRandomCardEntity(std::string entityName);

private:
	std::unordered_map<CardEntityUniqueID, std::function<Entity& (std::string)>> _cardEntityFactories;

	// Private constructor for singleton pattern
	CardCollection() {};
};

