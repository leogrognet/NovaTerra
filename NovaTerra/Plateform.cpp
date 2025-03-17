#include "Plateform.h"

Plateform::Plateform(float posX, float posY, Vector2f size, bool isStatic, bool asCollision, TextureLoader& textureLoader) :Entity(posX, posY, isStatic, asCollision)
{
    auto textureData = textureLoader.GetTexture(getID());

    if (textureData.first) {
        m_texture = textureData.first;
        m_textureRect = textureData.second;

        if (m_textureRect.width > 0 && m_textureRect.height > 0) {
            m_shape.setTexture(*m_texture);
            m_shape.setTextureRect(m_textureRect);
            m_shape.setScale(1.f, 1.f);
            m_shape.setPosition(posX, posY);
        }
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
