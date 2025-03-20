#include "MovingPlatform.h"

MovePlat::MovePlat(float posX, float posY, Vector2f size, bool isStatic, bool asCollision) :Entity(posX, posY, isStatic, asCollision)
{
	m_shapeTexture.loadFromFile("../assets/Deepslate.png");
	m_shape.setScale(size);
	m_shape.setPosition(posX, posY);

	m_stockedPos = { m_shape.getPosition() };
}

void MovePlat::draw(RenderWindow& window)
{
	window.draw(m_shape);
}

void MovePlat::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
	cout << m_shape.getPosition().x << " " << m_shape.getPosition().y << endl;
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
		if (m_shape.getPosition().x >= m_stockedPos.x + 300) {
			m_stockedPos = { m_shape.getPosition() };
			reverseMove = true;
		}
	} else {
		m_rigidBody.getVelocity().x = -5000 * deltatime;
		for (auto entity : colliders) {
			if (entity->getID() == 1 && entity->getHitBox().getGlobalBounds().intersects(m_shape.getGlobalBounds())) {
				entity->setForcedVelocity({ -5000 * deltatime,0 });
			}
		}
		if (m_shape.getPosition().x <= m_stockedPos.x - 300) {
			m_stockedPos = { m_shape.getPosition() };
			reverseMove = false;
		}
	}
}

int MovePlat::getID()
{
	return 0;
}

