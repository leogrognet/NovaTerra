#include "World.h"

//mettre le scroll dans le update

World::World() : currentBossIndex(0) {
	scroll = new Scroll(1200, 900);
	biomes.push_back(std::make_unique<Biome>("assets/map/lobby.txt", sf::Vector2f(0, 0)));
}

void World::load() {
	for (auto& biome : biomes) {
		biome->load();
	}
}

void World::update(float deltatime) {
	scroll->move(1.f, 0.f);

}

void World::render(sf::RenderWindow& window) {
	scroll->applyView(window);
	for (auto& biome : biomes) {
		biome->render(window);
	}
}