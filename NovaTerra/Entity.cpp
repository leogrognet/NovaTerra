#include "Entity.h"

void Entity::update(float deltaTime, const vector<std::shared_ptr<Entity>>& colliders)
{

    vector<FloatRect> vec;
    for (auto& collider : colliders) {
        if (&collider->m_shape == &m_shape) {
            continue;
        }
        vec.push_back(collider->m_shape.getGlobalBounds());
    }

    m_shape.setPosition(m_rigidBody.getPosition());
    m_rigidBody.update(deltaTime, vec, m_shape.getGlobalBounds());
    m_forcedVelocity = { 0,0 };
}


void Entity::draw(RenderWindow& window)
{
    window.draw(m_shape);
}

int Entity::getID()
{
    return 0;
}

void Entity::ForceMove()
{
}

RectangleShape Entity::getHitBox()
{
    return m_hitbox;
}

void Entity::setForcedVelocity(Vector2f velocity)
{
    m_forcedVelocity.x = velocity.x * 2;
    m_forcedVelocity.y = velocity.y * 2;
}

Entity::Entity(float posX, float posY, bool isStatic) : m_rigidBody({ posX,posY }, isStatic)
{
    m_shape.setPosition(posX, posY);
}

Sprite& Entity::getSprite()
{
    return m_shape;
}