#include "Firecamp.h"

Firecamp::Firecamp(float posX, float posY, bool isStatic, bool asCollision) : Entity(posX, posY, isStatic, asCollision, textureList) {
	firecampTexture.loadFromFile("../assets/firecamp.png");
	m_shape.setTexture(firecampTexture);
	m_shape.setPosition(posX, posY);
	m_shape.setScale(0.5f, 0.5f);
	detectionRange.setRadius(200);
	detectionRange.setFillColor(sf::Color(255, 0, 0, 128));
	detectionRange.setPosition(posX-125, posY-100);
}

void Firecamp::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
	//if (Keyboard::isKeyPressed(Keyboard::O)) {
	//	std::cout << "Test\n";
	//}
	Entity::update(deltaTime, colliders);
}

void Firecamp::interact(Cycle& cycle, Player& player) {
	if (CD.getElapsedTime().asSeconds() > 1.0f && player.getSprite().getGlobalBounds().intersects(detectionRange.getGlobalBounds())) {
		cycle.changeState();
		CD.restart();
	}
}

void Firecamp::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
	window.draw(detectionRange);
}