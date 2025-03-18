#include "Plateform.h"

Plateform::Plateform(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture) :Entity(posX, posY, isStatic, asCollision, texture)
{

    if (!textureList.empty()) {
        m_shape.setTexture(*textureList.at(0).get());
       // m_shape.setTextureRect(m_textureRect);
        m_shape.setScale(1.f, 1.f);
        m_shape.setPosition(posX, posY);
    }
    
}

void Plateform::draw(RenderWindow& window) {
	window.draw(m_shape);
}

void Plateform::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)
{
    Entity::update(deltaTime, colliders);

}

int Plateform::getID()
{
	return 3;
}
