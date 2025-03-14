#include "RigidBody.h"
#include <iostream>
#include <algorithm>



RigidBody::RigidBody(Vector2f pos, bool isStatic) : m_position(pos), m_isGrounded(false), m_isStatic(isStatic) {
    m_velocity = { 0, 0 };
}

void RigidBody::colliderFunc(const std::vector<FloatRect>& colliders, const FloatRect& selfShape) {
    int tempPos = 0;
    for (const auto& colliderBounds : colliders) {
        tempPos += 1;
        if (colliderBounds.intersects(selfShape)) {
            float overlapX = std::min(selfShape.left + selfShape.width, colliderBounds.left + colliderBounds.width) -
                std::max(selfShape.left, colliderBounds.left);
            float overlapY = std::min(selfShape.top + selfShape.height, colliderBounds.top + colliderBounds.height) -
                std::max(selfShape.top, colliderBounds.top);

            if (overlapX < overlapY) {
                if (selfShape.left < colliderBounds.left) {
                    m_position.x = colliderBounds.left - selfShape.width;
                }
                else {
                    m_position.x = colliderBounds.left + colliderBounds.width;
                }
                m_velocity.x = 0;
            }
            else {
                if (selfShape.top < colliderBounds.top) {
                    m_position.y = colliderBounds.top - selfShape.height;
                    m_isGrounded = true;
                }
                else {
                    m_position.y = colliderBounds.top + colliderBounds.height;
                }
                m_velocity.y = 0;
            }
        }
    }
}

void RigidBody::checkGrounded(const std::vector<FloatRect>& colliders, const FloatRect& selfShape) {
    m_isGrounded = false;

    for (const auto& collider : colliders) {

        if (selfShape.top + selfShape.height == collider.top &&
            selfShape.left + selfShape.width > collider.left &&
            selfShape.left < collider.left + collider.width)
        {
            m_isGrounded = true;
            return;
        }
    }
}

void RigidBody::update(float deltaTime, const vector<FloatRect>& colliders, const FloatRect& selfShape) {
    checkGrounded(colliders, selfShape);
    
    if (!m_isGrounded && !m_isStatic) {
        m_velocity.y += 981.0f * deltaTime / 2;
        if (m_velocity.y > 2500.f) {
            m_velocity.y = 2500.f;
        }
    }

    if (!m_isStatic) {
        colliderFunc(colliders, selfShape);
    }

    m_position += m_velocity * deltaTime;

}

Vector2f RigidBody::getPosition() const
{
    return m_position;
}

Vector2f& RigidBody::getVelocity()
{
    return m_velocity;
}

bool RigidBody::getIsGrounded()
{
    return m_isGrounded;
}

void RigidBody::setIsStatic(bool isStatic)
{
    m_isStatic = isStatic;
}