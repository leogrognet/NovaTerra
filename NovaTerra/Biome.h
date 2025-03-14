#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"

class Biome {
public:
	Biome(sf::FloatRect _bounds);

	sf::FloatRect getBounds() const { return bounds; }
	bool hasBoss() const { return bossSpawned; }
	void startBossFight();
	bool isBossDefeated() const;
	void defeatBoss();

private:
	sf::FloatRect bounds;
	bool bossSpawned;
	bool bossDefeated;
};
