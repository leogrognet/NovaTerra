#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "Biome.h"
#include "Scroll.h"
#include "Map.h"

class World {
public:
	World(const std::string& filePath);

	void update(float deltatime, sf::Vector2f playerPos);
	void render(sf::RenderWindow& window);

	bool isBossZone(sf::Vector2f playerPos);
	void startBossFight();
	bool isBossDefeated();
	void nextBiome();

private:
	Map* map;
	std::vector<std::unique_ptr<Biome>> biomes;
	int currentBiome;
	int currentBossIndex;
	Scroll* scroll;
};
