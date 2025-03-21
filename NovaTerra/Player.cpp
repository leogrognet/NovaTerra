#include "Player.h"
#include <SFML/Window/Joystick.hpp>

Player::Player(float posX, float posY, bool isStatic, bool asCollision) : Entity(posX, posY, isStatic, asCollision),
	m_hp(3), m_state(State::IDLE), m_direction(Direction::RIGHT), m_action(Action::NONE)
{
	m_texture.loadFromFile("../assets/player.png");
	m_shape.setTexture(m_texture);
	m_shape.setScale({ 0.5f,0.75f });
	m_shape.setPosition(posX, posY);

	m_hook.setSize({ 2.5f,2.5f });
	m_hook.setFillColor(Color::White);
	m_hook.setOrigin(0, 1.75f);

	m_hitbox.setSize({ 75,75 });
	m_hitbox.setPosition(posX, posY);
	m_hitbox.setFillColor(Color::Red);
}

void Player::update(float deltatime, const vector<shared_ptr<Entity>>& colliders)
{
	m_deltatime = deltatime;

	if (m_state != State::DEAD) {

		isDead();

		updateDirection();
		handleInput();
		dash();

		grapplinshoot(colliders);
		grabing(colliders);

		forceMove();

		Entity::update(deltatime, colliders);

		m_hook.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + 10);
		m_hitbox.setPosition(m_shape.getPosition().x - 5, m_shape.getPosition().y - 5);
		m_blackscreen.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + 10);
	}
	else {
		deathAnim();
	}
}

void Player::draw(RenderWindow& window) 
{ 
	window.draw(m_shape); 
	if (m_action == Action::HOOK || m_action == Action::REVERSEHOOK){ 
		window.draw(m_hook); 
	} 
	if (m_state == State::DEAD) {
		window.draw(m_blackscreen);
	}
}

void Player::handleInput()
{
	if (m_action == Action::REVERSEHOOK || m_action == Action::GRABING) { return; }

	//Clavier
	if (Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::LEFT;  m_rigidBody.getVelocity().x = -250; }
	else if (Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::RIGHT; m_rigidBody.getVelocity().x = 250;}
	else { m_rigidBody.getVelocity().x = 0; }

	if (Keyboard::isKeyPressed(Keyboard::Z)) { m_direction = Direction::UP; }
	if (Keyboard::isKeyPressed(Keyboard::S)) { m_direction = Direction::DOWN; }

	if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::UPRIGHT; }
	if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::UPLEFT; }

	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::DOWNRIGHT; }
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::DOWNLEFT; }

	if (Keyboard::isKeyPressed(Keyboard::Space) && m_rigidBody.getIsGrounded()) {
		m_rigidBody.getVelocity().y = -350;
	}
	if (Keyboard::isKeyPressed(Keyboard::F) && m_hookCd.getElapsedTime().asSeconds() >= 2) {
			m_action = Action::HOOK;
			m_hookSize = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift) && m_hookCd.getElapsedTime().asSeconds() > 1 && m_action != Action::REVERSEHOOK) {
			m_hookCd.restart();
			m_action = Action::DASHING;
	}

	//Manette
	if (Joystick::isConnected(0)) {
		float x = Joystick::getAxisPosition(0, Joystick::X);
		float y = Joystick::getAxisPosition(0, Joystick::Y);

		if (x < -50) { m_direction = Direction::LEFT; m_rigidBody.getVelocity().x = -250; }
		if (x > 50) { m_direction = Direction::RIGHT; m_rigidBody.getVelocity().x = 250; }

		if (y < -50) { m_direction = Direction::UP; }
		if (y > 50) { m_direction = Direction::DOWN; }

		if (y < -50 && x > 50) { m_direction = Direction::UPRIGHT; }
		if (y < -50 && x < -50) { m_direction = Direction::UPLEFT; }

		if (y > 50 && x > 50) { m_direction = Direction::DOWNRIGHT; }
		if (y > 50 && x < -50) { m_direction = Direction::DOWNLEFT; }

		if (Joystick::isButtonPressed(0, 0) && m_rigidBody.getIsGrounded()) {
			m_rigidBody.getVelocity().y = -350;
		}

		if (Joystick::isButtonPressed(0, 1) && m_hookCd.getElapsedTime().asSeconds() > 1 && m_action != Action::REVERSEHOOK) {
			m_hookCd.restart();
			m_action = Action::DASHING;
		}
		if (Joystick::isButtonPressed(0, 5) && m_hookCd.getElapsedTime().asSeconds() >= 2) {
			m_action = Action::HOOK;
			m_hookSize = 0;
		}
	}
	
}

