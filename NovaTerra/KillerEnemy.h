#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "RigidBody.h"

using namespace sf;

class KillerEnemy : public Entity {
public:
    enum class State { IDLE, DASHING, COOLDOWN };

    KillerEnemy(float posX, float posY, bool isStatic, bool hasCollision);

    void update(float deltaTime, const std::vector<Entity*>& colliders, const Player& player);
    void draw(RenderWindow& window) override;
    int getID() override;

private:
    RectangleShape shape;
    Vector2f velocity;
    Vector2f dashDirection;

    State m_KillerState;

    float dashSpeed = 500.f;
    float detectionRange = 250.f;
    float dashCooldown = 1.0f;
    float cooldownTimer = 0.f;

    void tryDash(const Player& player);
    void performDash(float deltaTime);
    void handleCooldown(float deltaTime);
    float distanceToPlayer(const Player& player);
};
