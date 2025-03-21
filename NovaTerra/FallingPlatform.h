#pragma once

#include "Entity.h"

class FallingPlat : public Entity {
public:

	enum class State{IDLE,FALLING};

	FallingPlat(float posX, float posY, Vector2f size, bool isStatic, bool asCollision);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)override;
	void draw(RenderWindow& window)override;
	void fall();

private:
	State m_state;
};
