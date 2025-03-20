#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;
class MovePlat : public Entity {
public:

	MovePlat(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture);

	void draw(RenderWindow& window) override;
	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;

	void move(float deltatime, const vector<shared_ptr<Entity>>& colliders);
	int getID() override;
private:

	bool reverseMove = false;
	Texture plateformetexture;
	Vector2f m_stockedPos;
};