#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity {
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::CircleShape ball;
	bool useableAsCounterAttack;
	float gravity = 300.0f;
public:
	Projectile(sf::Vector2f startPos, sf::Vector2f startVelocity, bool useableAsCounterAttack, bool isStatic, bool asCollision);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;

	void draw(sf::RenderWindow& window) override;

};
#pragma once
