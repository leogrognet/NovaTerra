#include "Player.h"
#include <SFML/Window/Joystick.hpp>

Player::Player() : hp(5), speed(50), state(State::IDLE), direction(Direction::RIGHT), body({100,700}), action(Action::NONE)
{
	playershape.setFillColor(Color::Red);
	playershape.setSize({ 25,25 });
	//playershape.setOrigin(12.5, 12.5);
	playershape.setPosition(100, 700);
}

void Player::update(float deltatime, vector<RectangleShape>& shape)
{
	dtime = deltatime;

	//coutState();
	handleInput();
	dash();
	body.update(deltatime);
	body.groundCollision(shape, playershape.getGlobalBounds());

	playershape.setPosition(body.position);
	grapplinshoot();

	hook.setPosition(playershape.getPosition().x, playershape.getPosition().y);
}

void Player::draw(RenderWindow& window) 
{ 
	window.draw(playershape); 
	if (action == Action::HOOK){ 
		window.draw(hook); 
	} 
}

void Player::handleInput()
{
	// Keyboard input
	if (Keyboard::isKeyPressed(Keyboard::Q)) { direction = Direction::LEFT;  body.velocity.x = -500; }
	else if (Keyboard::isKeyPressed(Keyboard::D)) { direction = Direction::RIGHT; body.velocity.x = 500;}
	else { body.velocity.x = 0; }

	if (Keyboard::isKeyPressed(Keyboard::Z)) { direction = Direction::UP; }
	if (Keyboard::isKeyPressed(Keyboard::S)) { direction = Direction::DOWN; }

	// Direction diagonale haut
	if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::D)) { direction = Direction::UPRIGHT; }
	if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::Q)) { direction = Direction::UPLEFT; }

	// Direction diagonale bas
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) { direction = Direction::DOWNRIGHT; }
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::Q)) { direction = Direction::DOWNLEFT; }

	if (Keyboard::isKeyPressed(Keyboard::Space) && body.isGrounded) {
		body.velocity.y = -500;
	}

	if (Keyboard::isKeyPressed(Keyboard::F)) { 
		action = Action::HOOK;
		hookSize = 0; 
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift) && cd.getElapsedTime().asSeconds() > 1 && action != Action::HOOK) {
		cd.restart();
		action = Action::DASHING;
	}

	if (Joystick::isConnected(0)) {
		float x = Joystick::getAxisPosition(0, Joystick::X);
		float y = Joystick::getAxisPosition(0, Joystick::Y);

		if (x < -50) { direction = Direction::LEFT; body.velocity.x = -500; }
		if (x > 50) { direction = Direction::RIGHT; body.velocity.x = 500; }

		if (y < -50) { direction = Direction::UP; }
		if (y > 50) { direction = Direction::DOWN; }

		// Direction diagonale haut
		if (y < -50 && x > 50) { direction = Direction::UPRIGHT; }
		if (y < -50 && x < -50) { direction = Direction::UPLEFT; }

		// Direction diagonale bas
		if (y > 50 && x > 50) { direction = Direction::DOWNRIGHT; }
		if (y > 50 && x < -50) { direction = Direction::DOWNLEFT; }

		if (Joystick::isButtonPressed(0, 0) && body.isGrounded) {
			body.velocity.y = -500;
		}

		if (Joystick::isButtonPressed(0, 1) && cd.getElapsedTime().asSeconds() > 1) { // Assuming button 1 is the dash button
			cd.restart();
			state = State::DASHING;
		}
	}
}

void Player::dash()
{
	if (action == Action::DASHING) {
		switch (direction) {
		case Direction::RIGHT: body.velocity.x = 1000; break;
		case Direction::LEFT: body.velocity.x = -1000; break;
		case Direction::UP: body.velocity.y = -1000; break;
		case Direction::UPRIGHT: body.velocity.x = 1000; body.velocity.y = -1000; break;
		case Direction::UPLEFT: body.velocity.x = -1000; body.velocity.y = -1000; break;
		}

		if (cd.getElapsedTime().asSeconds() > 0.1f) {
			action = Action::NONE;
		}
	}
}

void Player::grapplinshoot()
{
	if (action == Action::HOOK) {
		hookSize += dtime * 170;
		if (direction == Direction::RIGHT || direction == Direction::UPRIGHT) {
			hook.setScale({ hookSize,2.5f });
		}
		else {
			hook.setScale({ -hookSize,2.5f });
		}
		
		if (hookSize >= 100) {
			action = Action::NONE;
		}
	}
}

void Player::coutState()
{
	switch (state) {
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
