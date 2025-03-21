#pragma once

#include <iostream>
#include <random>

class Random {
private:
	std::mt19937 gen;
	std::uniform_int_distribution<int> distrib;

public:
	Random(int min, int max);
	int getRandomNumber();
};
