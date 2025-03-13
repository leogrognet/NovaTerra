#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Biome.h"
#include "Scroll.h"

class World {
public:
	World();

	void load();
	void update(float deltatime);
	void render(sf::RenderWindow& window);

	bool isBossZone(sf::Vector2f playerPos);
	bool startBossFight();
	bool isBossDefeated();

private:
	std::vector<std::unique_ptr<Biome>> biomes;
	int currentBossIndex;
	Scroll* scroll;
};
