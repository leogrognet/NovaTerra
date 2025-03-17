#include "Plateform.h"

Plateforme::Plateforme(float posX, float posY, Vector2f size, bool isStatic, bool asCollision):Entity(posX,posY,isStatic,asCollision)
{
	plateformetexture.loadFromFile("../assets/tiles1.png");
	IntRect rect(128, 384, 128, 128);

	m_shape.setTexture(plateformetexture);
	m_shape.setTextureRect(rect);
	m_shape.setScale(1,1);
}

void Plateforme::draw(RenderWindow& window) {
	window.draw(m_shape);
}

void Plateforme::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
	Entity::update(deltaTime, colliders);
}

int Plateforme::getID()
{
	return 0;
}
