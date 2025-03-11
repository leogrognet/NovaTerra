#include "RigidBody.h"
#include <cmath>
#include <iostream>

void RigidBody::groundCollision(vector<RectangleShape>& colliders, const FloatRect& selfShape) {
    isGrounded = false;

    for (auto& collider : colliders) {
        FloatRect colliderBounds = collider.getGlobalBounds();

        if (colliderBounds.intersects(selfShape)) {
            float overlapX = min(selfShape.left + selfShape.width, colliderBounds.left + colliderBounds.width) -
                max(selfShape.left, colliderBounds.left);
            float overlapY = min(selfShape.top + selfShape.height, colliderBounds.top + colliderBounds.height) -
                max(selfShape.top, colliderBounds.top);

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

RigidBody::RigidBody(Vector2f pos) : isGrounded(false)
{
    velocity = { 0,0 };
    pos = position;
}
