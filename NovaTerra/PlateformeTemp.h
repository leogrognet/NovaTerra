#pragma once
#include "Entity.h"
#include <iostream>

using namespace std;
class Plateforme : public Entity {
public:

	Plateforme(float posX, float posY, Vector2f size,bool isStatic);

	void draw(RenderWindow& window) override;
	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	int getID() override;

private:

	Texture plateformetexture;
	Vector2f m_stockedPos;
};