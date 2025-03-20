#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

class KillerEnemy : public Entity {
public:
    enum class State { IDLE, DASHING, COOLDOWN };

    KillerEnemy(float posX, float posY, bool isStatic, bool hasCollision);

    void update(float deltaTime, const vector<shared_ptr<Entity>>& player)override;
    void draw(RenderWindow& window) override;
    int getID()override;


private:

    void updateFSM(const vector<shared_ptr<Entity>>& plqyer);
    void dashToPlayer(const shared_ptr<Entity>& player);
    void stopAndCooldown(float deltaTime);


	State m_KillerState;

    Vector2f velocity;
	Vector2f position;
    Vector2f dashDirection;

    Texture killerTexture; 

    float m_KillerDashSpeed = 2000.f;
    float m_KillerDetectionRange = 250.f;
    float m_KillerDashCooldown = 1.0f;
	Clock m_KillerCooldownClock;


};