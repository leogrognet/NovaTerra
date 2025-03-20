#include "Random.h"

Random::Random(int min, int max) : gen(std::random_device{}()), distrib(min, max) {}

int Random::getRandomNumber() {
	return distrib(gen);
}
