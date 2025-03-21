#pragma once
#include "Entity.h"
#include <iostream>
#include "TextureLoader.h"

using namespace std;
class Plateform : public Entity {
public:




	Plateform(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, shared_ptr<Texture>& texture);

	void draw(RenderWindow& window) override;
	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	int getID() override;

private:
};