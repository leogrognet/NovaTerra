#include "Plateform.h"

Plateform::Plateform(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, shared_ptr<Texture>& texture) :Entity(posX, posY, isStatic, asCollision)
{
	m_shape.setTexture(*texture);
	m_shape.setScale(size);
	m_shape.setPosition(posX, posY);
}

void Plateform::draw(RenderWindow& window) {
	window.draw(m_shape);
}

void Plateform::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
    Entity::update(deltaTime, colliders);
}

int Plateform::getID()
{
	return 3;
}
