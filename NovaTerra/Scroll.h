#ifndef SCROLL_H
#define SCROLL_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Scroll {
private:
	sf::View view;
public:
	Scroll(float width, float height);
	~Scroll();
	void applyView(sf::RenderWindow& window);
	void update(float deltatime);
	void move(float offsetX, float offsetY);
};

#endif