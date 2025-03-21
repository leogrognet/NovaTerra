#include "GolemEnemy.h"

GolemEnemy::GolemEnemy(float posX, float posY, bool isStatic, bool asCollision): Entity(posX, posY, isStatic, asCollision),m_golemState(State::IDLE), animation(m_shape, { 340,534 }, 2, 0.2f) {
    golemTexture.loadFromFile("../NovaTerra/assets/Image/GOLEM/sprite_sheet_golem.png");
    m_shape.setTexture(golemTexture);
    m_shape.setPosition(posX, posY);
    float scaleFactorX = 160 / m_shape.getGlobalBounds().width;
    float scaleFactorY = 160/ m_shape.getGlobalBounds().height;
    
    m_shape.setScale({ scaleFactorX,scaleFactorY });
}

void GolemEnemy::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
    updateFSM(colliders);

    if (m_rigidBody.getVelocity().x > 0) {
        animation.animationSwitch(m_shape, deltaTime, { 340,534 });
    }
    else {
        animation.animationSwitch(m_shape, deltaTime, { -340,534 });
    }

    Entity::update(deltaTime, colliders);
    for (auto entity : colliders) {
        if (entity->getID() == 1 && m_shape.getGlobalBounds().intersects(entity->getSprite().getGlobalBounds())) {
            entity->takeDamage();
        }
    }
}

void GolemEnemy::draw(RenderWindow& window) {
    window.draw(m_shape);
}

int GolemEnemy::getID()
{
    return 2;
}

void GolemEnemy::updateFSM(const vector<shared_ptr<Entity>>& colliders) {
    float distance{};
    for (auto entity : colliders) {
        // Le player a un ID = 1
        if (entity->getID() == 1) {
            distance = abs(entity->getSprite().getPosition().x - m_shape.getPosition().x);
            break;
        }
    }


    switch (m_golemState) {
    case State::IDLE:
        if (distance <= m_golemDetectionRange) {
            jumpToPlayer(colliders);
            m_golemState = State::JUMPING;
        }
        break;

    case State::JUMPING:
        if (m_rigidBody.getIsGrounded()) {
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

void GolemEnemy::jumpToPlayer(const vector<shared_ptr<Entity>>& colliders) {
    Vector2f dir;
    for (auto entity : colliders) {
        if (entity->getID() == 1) {
            dir = entity->getSprite().getPosition() - m_shape.getPosition();
            break;
        }
    }
    m_rigidBody.getVelocity().y = m_golemJumpForce;
    m_rigidBody.getVelocity().x = (dir.x > 0) ? m_golemJumpSpeedX : -m_golemJumpSpeedX;
}

void GolemEnemy::landAndCooldown() {
    m_golemCooldownClock.restart();
    m_rigidBody.getVelocity().x = 0;
    m_golemState = State::COOLDOWN;
}
