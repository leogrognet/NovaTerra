#include "Plateform.h"

Plateform::Plateform(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, shared_ptr<Texture>& texture) :Entity(posX, posY, isStatic, asCollision)
{
	m_shape.setTexture(*texture);
	m_shape.setPosition(posX, posY);
	float scaleFactorX = 32 / m_shape.getGlobalBounds().width ;
	float scaleFactorY = 32 / m_shape.getGlobalBounds().height ;
	m_shape.setScale({ scaleFactorX,scaleFactorY });

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
