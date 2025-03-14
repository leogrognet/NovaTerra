#include "Pungus.h"

Pungus::Pungus(vector<shared_ptr<Entity>>& shape, sf::Vector2f pos, bool isStatic) : Entity(pos.x, pos.y , isStatic) {
	m_texture.loadFromFile("../assets/player.png");
	m_shape.setTexture(m_texture);
	m_shape.setScale({ 1.f,1.f });
	m_shape.setPosition(pos.x, pos.y);
}

void Pungus::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {

}

void Pungus::draw(sf::RenderWindow& window) {

}

void Pungus::attack() {

}
