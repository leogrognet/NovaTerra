#include "FallingPlatform.h"

FallingPlat::FallingPlat(float posX, float posY, Vector2f size, bool isStatic, bool asCollision) :Entity(posX, posY, isStatic, asCollision), m_state(State::IDLE)
{
	m_shape.setPosition(posX, posY);
	m_shapeTexture.loadFromFile("../NovaTerra/assets/map/map_tileset/PT.png");
	m_shape.setTexture(m_shapeTexture);

	m_shape.setScale(size);
}

void FallingPlat::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
	Entity::update(deltaTime, colliders);

	for (auto& entity : colliders) {
		if (entity->getID() == 1 && entity->getHitBox().getGlobalBounds().intersects(m_shape.getGlobalBounds())) {
			m_state = State::FALLING;
		}
	}

	if (m_state == State::FALLING) {
		fall();
	}
}

void FallingPlat::draw(RenderWindow& window)
{
	window.draw(m_shape);
}

void FallingPlat::fall()
{
	m_rigidBody.getVelocity().y = 150;
}
