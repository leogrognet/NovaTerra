#include "Entity.h"

void Entity::update(float deltaTime, const std::vector<std::shared_ptr<Entity>>& colliders)
{
    std::vector<FloatRect> vec;
    for (auto& collider : colliders) {
        if (&collider->m_shape == &m_shape) {
            continue;
        }
        vec.push_back(collider->m_shape.getGlobalBounds());
    }

    m_rigidBody.update(deltaTime, vec, m_shape.getGlobalBounds());

    m_shape.setPosition(m_rigidBody.getPosition());
}


void Entity::draw(RenderWindow& window)
{
    window.draw(m_shape);
}

Entity::Entity(float posX, float posY, bool isStatic) : m_rigidBody({ posX,posY }, isStatic)
{
    m_shape.setPosition(posX, posY);
}

Sprite& Entity::getSprite()
{
    return m_shape;
}