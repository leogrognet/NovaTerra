#pragma once
#include "Entity.h"
#include <iostream>
#include "TextureLoader.h"

using namespace std;
class Plateform : public Entity {
public:

	Plateform(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, TextureLoader& textureLoader);

	void draw(RenderWindow& window) override;
	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	int getID() override;

private:
	shared_ptr<Texture> m_texture;  // Pointeur partagé vers la texture
	IntRect m_textureRect;         // Section de la texture
	Sprite m_shape;

};