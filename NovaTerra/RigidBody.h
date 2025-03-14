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
    bool m_isStatic;
public:

    //Getters

    Vector2f getPosition() const;
    Vector2f& getVelocity();

    bool getIsGrounded();

    void setIsStatic(bool isStatic);

    RigidBody(Vector2f pos, bool isStatic);
    void colliderFunc(const vector<FloatRect>& colliders, const FloatRect& selfShape);
    void checkGrounded(const vector<FloatRect>& colliders, const FloatRect& selfShape);
    void update(float deltaTime, const vector<FloatRect>& colliders, const FloatRect& selfShape);
};
