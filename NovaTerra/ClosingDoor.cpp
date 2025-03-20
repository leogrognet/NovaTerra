#include "ClosingDoor.h"

Door::Door(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture) :Entity(posX, posY, isStatic, asCollision), m_state(State::IDLE)
{
	if (!textureList.empty()) {

		m_shape.setTexture(*textureList.at(0).get());
		IntRect m_textureRect(128, 384, 128, 128);

		m_shape.setTextureRect(m_textureRect);
		m_shape.setScale(1.f, 1.f);
		m_shape.setPosition(posX, posY);
	}

	m_buttonShape.setFillColor(Color::Red);
	m_buttonShape.setSize({ 400,100 });
	m_buttonShape.setPosition(600, 600);
}

void Door::draw(RenderWindow& window)
{
	window.draw(m_shape);
	window.draw(m_buttonShape);
}

void Door::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
	if (m_state == State::CLOSING) {
		closeDoor(deltaTime);
	}
	collisionButton(colliders);
	Entity::update(deltaTime, colliders);
}

void Door::openDoor()
{
	m_shape.setScale(1.f, m_doorSize);
}

void Door::closeDoor(float deltaTime)
{
	if (m_shape.getGlobalBounds().height <= 128) {
		m_doorSize += deltaTime * 0.01f;
		m_shape.setScale(1.f, m_doorSize);
	}
	else {
		m_state = State::IDLE;
	}
}

bool Door::collisionButton(const vector<shared_ptr<Entity>>& colliders)
{
	for (auto& entity : colliders) {
		if (entity->getID() == 1
			&& entity->getSprite().getGlobalBounds().intersects(m_buttonShape.getGlobalBounds())
			&& (Keyboard::isKeyPressed(Keyboard::E) || (Joystick::isConnected(0) && Joystick::isButtonPressed(0, 2)))) { // Bouton X = ID 2

			openDoor();
			m_state = State::CLOSING;
			m_doorSize = 0;
			return true;
		}
	}
	return false;

}
