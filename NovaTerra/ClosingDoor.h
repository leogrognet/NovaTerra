#pragma once
#include "Entity.h"

class Door : public Entity {
public:
	enum class State{CLOSING,IDLE};

	Door(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture);

	void draw(RenderWindow& window) override;
	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	void openDoor();
	void closeDoor(float deltaTime);

	bool collisionButton(const vector<shared_ptr<Entity>>& colliders);

private:
	RectangleShape m_buttonShape;
	State m_state;

	float m_doorSize = 0;
};