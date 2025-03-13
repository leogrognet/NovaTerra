#include "Player.h"
#include <SFML/Window/Joystick.hpp>

Player::Player() : m_hp(5), m_state(State::IDLE), m_direction(Direction::RIGHT), body({100,700}), m_action(Action::NONE)
{
	m_playershape.setFillColor(Color::Red);
	m_playershape.setSize({ 25,25 });
	//m_playershape.setOrigin(12.5, 12.5);
	m_playershape.setPosition(100, 700);

	m_hook.setSize({ 2.5f,2.5f });
	m_hook.setFillColor(Color::White);
	m_hook.setOrigin(0, 1.75f);
}

void Player::update(float deltatime, vector<RectangleShape>& shape)
{
	m_deltatime = deltatime;

	//Cout du m_state si besoin de debug
	//coutState();
	updateDirection();
	handleInput(); 
	
	dash();
	body.update(deltatime);
  m_playershape.setPosition(body.getPosition());
	body.groundCollision(shape, m_playershape.getGlobalBounds());
	
	m_playershape.setPosition(body.getPosition());
	grapplinshoot(shape);
	grabing();

	//Cout du player pos si besoin de debug
	//cout << m_playershape.getPosition().x << " " << m_playershape.getPosition().y << endl;
	m_hook.setPosition(m_playershape.getPosition().x, m_playershape.getPosition().y);
}

void Player::draw(RenderWindow& window) 
{ 
	window.draw(m_playershape); 
	if (m_action == Action::HOOK || m_action == Action::REVERSEHOOK){ 
		window.draw(m_hook); 
	} 
}

void Player::handleInput()
{
	// D�sactiv� les inputs si le joueur est en train de hook ou de grab ou de dash	
	if (m_action != Action::REVERSEHOOK && m_action != Action::GRABING && m_action != Action::DASHING) {

		// Keyboard input
		if (Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::LEFT;  body.getVelocity().x = -500; }
		else if (Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::RIGHT; body.getVelocity().x = 500; }
		else { body.getVelocity().x = 0; }

		if (Keyboard::isKeyPressed(Keyboard::Z)) { m_direction = Direction::UP; }
		if (Keyboard::isKeyPressed(Keyboard::S)) { m_direction = Direction::DOWN; }

		// Direction diagonale haut
		if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::UPRIGHT; }
		if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::UPLEFT; }

		// Direction diagonale bas
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) { m_direction = Direction::DOWNRIGHT; }
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::Q)) { m_direction = Direction::DOWNLEFT; }

		if (Keyboard::isKeyPressed(Keyboard::Space) && body.getIsGrounded()) {
			body.getVelocity().y = -500;
		}

		if (Keyboard::isKeyPressed(Keyboard::F) && m_hookCd.getElapsedTime().asSeconds() >= 5) {
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

			if (x < -50) { m_direction = Direction::LEFT; body.getVelocity().x = -500; }
			if (x > 50) { m_direction = Direction::RIGHT; body.getVelocity().x = 500; }

			if (y < -50) { m_direction = Direction::UP; }
			if (y > 50) { m_direction = Direction::DOWN; }

			// Direction diagonale haut
			if (y < -50 && x > 50) { m_direction = Direction::UPRIGHT; }
			if (y < -50 && x < -50) { m_direction = Direction::UPLEFT; }

			// Direction diagonale bas
			if (y > 50 && x > 50) { m_direction = Direction::DOWNRIGHT; }
			if (y > 50 && x < -50) { m_direction = Direction::DOWNLEFT; }

			if (Joystick::isButtonPressed(0, 0) && body.getIsGrounded()) {
				body.getVelocity().y = -500;
				cout << "Jump triggered from controller!" << endl;
			}

			if (Joystick::isButtonPressed(0, 1) && m_hookCd.getElapsedTime().asSeconds() > 1) {
				m_hookCd.restart();
				m_action = Action::DASHING;
				cout << "Dashing triggered from controller!" << endl;
			}

			if (Joystick::isButtonPressed(0, 2) && m_hookCd.getElapsedTime().asSeconds() > 1) {
				m_action = Action::HOOK;
				m_hookSize = 0;
				cout << "Hook triggered from controller!" << endl;
			}
		}
	}
}

void Player::dash()
{
	if (m_action == Action::DASHING) {
		switch (m_direction) {
		case Direction::RIGHT: body.getVelocity().x = 1000; break;
		case Direction::LEFT: body.getVelocity().x = -1000; break;
		case Direction::UP: body.getVelocity().y = -1000; break;
		case Direction::UPRIGHT: body.getVelocity().x = 1000; body.getVelocity().y = -1000; break;
		case Direction::UPLEFT: body.getVelocity().x = -1000; body.getVelocity().y = -1000; break;
		}

		if (m_hookCd.getElapsedTime().asSeconds() > 0.1f) {
			m_action = Action::NONE;
		}
	}
}

void Player::grapplinshoot(vector<RectangleShape>& shape)
{
	if (m_action == Action::HOOK) {
		m_hookSize += m_deltatime * 170;
		for (auto& vec : shape) {
			if (m_hook.getGlobalBounds().intersects(vec.getGlobalBounds(), m_intersection)) {
				m_hookCd.restart();
				m_action = Action::REVERSEHOOK;
				body.getVelocity() = {0,0};
			}

			m_hook.setScale({ m_hookSize * m_stockedDirection.x,2.5f });

			if (m_hookSize >= 100) {
				m_action = Action::NONE;
			}
		}		
	}
	if (m_action == Action::REVERSEHOOK) {
		body.getVelocity().x = 800.f * m_stockedDirection.x;
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
		body.getVelocity().y = -981.f * m_deltatime;
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			m_action = Action::NONE; 
			body.getVelocity().y = -400;
		}
		if (Joystick::isConnected(0) && Joystick::isButtonPressed(0,0)) {
			m_action = Action::NONE;
			body.getVelocity().y = -400;
		}
	}
}

void Player::coutState()
{
	switch (m_state) {
	case State::IDLE:
		cout << "State : Idle" << endl;
		break;
	case State::JUMPING:
		cout << "State : Jumping" << endl;
		break;
	case State::DASHING:
		cout << "State : Dashing" << endl;
		break;
	case State::MIDAIR:
		cout << "State : Air" << endl;
		break;
	}
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