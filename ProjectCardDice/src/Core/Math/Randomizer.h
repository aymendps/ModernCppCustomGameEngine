#pragma once
#include <random>

class Randomizer
{
public:
	/// <summary>
	/// Sets the seed of the randomizer to the given value. Should be used when loading a game run or when replaying a game run.
	/// </summary>
	/// <param name="seed">The seed to set</param>
	static void Seed(unsigned int seed);

	/// <summary>
	/// Sets the seed of the randomizer to a random value. Should be used when creating a new game run.
	/// </summary>
	static void RandomSeed();

	/// <summary>
	/// Returns a random integer between 0 and 100000.
	/// </summary>
	static int GetRandomInt();

	/// <summary>
	/// Returns a random integer between min and max. Max is replaced by 100000 if it is greater than that.
	/// </summary>
	static int GetRandomInt(int min, int max);

	/// <summary>
	/// Generates the result of rolling the given amount of dice with the given amount of sides.
	/// </summary>
	/// <param name="diceCount">The amount of dice to roll</param>
	/// <param name="diceSides">The amount of sides each dice has</param>
	/// <returns>The result of the dice roll</returns>
	static int GetDiceRoll(int diceCount, int diceSides);

private:
	static std::mt19937 _generator;
	static std::uniform_int_distribution<int> _distribution;
};

