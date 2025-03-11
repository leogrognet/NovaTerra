#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class RigidBody {
public:
    Vector2f position;
    Vector2f velocity;
    bool isGrounded;

    RigidBody(Vector2f pos);
    void groundCollision(const std::vector<RectangleShape>& colliders, const FloatRect& selfShape);
    void update(float deltaTime);
};

#endif
