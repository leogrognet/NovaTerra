#include "GolemEnemy.h"

GolemEnemy::GolemEnemy(Vector2f position) : m_golemState(State::IDLE), m_golemBody(position) {
    m_golemShape.setSize({ 40.f, 60.f });
    m_golemShape.setFillColor(Color::Yellow);
    m_golemShape.setPosition(position);
}

void GolemEnemy::update(float deltaTime, const Player& player) {
    updateFSM(player);
    m_golemBody.update(deltaTime);
    m_golemShape.setPosition(m_golemBody.getPosition());
}

void GolemEnemy::draw(RenderWindow& window) {
    window.draw(m_golemShape);
}

void GolemEnemy::updateFSM(const Player& player) {
    switch (m_golemState) {
    case State::IDLE:
        if (raycastToPlayer(player)) {
            jumpToPlayer(player);
            m_golemState = State::JUMPING;
        }
        break;

    case State::JUMPING:
        if (m_golemBody.getIsGrounded()) {
            landAndCooldown();
        }
        break;

    case State::COOLDOWN:
        if (m_golemCooldownClock.getElapsedTime().asSeconds() >= 3.f) {
            m_golemState = State::IDLE;
        }
        break;
    }
}

bool GolemEnemy::raycastToPlayer(const Player& player) {
    Vector2f playerPos = player.body.getPosition();
    Vector2f golemPos = m_golemBody.getPosition();
    float distance = (playerPos.x - golemPos.x);

    // Simple horizontal raycast logic
    return distance <= m_golemDetectionRange && (playerPos.y - golemPos.y) < 100;
}

void GolemEnemy::jumpToPlayer(const Player& player) {
    Vector2f dir = player.body.getPosition() - m_golemBody.getPosition();
    m_golemBody.getVelocity().y = m_golemJumpForce;
    m_golemBody.getVelocity().x = (dir.x > 0) ? m_golemJumpSpeedX : -m_golemJumpSpeedX;
}

void GolemEnemy::landAndCooldown() {
    m_golemCooldownClock.restart();
    m_golemBody.getVelocity().x = 0;
    m_golemState = State::COOLDOWN;
}
