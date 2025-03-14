#pragma once

#include <SFML/Graphics.hpp>
#include "RigidBody.h"
#include "Player.h"

class Pungus : public Entity {
private:
	sf::RectangleShape shape;
	RigidBody* body;
	sf::Clock attackCD;
	sf::Texture m_texture;
public:
	Pungus(vector<shared_ptr<Entity>>& shape, sf::Vector2f pos, bool isStatic);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	void draw(RenderWindow& window) override;
	void attack();

	sf::Clock poison;
};