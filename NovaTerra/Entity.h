#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RigidBody.h"
using namespace sf;
using namespace std;


class Entity {
protected:

	Sprite m_shape;
	Texture m_shapeTexture;
	RigidBody m_rigidBody;
	RectangleShape m_hitbox;
	Vector2f m_forcedVelocity;


public:
	virtual void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders);
	virtual void draw(RenderWindow& window);
	virtual int getID();
	virtual void ForceMove();

	virtual RectangleShape getHitBox();
	virtual void setForcedVelocity(Vector2f velocity);

	virtual Vector2f getVelocity();
	virtual void setVelocity(Vector2f velocity);

	Entity(float posX, float posY,bool isStatic);

	Sprite& getSprite();

};