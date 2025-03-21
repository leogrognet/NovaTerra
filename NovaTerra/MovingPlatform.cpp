#include "MovingPlatform.h"

MovePlat::MovePlat(float posX, float posY, Vector2f size, bool isStatic, bool asCollision) :Entity(posX, posY, isStatic, asCollision)
{
	m_shape.setPosition(posX, posY);
	m_shapeTexture.loadFromFile("../NovaTerra/assets/Image/Bounce and Move/PM.png");
	m_shape.setTexture(m_shapeTexture);

	float scaleFactorX = 128 / m_shape.getGlobalBounds().width / 2;
	float scaleFactorY = 128 / m_shape.getGlobalBounds().height /2;

	m_shape.setScale({ scaleFactorX,scaleFactorY });

	m_stockedPos = { m_shape.getPosition() };
}

void MovePlat::draw(RenderWindow& window)
{
	window.draw(m_shape);
}

void MovePlat::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
	Entity::update(deltaTime, colliders); 
	move(deltaTime,colliders);
}

void MovePlat::move(float deltatime, const vector<shared_ptr<Entity>>& colliders)
{
	if (!reverseMove) {
		m_rigidBody.getVelocity().x = 5000 * deltatime;
		for (auto entity : colliders) {
			if (entity->getID() == 1 && entity->getHitBox().getGlobalBounds().intersects(m_shape.getGlobalBounds())) {
				entity->setForcedVelocity({ 5000 * deltatime,0 });
			}
		}
		if (m_shape.getPosition().x >= m_stockedPos.x + 150) {
			reverseMove = true;
		}
	} else {
		m_rigidBody.getVelocity().x = -5000 * deltatime;
		for (auto entity : colliders) {
			if (entity->getID() == 1 && entity->getHitBox().getGlobalBounds().intersects(m_shape.getGlobalBounds())) {
				entity->setForcedVelocity({ -5000 * deltatime,0 });
			}
		}
		if (m_shape.getPosition().x <= m_stockedPos.x - 150) {
			reverseMove = false;
		}
	}
}

int MovePlat::getID()
{
	return 0;
}

