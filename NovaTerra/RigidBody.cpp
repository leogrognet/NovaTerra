#include "RigidBody.h"
#include <cmath>
#include <iostream>

void RigidBody::applyForce(Vector2f force) {
    acceleration += force / mass;
}

void RigidBody::update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    acceleration = Vector2f(0, 0); // Reset acceleration after applying it
}

void RigidBody::groundCollision(std::vector<RectangleShape>& colliders, const FloatRect& selfShape) {
    isGrounded = false;

    for (auto& collider : colliders) {
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
                velocity.x = 0; // Stopper le mouvement horizontal
            }
            else {
                // Collision verticale
                if (selfShape.top < colliderBounds.top) {
                    position.y = colliderBounds.top - selfShape.height;
                    isGrounded = true;
                }
                else {
                    position.y = colliderBounds.top + colliderBounds.height;
                }
                velocity.y = 0; // Stopper le mouvement vertical
            }
        }
    }
}
