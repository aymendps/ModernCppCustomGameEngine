#include "Randomizer.h"

std::default_random_engine Randomizer::_generator{};
std::uniform_int_distribution<int> Randomizer::_distribution{0, 100000};

void Randomizer::Seed(unsigned int seed)
{
	_generator.seed(seed);
}

void Randomizer::RandomSeed()
{
	_generator.seed(std::random_device()());
}

int Randomizer::GetRandomInt()
{
	return _distribution(_generator);
}

int Randomizer::GetRandomInt(int min, int max)
{
	// Make sure max is not greater than 100000 because that is the maximum value of the distribution.
	max = max > 100000 ? 100000 : max;

	return GetRandomInt() % (max - min + 1) + min;
}

int Randomizer::GetDiceRoll(int diceCount, int diceSides)
{
	int result { 0 };

	for (int i = 0; i < diceCount; i++)
	{
		result += GetRandomInt(1, diceSides);
	}

	return result;
}
