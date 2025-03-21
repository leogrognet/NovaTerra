#include "GolemEnemy.h"

GolemEnemy::GolemEnemy(float posX, float posY, bool isStatic, bool asCollision): Entity(posX, posY, isStatic, asCollision),m_golemState(State::IDLE) {
    golemTexture.loadFromFile("../assets/fries.png");
    m_shape.setTexture(golemTexture);
    m_shape.setPosition(posX, posY);
    m_shape.setScale(1.f,1.f);
}

void GolemEnemy::update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) {
    updateFSM(colliders);

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
    float distance;
    for (auto entity : colliders) {
        // Le player a un ID = 1
        if (entity->getID() == 1) {
            distance = abs(entity->getSprite().getPosition().x - m_shape.getPosition().x);
            break;
        }
    }

    //cout << distance << endl;

    switch (m_golemState) {
    case State::IDLE:
        if (distance <= m_golemDetectionRange) {
			cout << "Golem detected player\n";
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
    cout << "Golem jumped to player\n";
}

void GolemEnemy::landAndCooldown() {
    m_golemCooldownClock.restart();
    m_rigidBody.getVelocity().x = 0;
    m_golemState = State::COOLDOWN;
    cout << "Golem landed and is on cooldown\n";
}
