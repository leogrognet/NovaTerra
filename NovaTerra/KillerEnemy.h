#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "RigidBody.h"

using namespace sf;
using namespace std;

class KillerEnemy : public Entity {
public:
    enum class State { IDLE, DASHING, COOLDOWN };

    KillerEnemy(float posX, float posY, bool isStatic, bool hasCollision);

    void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders)override;
    void draw(RenderWindow& window) override;
    int getID()override;


private:

    void updateFSM(const vector<shared_ptr<Entity>>& colliders);
    void dashToPlayer(const vector<shared_ptr<Entity>>& colliders);
	void stopAndCooldown();

    RectangleShape m_shape;
	State m_KillerState;

    Vector2f velocity;
    Vector2f dashDirection;

    Texture killerTexture;

    float m_KillerDashSpeed = 500.f;
    float m_KillerDetectionRange = 250.f;
    float m_KillerKashCooldown = 1.0f;
    float m_KillerCooldownClock = 0.f;

    RigidBody m_rigidBody; 

};