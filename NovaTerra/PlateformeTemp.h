#pragma once
#include "Entity.h"

class Plateforme : public Entity {
public:

	Plateforme(float posX, float posY, Vector2f size,bool isStatic);

	void draw(RenderWindow& window) override;
	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;

private:

	Texture plateformetexture;

};