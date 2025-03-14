#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "RigidBody.h"

using namespace sf; 
using namespace std;

class GolemEnemy : public Entity {
public:
    enum class State { IDLE, JUMPING, COOLDOWN };

    GolemEnemy(Vector2f position, float posX, float posY, bool isStatic);

    void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)override;
    void draw(RenderWindow& window) override;

private:

    void updateFSM(const Player& player);
    void jumpToPlayer(const Player& player);
    void landAndCooldown();

    RectangleShape m_golemShape;
    RigidBody m_golemBody;
    State m_golemState;

    Texture golemTexture;

    Clock m_golemCooldownClock;
    float m_golemJumpForce = -600.f;
    float m_golemJumpSpeedX = 300.f;
    float m_golemDetectionRange = 500.f;
};
