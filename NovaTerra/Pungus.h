#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "RigidBody.h"
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Random.h"
#include "Projectile.h"

enum class Direction { WEST, EAST };

class Pungus : public Entity {
private:
	int m_hp = 5;

	Random* rng;
	int temp_rng;
	vector<Projectile> projectiles;
	Direction direction;
	Texture pungusTexture;
	Clock attackCD;
	Clock poison;
	Clock damageCD;

	CircleShape m_detectionRange;

	bool isDead = false;

	void attack(Vector2f playerPos, const vector<shared_ptr<Entity>>& colliders);
	Vector2f calculateProjectileVelocity(Vector2f startPos, Vector2f targetPos, float timeToReach, float gravity);
public:
	Pungus(float posX, float posY, bool isStatic, bool asCollision);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	void changeDirection(int playerPosX);
	int getID() override;
	void draw(RenderWindow& window) override;
	void checkAtk(const vector<shared_ptr<Entity>>& colliders);

};
