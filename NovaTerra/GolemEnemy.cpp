#include "GolemEnemy.h"

GolemEnemy::GolemEnemy(Vector2f position, float posX, float posY, bool isStatic) : Entity(posX, posY, isStatic),m_golemState(State::IDLE), m_golemBody(position) {
    golemTexture.loadFromFile("../assets/fries.png");
    m_shape.setTexture(golemTexture);
    m_shape.setPosition(posX, posY);
    m_shape.setScale(1.f,1.f);
}

void GolemEnemy::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
    updateFSM(player);

    Entity::update(deltaTime,colliders)
    m_golemShape.setPosition(m_golemBody.getPosition());
}

void GolemEnemy::draw(RenderWindow& window) {
    window.draw(m_shape);
}

void GolemEnemy::updateFSM(const Player& player) {
    float distance = abs(player.body.getPosition().x - m_golemBody.getPosition().x);

    switch (m_golemState) {
    case State::IDLE:
        if (distance <= m_golemDetectionRange) {
			cout << "Golem detected player\n";
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

void GolemEnemy::jumpToPlayer(const Player& player) {
    Vector2f dir = player.body.getPosition() - m_golemBody.getPosition();
    m_golemBody.getVelocity().y = m_golemJumpForce;
    m_golemBody.getVelocity().x = (dir.x > 0) ? m_golemJumpSpeedX : -m_golemJumpSpeedX;
    cout << "Golem jumped to player\n";
}

void GolemEnemy::landAndCooldown() {
    m_golemCooldownClock.restart();
    m_golemBody.getVelocity().x = 0;
    m_golemState = State::COOLDOWN;
    cout << "Golem landed and is on cooldown\n";
}
