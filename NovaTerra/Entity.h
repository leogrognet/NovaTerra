#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RigidBody.h"
using namespace sf;
using namespace std;


enum entityType
{	
	NOTYPE,
	BIOME_1_PLAT,
	BIOME_2_PLAT,
	BIOME_3_PLAT,
	GOLEM,
	PLAYER,
	CROC,
	MOVE_PLAT,
	BOUNCE_PLAT,
	GRIND_VINE,
	DOOR,
	
};


class Entity {
protected:

	Sprite m_shape;
	Texture m_shapeTexture;
	RigidBody m_rigidBody;
	RectangleShape m_hitbox;
	Vector2f m_forcedVelocity;
	vector<shared_ptr<Texture>> textureList;

	bool m_asCollision;


public:

	virtual void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders);
	virtual void draw(RenderWindow& window);
	virtual int getID();
	virtual void forceMove();

	virtual RectangleShape getHitBox();
	virtual void setForcedVelocity(Vector2f velocity);

	virtual Vector2f getVelocity();
	virtual void setVelocity(Vector2f velocity);

	Entity(float posX, float posY, bool isStatic, bool asCollision);


	virtual void takeDamage();
	virtual bool isDead();

	virtual bool getasCollision();

	Sprite& getSprite();

};