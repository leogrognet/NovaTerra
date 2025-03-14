#include "Biome.h"

Biome::Biome(sf::FloatRect _bounds)
	: bounds(_bounds), bossDefeated(false), bossSpawned(false) {}

bool Biome::isBossDefeated() const {
	return bossDefeated;
}

void Biome::defeatBoss() {
	bossDefeated = true;
	std::cout << "Boss vaincu\n";
}

void Biome::startBossFight() {

}