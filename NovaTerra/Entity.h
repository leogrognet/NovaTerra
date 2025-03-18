#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RigidBody.h"
using namespace sf;
using namespace std;


enum entityType
{
	GOLEM,
	PLAYER,
	TILE,
	NOTYPE,
};

//enum Tiles {
//    NO_TYPE = 0,
//    GRASS_1_1 = 11,
//    GRASS_1_2 = 12,
//    GRASS_1_3 = 13,
//
//    GRASS_2_1 = 21,
//    GRASS_2_2 = 22,
//    GRASS_2_3 = 23,
//
//    GRASS_3_1 = 31,
//    GRASS_3_2 = 32,
//    GRASS_3_3 = 33,
//
//    GRASS_4_1 = 41,
//    GRASS_4_2 = 42,
//    GRASS_4_3 = 43,
//    GRASS_4_4 = 44,
//
//    GRASS_5_1 = 51,
//    GRASS_5_2 = 52,
//    GRASS_5_3 = 53,
//    GRASS_5_4 = 54,
//    GRASS_5_5 = 55,
//    GRASS_5_6 = 56,
//    GRASS_5_7 = 57,
//
//    GRASS_6_1 = 61,
//    GRASS_6_2 = 62,
//    GRASS_6_3 = 63,
//    GRASS_6_4 = 64,
//    GRASS_6_5 = 65,
//    GRASS_6_6 = 66,
//    GRASS_6_7 = 67,
//
//    GRASS_7_1 = 71,
//    GRASS_7_2 = 72,
//    GRASS_7_3 = 73,
//    GRASS_7_4 = 74,
//    GRASS_7_5 = 75,
//    GRASS_7_6 = 76,
//    GRASS_7_7 = 77
//};



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

	Entity(float posX, float posY, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture);

	virtual void takeDamage();
	virtual bool isDead();

	virtual bool getasCollision();

	Sprite& getSprite();

};