#include "Player.h"
#include <SFML/Window/Joystick.hpp>

Player::Player(vector<shared_ptr<Entity>>& shape, float posX, float posY, bool isStatic) : Entity(posX, posY, isStatic),
	m_hp(5), m_state(State::IDLE), m_direction(Direction::RIGHT), m_action(Action::NONE)
{

	m_wallvec = shape;

	m_texture.loadFromFile("../assets/player.png");
	m_shape.setTexture(m_texture);
	m_shape.setScale({ 1.f,1.f });
	m_shape.setPosition(posX, posY);

	m_hook.setSize({ 2.5f,2.5f });
	m_hook.setFillColor(Color::White);
	m_hook.setOrigin(0, 1.75f);
}

void Player::update(float deltatime, const vector<shared_ptr<Entity>>& colliders)
{
	m_deltatime = deltatime;

	updateDirection();
	handleInput(); 
	dash();

	grapplinshoot();
	grabing();

	//Cout du player pos si besoin de debug
	cout << "Shape joueur : " << m_shape.getPosition().x << " " << m_shape.getPosition().y << endl;
	cout << "RigiBody : " <<m_rigidBody.getPosition().x << " " << m_rigidBody.getPosition().y << endl;
	//cout << m_shape.getScale().x << " " << m_shape.getScale().y << endl;

	m_hook.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);
}

void Player::draw(RenderWindow& window) 
{ 
	window.draw(m_shape); 
	if (m_action == Action::HOOK || m_action == Action::REVERSEHOOK){ 
		window.draw(m_hook); 
	} 
}

void Player::handleInput()
{
	// D�sactiv� les inputs si le joueur est en train de hook ou de grab
	if (m_action != Action::REVERSEHOOK && m_action != Action::GRABING) {
	// Keyboard input
		if (Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::LEFT;  m_rigidBody.getVelocity().x = -500; }
	else if (Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::RIGHT; m_rigidBody.getVelocity().x = 500;}
	else { m_rigidBody.getVelocity().x = 0; }

		if (Keyboard::isKeyPressed(Keyboard::Z)) { m_direction = Direction::UP; }
		if (Keyboard::isKeyPressed(Keyboard::S)) { m_direction = Direction::DOWN; }

		// Direction diagonale haut
		if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::UPRIGHT; }
		if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::UPLEFT; }

		// Direction diagonale bas
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::DOWNRIGHT; }
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::DOWNLEFT; }

	if (Keyboard::isKeyPressed(Keyboard::Space) && m_rigidBody.getIsGrounded()) {
		m_rigidBody.getVelocity().y = -500;
	}

		if (Keyboard::isKeyPressed(Keyboard::F) && m_hookCd.getElapsedTime().asSeconds() >= 2) {
			m_action = Action::HOOK;
			m_hookSize = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::LShift) && m_hookCd.getElapsedTime().asSeconds() > 1 && m_action != Action::REVERSEHOOK) {
			m_hookCd.restart();
			m_action = Action::DASHING;
		}

		if (Joystick::isConnected(0)) {
			float x = Joystick::getAxisPosition(0, Joystick::X);
			float y = Joystick::getAxisPosition(0, Joystick::Y);

		if (x < -50) { m_direction = Direction::LEFT; m_rigidBody.getVelocity().x = -500; }
		if (x > 50) { m_direction = Direction::RIGHT; m_rigidBody.getVelocity().x = 500; }

			if (y < -50) { m_direction = Direction::UP; }
			if (y > 50) { m_direction = Direction::DOWN; }

			// Direction diagonale haut
			if (y < -50 && x > 50) { m_direction = Direction::UPRIGHT; }
			if (y < -50 && x < -50) { m_direction = Direction::UPLEFT; }

			// Direction diagonale bas
			if (y > 50 && x > 50) { m_direction = Direction::DOWNRIGHT; }
			if (y > 50 && x < -50) { m_direction = Direction::DOWNLEFT; }

		if (Joystick::isButtonPressed(0, 0) && m_rigidBody.getIsGrounded()) {
			m_rigidBody.getVelocity().y = -500;
		}

			if (Joystick::isButtonPressed(0, 1) && m_hookCd.getElapsedTime().asSeconds() > 1) { // Assuming button 1 is the dash button
				m_hookCd.restart();
				m_state = State::DASHING;
			}
		}
	}
	
}

void Player::dash()
{
	if (m_action == Action::DASHING) {
		switch (m_direction) {
		case Direction::RIGHT: m_rigidBody.getVelocity().x = 1000; break;
		case Direction::LEFT: m_rigidBody.getVelocity().x = -1000; break;
		case Direction::UP: m_rigidBody.getVelocity().y = -1000; break;
		case Direction::UPRIGHT: m_rigidBody.getVelocity().x = 1000; m_rigidBody.getVelocity().y = -1000; break;
		case Direction::UPLEFT: m_rigidBody.getVelocity().x = -1000; m_rigidBody.getVelocity().y = -1000; break;
		}

		if (m_hookCd.getElapsedTime().asSeconds() > 0.1f) {
			m_action = Action::NONE;
		}
	}
}

void Player::grapplinshoot()
{
	if (m_action == Action::HOOK) {
		m_hookSize += m_deltatime * 170;
		for (auto& vec : m_wallvec) {
			if (m_hook.getGlobalBounds().intersects(vec->getSprite().getGlobalBounds(), m_intersection)) {
				m_hookCd.restart();
				m_action = Action::REVERSEHOOK;
				m_rigidBody.getVelocity() = {0,0};
			}

			m_hook.setScale({ m_hookSize * m_stockedDirection.x,2.5f });

			if (m_hookSize >= 100) {
				m_action = Action::NONE;
			}
		}		
	}
	if (m_action == Action::REVERSEHOOK) {
		m_rigidBody.getVelocity().x = 800.f * m_stockedDirection.x;
		m_hookSize -= m_deltatime * 300;
		m_hook.setScale(m_hookSize * m_stockedDirection.x , 2.5f);

		if (m_hookSize <= 0) {
			m_action = Action::GRABING;
		}
	}
}

void Player::grabing()
{
	if (m_action == Action::GRABING) {
		m_rigidBody.getVelocity().y = -981.f * m_deltatime;
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			m_action = Action::NONE; 
			m_rigidBody.getVelocity().y = -400;
		}
		if (Joystick::isConnected(0) && Joystick::isButtonPressed(0,0)) {
			m_action = Action::NONE;
			m_rigidBody.getVelocity().y = -400;
		}

		if (Keyboard::isKeyPressed(Keyboard::Z) && grabLiane) {
			m_rigidBody.getVelocity().y = -200.f;
		}
	}
}

void Player::setGrabLiane(bool value)
{
	grabLiane = value;
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