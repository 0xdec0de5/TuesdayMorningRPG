#pragma once
#include <random>

inline unsigned int roll_dice(const unsigned int min, const unsigned int max)
{
	std::random_device device;
	std::mt19937 engine(device());
	const std::uniform_int_distribution<unsigned int> dist(min, max);
	return dist(engine);
}