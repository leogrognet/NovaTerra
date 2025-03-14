#include "World.h"

World::World(const std::string& filePath) : currentBiome(0), currentBossIndex(0) {
	scroll = new Scroll(1200, 900);
	map = new Map(filePath, "assets/map/map_tileset/Tileset_Grass.png", 32, {});
	biomes.push_back(std::make_unique<Biome>(sf::FloatRect(0, 0, 1200, 1000)));
	biomes.push_back(std::make_unique<Biome>(sf::FloatRect(1200, 0, 1200, 1000)));
	biomes.push_back(std::make_unique<Biome>(sf::FloatRect(2400, 0, 1200, 1000)));
	// Appelez la suite des biomes...
}

void World::update(float deltatime, sf::Vector2f playerPos) {
	scroll->move(2.f, 0.f);
	for (int i = 0; i < biomes.size(); i++) {
		if (biomes[i]->getBounds().contains(playerPos.x, playerPos.y)) {
			if (currentBiome != i) {
				currentBiome = i;
				std::cout << "Nouveau biome : " << currentBiome << std::endl;
			}
		}
	}
	//std::cout << playerPos.x << " " << playerPos.y << std::endl;
}

void World::render(sf::RenderWindow& window) {
	scroll->applyView(window);
	map->draw(window);
}

bool World::isBossZone(sf::Vector2f playerPos) {
	return true;
}

void World::startBossFight() {

}

bool World::isBossDefeated() {

}

void World::nextBiome() {
	currentBiome += 1;
	std::cout << "Changement de biome\n";
}
