#pragma once
#include "Entity.h"
#include "Player.h"

class Vine : public Entity {
public:
	Vine(float posX, float posY, float width, float height, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)override;
	void draw(RenderWindow& window)override;
	int getID()override;

};