#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class RigidBody {
private:
    Vector2f m_position;
    Vector2f m_velocity;
    bool m_isGrounded;
    bool m_isStatic;
public:

    //Getters

    Vector2f getPosition();
    Vector2f& getVelocity();

    bool getIsGrounded();

    void setIsStatic(bool isStatic);

    RigidBody(Vector2f pos, bool isStatic);
    void colliderFunc(const std::vector<FloatRect>& colliders, const FloatRect& selfShape);
    void checkGrounded(const std::vector<FloatRect>& colliders, const FloatRect& selfShape);
    void update(float deltaTime, const std::vector<FloatRect>& colliders, const FloatRect& selfShape);
};
