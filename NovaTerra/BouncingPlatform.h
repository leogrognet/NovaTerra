#pragma once
#include "Entity.h"

class Bounce : public Entity {
public:

	Bounce(float posX, float posY, Vector2f size, bool isStatic);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	void draw(RenderWindow& window)override;

	void propulse(const vector<shared_ptr<Entity>>& colliders);

private:
};