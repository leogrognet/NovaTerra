#include "RigidBody.h"
#include <iostream>
#include <algorithm>




void RigidBody::setIsGrounded(bool isGrounded)
{
    m_isGrounded = isGrounded;
}

RigidBody::RigidBody(Vector2f pos) : m_position(pos), m_isGrounded(false) {
    m_velocity = { 0, 0 };
}

void RigidBody::groundCollision(const std::vector<RectangleShape>& colliders, const FloatRect& selfShape) {
    m_isGrounded = false;

    for (const auto& collider : colliders) {
        FloatRect colliderBounds = collider.getGlobalBounds();

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

void RigidBody::update(float deltaTime) {
    if (!m_isGrounded) {
        m_velocity.y += 981.0f * deltaTime; // Gravit� (981 pixels/sec�)
    }

    m_position += m_velocity * deltaTime;
}


Vector2f RigidBody::getPosition()
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