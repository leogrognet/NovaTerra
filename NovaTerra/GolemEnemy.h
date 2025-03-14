#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "RigidBody.h"

using namespace sf; 
using namespace std;

class GolemEnemy {
public:
    enum class State { IDLE, JUMPING, COOLDOWN };

    GolemEnemy(Vector2f position);

    void update(float deltaTime, const Player& player);
    void draw(RenderWindow& window);

private:
    void updateFSM(const Player& player);
    void jumpToPlayer(const Player& player);
    bool raycastToPlayer(const Player& player);
    void landAndCooldown();

    RectangleShape m_golemShape;
    RigidBody m_golemBody;
    State m_golemState;

    Clock m_golemCooldownClock;
    float m_golemJumpForce = -800.f;
    float m_golemJumpSpeedX = 300.f;
    float m_golemDetectionRange = 500.f;
};