void Player::dash()
{
	if (m_action == Action::DASHING) {
		switch (m_direction) {
		case Direction::RIGHT: m_rigidBody.getVelocity().x = 800; break;
		case Direction::LEFT: m_rigidBody.getVelocity().x = -800; break;
		case Direction::UP: m_rigidBody.getVelocity().y = -350; break;
		case Direction::UPRIGHT: m_rigidBody.getVelocity().x = 300; m_rigidBody.getVelocity().y = -300; break;
		case Direction::UPLEFT: m_rigidBody.getVelocity().x = -300; m_rigidBody.getVelocity().y = -300; break;
		}

		if (m_hookCd.getElapsedTime().asSeconds() > 0.1f) {
			m_action = Action::NONE;
		}
	}
}

void Player::grapplinshoot(const vector<shared_ptr<Entity>>& colliders)
{
	if (m_action == Action::HOOK) {
		m_hookSize += m_deltatime * 110;
		for (auto& vec : colliders) {
			if (m_hook.getGlobalBounds().intersects(vec->getSprite().getGlobalBounds(), m_intersection) && vec->getasCollision() && vec->getID() != 1) {
				m_hookCd.restart();
				m_action = Action::REVERSEHOOK;
				m_rigidBody.getVelocity() = { 0,0 };
			}
			m_hook.setScale({ m_hookSize * m_stockedDirection.x,2.5f });

			if (m_hookSize >= 100) {
				m_action = Action::NONE;
			}
		}
	}
	if (m_action == Action::REVERSEHOOK) {
		m_rigidBody.getVelocity().y = -981.f * m_deltatime / 2;
		m_rigidBody.getVelocity().x = 400.f * m_stockedDirection.x;
		m_hookSize -= m_deltatime * 150;
		m_hook.setScale(m_hookSize * m_stockedDirection.x , 2.5f );

		if (m_hookSize <= 0) {
			m_action = Action::GRABING;
		}
	}
}

void Player::grabing(const vector<shared_ptr<Entity>>& colliders)
{
	if (m_action == Action::GRABING) {
		m_rigidBody.getVelocity().y = -981.f * m_deltatime / 2;
		if (Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isConnected(0) && Joystick::isButtonPressed(0, 0)) {
			m_action = Action::NONE; 
			m_rigidBody.getVelocity().y = -200;
		}
		for (auto entity : colliders) {
			if ((Keyboard::isKeyPressed(Keyboard::Z) || (Joystick::isConnected(0) && Joystick::getAxisPosition(0, Joystick::Y) < -50))
				&& grabLiane && m_hitbox.getGlobalBounds().intersects(entity->getSprite().getGlobalBounds())) {
				m_rigidBody.getVelocity().y = -100.f;
			}
			else if ((Keyboard::isKeyPressed(Keyboard::S) || (Joystick::isConnected(0) && Joystick::getAxisPosition(0, Joystick::Y) > 50))
				&& grabLiane && m_hitbox.getGlobalBounds().intersects(entity->getSprite().getGlobalBounds())) {
				m_rigidBody.getVelocity().y = 100.f;
			}
		}		
	}
}

void Player::setGrabLiane(bool value)
{
	grabLiane = value;
}

int Player::getID()
{
	return 1;
}

void Player::forceMove()
{
	m_rigidBody.getVelocity() += m_forcedVelocity;
}

RectangleShape Player::getHitBox()
{
	return m_hitbox;
}

bool Player::isDead()
{
	if (m_hp <= 0 || m_shape.getPosition().y >= 1080) {
		m_stockedPos = m_shape.getPosition();
		m_shape.setColor(Color(255, 255, 255, 128));
		initializeBlackScreen();
		m_state = State::DEAD;
		return true;
	}
	return false;
}

void Player::deathAnim()
{
	if (m_fadeValue <= 255) {
		m_fadeValue += m_deltatime * 60;
		m_blackscreen.setFillColor(Color(7, 7, 7, m_fadeValue));

		m_rotationAngle += m_deltatime * 20;
		m_shape.move(0, -3);
		m_shape.setRotation(-m_rotationAngle);
	}
}

void Player::takeDamage()
{
	if (m_invincibleFrame.getElapsedTime().asSeconds() >= 1) {
		m_invincibleFrame.restart();
		m_hp--;
	}
}

void Player::initializeBlackScreen()
{
	m_blackscreen.setFillColor(Color(0, 0, 0, 0));
	m_blackscreen.setSize({ 3000,3000 });
	m_blackscreen.setOrigin(1500, 1500);
	m_blackscreen.setPosition(0,0);
}

void Player::setState(Player::State newState)
{
	m_state = newState;
}

Player::State Player::getState()
{
	return State();
}

void Player::setAction(Player::Action newAction)
{
	m_action = newAction;
}

Player::Action Player::getAction()
{
	return Action();
}

void Player::updateDirection()
{
	switch (m_direction) {
	case Direction::UP: m_stockedDirection = { 0,-1 };
		break;
	case Direction::RIGHT: m_stockedDirection = { 1,0 };
		break;
	case Direction::DOWN: m_stockedDirection = { 0,1 };
		break;
	case Direction::LEFT: m_stockedDirection = { -1,0 };
		break;
	}
}