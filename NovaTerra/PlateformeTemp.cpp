#include "PlateformeTemp.h"

Plateforme::Plateforme(float posX, float posY, Vector2f size, bool isStatic):Entity(posX,posY,isStatic)
{
	plateformetexture.loadFromFile("../assets/deepslate.png");
	m_shape.setTexture(plateformetexture);
	m_shape.setScale(size);
}

void Plateforme::draw(RenderWindow& window) {
	window.draw(m_shape);
}

void Plateforme::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{

	//cout << m_rigidBody.getVelocity().x << " " << m_rigidBody.getVelocity().y << endl;
	//m_rigidBody.getVelocity().x += deltaTime * 50;
	Entity::update(deltaTime, colliders);

}
