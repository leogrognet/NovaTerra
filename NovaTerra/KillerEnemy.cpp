#include "KillerEnemy.h"

KillerEnemy::KillerEnemy(float posX, float posY, bool isStatic, bool hasCollision)
    : Entity(posX, posY, isStatic, hasCollision),
    m_KillerState(State::IDLE),
    velocity(0.f, 0.f),
    dashDirection(0.f, 0.f)
{

    if (!killerTexture.loadFromFile("assets/croc/killercroc.png")) {
        cerr << "KillerEnemy: Failed to load texture." << endl;
    }

    m_shape.setSize(Vector2f(48.f, 48.f));
    m_shape.setTexture(&killerTexture);
    m_shape.setPosition(posX, posY);
    m_shape.setScale(1.f, 1.f);
}

void KillerEnemy::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
    updateFSM(colliders);

    // Apply velocity (dash movement)
    m_shape.move(velocity * deltaTime);
    position = m_shape.getPosition();
}

void KillerEnemy::draw(RenderWindow& window) {
    window.draw(m_shape);
}

int KillerEnemy::getID() {
    return 3; // Unique ID for KillerEnemy
}

void KillerEnemy::updateFSM(const vector<shared_ptr<Entity>>& colliders) {
    shared_ptr<Entity> player = nullptr;

    // Find the player entity (ID = 1)
    for (const auto& entity : colliders) {
        if (entity->getID() == 1) {
            player = entity;
            break;
        }
    }

    if (!player) return;

    float distanceToPlayer = abs(player->getSprite().getPosition().x - m_shape.getPosition().x);

    switch (m_KillerState) {
    case State::IDLE:
        if (distanceToPlayer <= m_KillerDetectionRange) {
            dashToPlayer(player);
            m_KillerState = State::DASHING;
            m_KillerCooldownClock.restart();
        }
        break;

    case State::DASHING:
        // Stop the dash instantly after one frame of movement
        velocity = Vector2f(0.f, 0.f);
        m_KillerState = State::COOLDOWN;
        break;

    case State::COOLDOWN:
        stopAndCooldown(m_KillerCooldownClock.getElapsedTime().asSeconds());
        break;
    }
}

void KillerEnemy::dashToPlayer(const vector<shared_ptr<Entity>>& colliders) {
    Vector2f direction = player->getSprite().getPosition() - m_shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0.f)
        dashDirection = direction / length;
    else
        dashDirection = Vector2f(0.f, 0.f);

    velocity = dashDirection * m_KillerDashSpeed;
}

void KillerEnemy::stopAndCooldown(float deltaTime) {
    if (m_KillerCooldownClock.getElapsedTime().asSeconds() >= m_KillerKashCooldown) {
        m_KillerState = State::IDLE;
    }
}
