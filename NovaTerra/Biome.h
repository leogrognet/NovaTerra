#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"

class Biome {
public:
	Biome(const std::string& filePath, sf::Vector2f _startPosition);

	void load();
	void update(float deltatime);
	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const { return bounds; }
	bool hasBoss() const { return bossSpawned; }
	void startBossFight();
	bool isBossDefeated() const;
	void defeatBoss();

private:
	Map* map;
	sf::Vector2f startPosition;
	sf::FloatRect bounds;
	bool bossSpawned;
	bool bossDefeated;
};
