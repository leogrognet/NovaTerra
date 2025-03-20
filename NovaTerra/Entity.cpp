#include "Entity.h"

void Entity::update(float deltaTime, const vector<std::shared_ptr<Entity>>& colliders)
{

    vector<FloatRect> vec;
    for (auto& collider : colliders) {
        if (&collider->m_shape == &m_shape || !collider->getasCollision()) {
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

void Entity::interact(Cycle& cycle, Player& player) {}

void Entity::forceMove()
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

Vector2f Entity::getVelocity()
{
    return m_rigidBody.getVelocity();
}

void Entity::setVelocity(Vector2f velocity)
{
    m_rigidBody.getVelocity() = velocity;
}

Entity::Entity(float posX, float posY, bool isStatic, bool asCollision, vector<shared_ptr<Texture>>& texture) : m_rigidBody({ posX,posY }, isStatic, asCollision)
{
    m_asCollision = asCollision;
    textureList = texture;
    m_shape.setPosition(posX, posY);
}

void Entity::takeDamage(){}

bool Entity::isDead()
{
    return false;
}

bool Entity::getasCollision()
{
    return m_asCollision;
}

Sprite& Entity::getSprite()
{
    return m_shape;
}