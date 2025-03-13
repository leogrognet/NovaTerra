#include "Biome.h"

Biome::Biome(const std::string& filePath, sf::Vector2f _startPosition)
	: bossDefeated(false), bossSpawned(false), startPosition(_startPosition) {
	map = new Map(filePath, "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });
}

void Biome::load() {

}

void Biome::update(float deltatime) {

}

void Biome::render(sf::RenderWindow& window) {

}

bool Biome::isBossDefeated() const {
	return bossDefeated;
}

void Biome::defeatBoss() {
	bossDefeated = true;
	std::cout << "Boss vaincu\n";
}

void Biome::startBossFight() {

}