#include "Entity.h"

void Entity::update(float deltaTime, const std::vector<shared_ptr<Entity>>& colliders)
{

    vector<FloatRect> vec;
    for (auto& collider : colliders) {
        if (&collider->m_shape == &m_shape) {
            continue;
        }
        vec.push_back(collider->m_shape.getGlobalBounds());
    }
    m_rigidBody.update(deltaTime, vec, m_shape.getGlobalBounds());
}

void Entity::draw(RenderWindow& window)
{
    window.draw(m_shape);
}

Entity::Entity(float posX, float posY) : m_rigidBody({posX,posY})
{
    m_shape.setPosition(posX, posY);
}

Sprite& Entity::getSprite()
{
    return m_shape;
}