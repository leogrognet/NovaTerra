#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class RigidBody {
private:
    Vector2f m_position;
    Vector2f m_velocity;
    bool m_isGrounded;
public:

    //Getters

    Vector2f getPosition();
    Vector2f& getVelocity();
    
    bool getIsGrounded();


    void setIsGrounded(bool isGrounded);

    RigidBody(Vector2f pos);
    void groundCollision(const std::vector<RectangleShape>& colliders, const FloatRect& selfShape);
    void update(float deltaTime);
};


