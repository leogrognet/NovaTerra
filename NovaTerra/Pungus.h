#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "RigidBody.h"
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Random.h"
#include "Projectile.h"

enum class Direction { WEST, EAST };

class Pungus : public Entity {
private:
	Random* rng;
	int temp_rng;
	std::vector<Projectile> projectiles;
	Direction direction;
	sf::Texture pungusTexture;
	sf::Clock attackCD;
	sf::Clock poison;

	void attack(sf::Vector2f playerPos);
	sf::Vector2f calculateProjectileVelocity(sf::Vector2f startPos, sf::Vector2f targetPos, float timeToReach, float gravity);
public:
	Pungus(float posX, float posY, bool isStatic, bool asCollision);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	void changeDirection(int playerPosX);
	int getID() override;
	void draw(RenderWindow& window) override;


};
