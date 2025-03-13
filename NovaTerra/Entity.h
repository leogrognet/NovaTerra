#pragma once
#include <SFML/Graphics.hpp>
#include "RigidBody.h"
using namespace sf;
using namespace std;


class Entity {
protected:

	Sprite m_shape;
	RigidBody m_rigidBody;


public:
	virtual void update(float deltaTime, const std::vector<Entity*>& colliders);
	virtual void draw(RenderWindow& window) ;

	Entity(float posX, float posY);

	Sprite& getSprite();

};