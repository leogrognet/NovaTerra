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

    GolemEnemy(float posX, float posY, bool isStatic, bool asCollision);

    void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)override;
    void draw(RenderWindow& window) override;
    int getID()override;

private:

    void updateFSM(const vector<shared_ptr<Entity>>& colliders);
    void jumpToPlayer(const vector<shared_ptr<Entity>>& colliders);
    void landAndCooldown();

    RectangleShape m_golemShape;
    State m_golemState;

    Texture golemTexture;

    Clock m_golemCooldownClock;
    float m_golemJumpForce = -600.f;
    float m_golemJumpSpeedX = 300.f;
    float m_golemDetectionRange = 500.f;
};
