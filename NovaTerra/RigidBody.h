#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class RigidBody {
private:
    Vector2f m_position;
    Vector2f m_velocity;
    bool m_isGrounded;
public:

    //Getters

    Vector2f getPosition() const;
    Vector2f& getVelocity();
    
    bool getIsGrounded();


    RigidBody(Vector2f pos);
    void groundCollision(const vector<RectangleShape>& colliders, const FloatRect& selfShape);
    void update(float deltaTime);
};


