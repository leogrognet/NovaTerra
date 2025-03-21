#include "Pungus.h"

Pungus::Pungus(float posX, float posY, bool isStatic, bool asCollision) : Entity(posX, posY, isStatic, asCollision) {
	rng = new Random(0, 4);
	pungusTexture.loadFromFile("../NovaTerra/assets/Image/Boss/MOB.png");
	m_shape.setTexture(pungusTexture);
	m_shape.setPosition(posX, posY);
	float scaleFactorX = 128 / m_shape.getGlobalBounds().width / 4;
	float scaleFactorY = 256 / m_shape.getGlobalBounds().height / 4;

	m_shape.setScale({ scaleFactorX,scaleFactorY });
	direction = Direction::WEST;

	m_detectionRange.setRadius(500);
	m_detectionRange.setFillColor(Color::Red);
	m_detectionRange.setOrigin(500, 500);
	m_detectionRange.setPosition(m_shape.getPosition());
}

void Pungus::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
	Vector2f playerPos;
	if (isDead) { return; }

	for (auto entity : colliders) {
		if (entity->getID() == 1) {
			playerPos.x = entity->getSprite().getPosition().x;
			playerPos.y = entity->getSprite().getPosition().y;
			if (!entity->getSprite().getGlobalBounds().intersects(m_detectionRange.getGlobalBounds())) {
				return;
			}
		}
	}

	attack(playerPos,colliders);
	checkAtk(colliders);
	changeDirection(playerPos.x);
	for (auto& projectile : projectiles) {
		projectile.update(deltaTime, colliders);
	}

	Entity::update(deltaTime, colliders);
	
	if (m_hp <= 0) {
		isDead = true;
	}
}

void Pungus::draw(RenderWindow& window) {
	if (!isDead) {
		window.draw(m_shape);

		for (auto& projectile : projectiles) {
			projectile.draw(window);
		}
	}
}

void Pungus::checkAtk(const vector<shared_ptr<Entity>>& colliders)
{
	for (auto& projectile : projectiles) {
		for (auto& entity : colliders) {
			if (entity->getID() == 1 && projectile.getID() == 50 && entity->getSprite().getGlobalBounds().intersects(projectile.getCircleShape().getGlobalBounds())) {
				projectile.setVelocity(-projectile.getVelocity());
				if (damageCD.getElapsedTime().asSeconds() >= 2.5) {
					damageCD.restart();
					m_hp--;
				}
			}
			else if (entity->getID() == 1 && projectile.getID() == 51 && entity->getSprite().getGlobalBounds().intersects(projectile.getCircleShape().getGlobalBounds())) {
				entity->takeDamage();
			}
		}
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

void Pungus::attack(Vector2f playerPos, const vector<shared_ptr<Entity>>& colliders) {
	if (attackCD.getElapsedTime().asSeconds() > 1.0f) {
		temp_rng = rng->getRandomNumber();
		attackCD.restart();

		Vector2f startPos = m_shape.getPosition();
		Vector2f targetPos = { playerPos.x, playerPos.y };
		float timeToReach = 2.5f;
		float gravity = 300.0f;

		Vector2f velocity = calculateProjectileVelocity(startPos, targetPos, timeToReach, gravity);

		if (temp_rng == 0) {
			projectiles.push_back(Projectile(startPos, velocity, true, false, true));
		}
		else {
			projectiles.push_back(Projectile(startPos, velocity, false, false, true));
		}
	}
}

Vector2f Pungus::calculateProjectileVelocity(Vector2f startPos, Vector2f targetPos, float timeToReach, float gravity) {
	Vector2f velocity;
	velocity.x = (targetPos.x - startPos.x) / timeToReach;
	velocity.y = (targetPos.y - startPos.y) / timeToReach - 0.5f * gravity * timeToReach;

	return velocity;
}
