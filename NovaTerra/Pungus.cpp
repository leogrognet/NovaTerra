#include "Pungus.h"

Pungus::Pungus(float posX, float posY, bool isStatic, bool asCollision) : Entity(posX, posY, isStatic, asCollision) {
	rng = new Random(0, 4);
	pungusTexture.loadFromFile("../assets/slimet.png");
	m_shape.setTexture(pungusTexture);
	m_shape.setPosition(posX, posY);
	m_shape.setScale(1.f, 1.f);
	direction = Direction::WEST;
}

void Pungus::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
	sf::Vector2f playerPos;
	for (auto entity : colliders) {
		if (entity->getID() == 1) {
			playerPos.x = entity->getSprite().getPosition().x;
			playerPos.y = entity->getSprite().getPosition().y;
		}
	}

	attack(playerPos);
	changeDirection(playerPos.x);
	for (auto& projectile : projectiles) {
		projectile.update(deltaTime, colliders);
	}

	Entity::update(deltaTime, colliders);
}

void Pungus::draw(sf::RenderWindow& window) {
	window.draw(m_shape);

	for (auto& projectile : projectiles) {
		projectile.draw(window);
	}
}

int Pungus::getID()
{
	return 3;
}

void Pungus::changeDirection(int playerPosX) {
	if (playerPosX < m_shape.getPosition().x && direction != Direction::WEST) {
		direction = Direction::WEST;
	}
	else if (playerPosX > m_shape.getPosition().x && direction != Direction::EAST) {
		direction = Direction::EAST;
	}
}

void Pungus::attack(sf::Vector2f playerPos) {
	if (attackCD.getElapsedTime().asSeconds() > 1.0f) {
		temp_rng = rng->getRandomNumber();
		attackCD.restart();

		sf::Vector2f startPos = m_shape.getPosition();
		sf::Vector2f targetPos = { playerPos.x, playerPos.y };
		float timeToReach = 2.5f;
		float gravity = 300.0f;

		sf::Vector2f velocity = calculateProjectileVelocity(startPos, targetPos, timeToReach, gravity);

		if (temp_rng == 0) {
			projectiles.push_back(Projectile(startPos, velocity, true, false, true));
		}
		else {
			projectiles.push_back(Projectile(startPos, velocity, false, false, true));
		}
	}
}

sf::Vector2f Pungus::calculateProjectileVelocity(sf::Vector2f startPos, sf::Vector2f targetPos, float timeToReach, float gravity) {
	sf::Vector2f velocity;
	velocity.x = (targetPos.x - startPos.x) / timeToReach;
	velocity.y = (targetPos.y - startPos.y) / timeToReach - 0.5f * gravity * timeToReach;

	return velocity;
}
