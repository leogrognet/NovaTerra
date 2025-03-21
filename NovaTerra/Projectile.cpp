#include "Projectile.h"

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f startVelocity, bool useableAsCounterAttack, bool isStatic, bool asCollision)
	: position(startPos), velocity(startVelocity), useableAsCounterAttack(useableAsCounterAttack), Entity(startPos.x, startPos.y, isStatic, asCollision) {
	gravity = 300.0f;
	ball.setRadius(10.0f);
	if (useableAsCounterAttack) {
		ball.setFillColor(sf::Color::Magenta);
	}
	else {
		ball.setFillColor(sf::Color::Green);
	}
	ball.setPosition(position);
}

void Projectile::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
	velocity.y += gravity * deltaTime;
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	ball.setPosition(position);

	Entity::update(deltaTime, colliders);
}

void Projectile::draw(sf::RenderWindow& window) {
	window.draw(ball);
}
