#include "Scroll.h"

Scroll::Scroll(float width, float height) : view(sf::FloatRect(0, 0, width, height)) {
	view.setCenter(width / 2, height / 2);
}

Scroll::~Scroll() {
	std::cout << "Le défilement est détruit";
}

void Scroll::applyView(sf::RenderWindow& window) {
	window.setView(view);
}

void Scroll::update(float deltatime) {

}

void Scroll::move(float offsetX, float offsetY) {
	view.move(offsetX, offsetY);
	
}