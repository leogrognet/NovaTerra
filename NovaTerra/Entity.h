#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class Entity {
protected:

	Sprite sprite;

public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(RenderWindow& window) = 0;

	Entity(Texture& texture, float posX, float posY);

	Sprite& getSprite();

};
