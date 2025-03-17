#include "KillerEnemy.h"

KillerEnemy::KillerEnemy(float posX, float posY, bool isStatic, bool hasCollision) : Entity(posX, posY, isStatic, hasCollision), m_KillerState(State::IDLE) {
    shape.setSize(Vector2f(50.f, 50.f)); 
    shape.setPosition(posX, posY);       
    shape.setFillColor(Color::Green);       

}

void KillerEnemy::update(float deltaTime, const std::vector<Entity*>& colliders, const Player& player) {
    if (m_KillerState == State::COOLDOWN) {
        handleCooldown(deltaTime);
    }

    // Try to dash if the player is within range and cooldown is finished
    if (m_KillerState == State::IDLE) {
        tryDash(player);
    }

    // Perform dash motion if in DASHING state
    if (m_KillerState == State::DASHING) {
        performDash(deltaTime);
    }
}

void KillerEnemy::draw(RenderWindow& window) {
    window.draw(shape);
}

int KillerEnemy::getID() {
    return 3; 
}

void KillerEnemy::tryDash(const Player& player) {
    if (distanceToPlayer(player) <= detectionRange && cooldownTimer <= 0.f) {
        m_KillerState = State::DASHING;
        dashDirection = player.getPosition() - shape.getPosition();  
        float length = sqrt(dashDirection.x * dashDirection.x + dashDirection.y * dashDirection.y);
        dashDirection /= length; 
    }
}

void KillerEnemy::performDash(float deltaTime) {
    shape.move(dashDirection * dashSpeed * deltaTime);

    m_KillerState = State::COOLDOWN;
    cooldownTimer = dashCooldown;
}

void KillerEnemy::handleCooldown(float deltaTime) {
    cooldownTimer -= deltaTime;
    if (cooldownTimer <= 0.f) {
        m_KillerState = State::IDLE;  
    }
}

float KillerEnemy::distanceToPlayer(const Player& player) {
    Vector2f playerPos = player.getPosition();
    Vector2f enemyPos = shape.getPosition();
    float dx = playerPos.x - enemyPos.x;
    float dy = playerPos.y - enemyPos.y;
    return sqrt(dx * dx + dy * dy);
}
