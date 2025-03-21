#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RigidBody.h"
#include "Cycle.h"
using namespace sf;
using namespace std;


enum entityType
{	
	NOTYPE  = 0,
	BIOME_1_PLAT = 1,
	BIOME_2_PLAT = 2,
	BIOME_3_PLAT = 3,
	PUNGUS = 4,
	CROC = 5,
	GOLEM = 6,
	GRIND_VINE = 7,
	FIRECAMP = 12,
	PLAYER = 8,
	MOVE_PLAT = 9,
	BOUNCE_PLAT = 10,
	DOOR = 50,
	FALLING_PLAT = 11,
};

class Player;

class Entity {
protected:

	Sprite m_shape;
	Texture m_shapeTexture;
	RigidBody m_rigidBody;
	RectangleShape m_hitbox;
	Vector2f m_forcedVelocity;
	vector<shared_ptr<Texture>> textureList;

	CircleShape projectile;

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
	virtual void interact(Cycle& cycle, Player& player);

	Entity(float posX, float posY, bool isStatic, bool asCollision);


	virtual void takeDamage();
	virtual bool isDead();

	virtual bool getasCollision();

	virtual CircleShape& getCircleShape();

	Sprite& getSprite();

};