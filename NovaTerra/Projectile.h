#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity {
private:
	Vector2f position;
	Vector2f m_velocity;
	CircleShape ball;
	bool useableAsCounterAttack;
	float gravity = 300.0f;

	int id;
public:
	Projectile(Vector2f startPos, Vector2f startVelocity, bool useableAsCounterAttack, bool isStatic, bool asCollision);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;

	void draw(RenderWindow& window) override;
	int getID()override;
	void setVelocity(Vector2f velocity) override;
	Vector2f getVelocity()override;

	CircleShape& getCircleShape()override;

};
#pragma once
