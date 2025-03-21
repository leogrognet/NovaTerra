#include "Projectile.h"

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f startVelocity, bool useableAsCounterAttack, bool isStatic, bool asCollision)
	: position(startPos), m_velocity(startVelocity), useableAsCounterAttack(useableAsCounterAttack), Entity(startPos.x, startPos.y, isStatic, asCollision) {
	gravity = 300.0f;
	ball.setRadius(10.0f);
	if (useableAsCounterAttack) {
		ball.setFillColor(sf::Color::Magenta);
		id = 50;
	}
	else {
		ball.setFillColor(sf::Color::Green);
		id = 51;
	}
	ball.setPosition(position);
}

void Projectile::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
	m_velocity.y += gravity * deltaTime;
	position.x += m_velocity.x * deltaTime;
	position.y += m_velocity.y * deltaTime;
	ball.setPosition(position);

	Entity::update(deltaTime, colliders);
}

void Projectile::draw(sf::RenderWindow& window) {
	window.draw(ball);
}

int Projectile::getID()
{
	return id;
}

void Projectile::setVelocity(Vector2f velocity)
{
	m_velocity = velocity;
}

Vector2f Projectile::getVelocity()
{
	return m_velocity;
}

CircleShape& Projectile::getCircleShape()
{
	return ball;
}
