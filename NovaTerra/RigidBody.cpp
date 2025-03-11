#include "RigidBody.h"
#include <iostream>
#include <algorithm>

RigidBody::RigidBody(Vector2f pos) : position(pos), isGrounded(false) {
    velocity = { 0, 0 };
}

void RigidBody::groundCollision(const std::vector<RectangleShape>& colliders, const FloatRect& selfShape) {
    isGrounded = false;

    for (const auto& collider : colliders) {
        FloatRect colliderBounds = collider.getGlobalBounds();

        if (colliderBounds.intersects(selfShape)) {
            float overlapX = std::min(selfShape.left + selfShape.width, colliderBounds.left + colliderBounds.width) -
                std::max(selfShape.left, colliderBounds.left);
            float overlapY = std::min(selfShape.top + selfShape.height, colliderBounds.top + colliderBounds.height) -
                std::max(selfShape.top, colliderBounds.top);

            if (overlapX < overlapY) {
                if (selfShape.left < colliderBounds.left) {
                    position.x = colliderBounds.left - selfShape.width;
                }
                else {
                    position.x = colliderBounds.left + colliderBounds.width;
                }
                velocity.x = 0;
            }
            else {
                if (selfShape.top < colliderBounds.top) {
                    position.y = colliderBounds.top - selfShape.height;
                    isGrounded = true;
                }
                else {
                    position.y = colliderBounds.top + colliderBounds.height;
                }
                velocity.y = 0;
            }
        }
    }
}

void RigidBody::update(float deltaTime) {
    if (!isGrounded) {
        velocity.y += 981.0f * deltaTime; // Gravité (981 pixels/sec²)
    }

    position += velocity * deltaTime;
}
