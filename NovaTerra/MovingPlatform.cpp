#include "MovingPlatform.h"

MovePlat::MovePlat(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture) :Entity(posX, posY, isStatic, asCollision, texture)
{
	if (!textureList.empty()) {

		m_shape.setTexture(*textureList.at(0).get());
		IntRect m_textureRect(384, 384, 128, 128);

		m_shape.setTextureRect(m_textureRect);
		m_shape.setScale(1.f, 1.f);
		m_shape.setPosition(posX, posY);
	}

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

