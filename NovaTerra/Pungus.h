#pragma once

#include <SFML/Graphics.hpp>
#include "RigidBody.h"
#include "Player.h"

class Pungus {
private:
	sf::RectangleShape pungusShape;
	RigidBody* pungusBody;
	sf::Clock attackCD;
public:
	Pungus(sf::Vector2f pos);

	void update(float deltatime, Player& player);
	void draw(sf::RenderWindow& window);
	void attack();
};