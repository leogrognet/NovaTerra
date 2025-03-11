#include "Player.h"
#include <SFML/Window/Joystick.hpp>

Player::Player() : hp(5), speed(50), gravity(9.81), jumpspeed(20), state(State::IDLE), direction(Direction::RIGHT)
{
	playershape.setFillColor(Color::Red);
	playershape.setSize({ 25,25 });
	playershape.setOrigin(12.5, 12.5);
	playershape.setPosition(100, 100);

	hook.setSize({ 2.5f,2.5f });
	hook.setFillColor(Color::White);
	hook.setOrigin(0, 1.75f);
}

void Player::update(float deltatime)
{
	dtime = deltatime;

	//coutState();
	handleInput();
	jump();
	dash();
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
	if (Keyboard::isKeyPressed(Keyboard::Q)) { direction = Direction::LEFT; playershape.move(-speed * dtime * 10, 0); }
	if (Keyboard::isKeyPressed(Keyboard::D)) { direction = Direction::RIGHT; playershape.move(speed * dtime * 10, 0); }

	if (Keyboard::isKeyPressed(Keyboard::Z)) { direction = Direction::UP; }
	if (Keyboard::isKeyPressed(Keyboard::S)) { direction = Direction::DOWN; }

	// Direction diagonale haut
	if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::D)) { direction = Direction::UPRIGHT; }
	if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::Q)) { direction = Direction::UPLEFT; }

	// Direction diagonale bas
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) { direction = Direction::DOWNRIGHT; }
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::Q)) { direction = Direction::DOWNLEFT; }

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (playershape.getPosition().y >= 800 && state != State::JUMPING) {
			state = State::JUMPING;
			time = 0;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::F)) { 
		action = Action::HOOK;
		hookSize = 0; 
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift) && cd.getElapsedTime().asSeconds() > 1 && action != Action::HOOK) {
		cd.restart();
		action = Action::DASHING;
	}

	// Joystick input
	if (Joystick::isConnected(0)) {
		float x = Joystick::getAxisPosition(0, Joystick::X);
		float y = Joystick::getAxisPosition(0, Joystick::Y);

		if (x < -50) { direction = Direction::LEFT; playershape.move(-speed * dtime * 10, 0); }
		if (x > 50) { direction = Direction::RIGHT; playershape.move(speed * dtime * 10, 0); }

		if (y < -50) { direction = Direction::UP; }
		if (y > 50) { direction = Direction::DOWN; }

		// Direction diagonale haut
		if (y < -50 && x > 50) { direction = Direction::UPRIGHT; }
		if (y < -50 && x < -50) { direction = Direction::UPLEFT; }

		// Direction diagonale bas
		if (y > 50 && x > 50) { direction = Direction::DOWNRIGHT; }
		if (y > 50 && x < -50) { direction = Direction::DOWNLEFT; }

		if (Joystick::isButtonPressed(0, 0)) { // Assuming button 0 is the jump button
			if (playershape.getPosition().y >= 800 && state != State::JUMPING) {
				state = State::JUMPING;
				time = 0;
			}
		}

		if (Joystick::isButtonPressed(0, 1) && cd.getElapsedTime().asSeconds() > 1) { // Assuming button 1 is the dash button
			cd.restart();
			action = Action::DASHING;
		}
	}
}

void Player::jump()
{
	time += dtime;

	if (state == State::JUMPING) {
		jumpspeed -= dtime * 80;
		playershape.move(0, -jumpspeed * dtime * 60);
		if (jumpspeed <= 0) {
			state = State::IDLE;
			jumpspeed = 20;
		}
	}
	else if (action != Action::DASHING) {
		if (playershape.getPosition().y <= 800) {
			state = State::MIDAIR;
			playershape.setPosition(playershape.getPosition().x, playershape.getPosition().y + gravity * dtime * 70);
		}
		else {
			state = State::IDLE;
		}
	}
}

void Player::dash()
{
	if (action == Action::DASHING) {
		switch (direction) {
		case Direction::RIGHT: playershape.move(dashspeed * dtime * 15, 0); break;
		case Direction::LEFT: playershape.move(-dashspeed * dtime * 15, 0); break;
		case Direction::UP: playershape.move(0, -dashspeed * dtime * 15); break;
		case Direction::UPRIGHT: playershape.move(dashspeed * dtime * 15, -dashspeed * dtime * 15); break;
		case Direction::UPLEFT: playershape.move(-dashspeed * dtime * 15, -dashspeed * dtime * 15); break;

			// Pour le moment le dash vers le bas est mis de côté. A revoir plus tard après collisions créés.

			/*case Direction::DOWN:
				cout << "Dash down" << endl;
				if (state != State::IDLE) {
					cout << "Dash execute" << endl;
				playershape.move(0, dashspeed * deltatime * 15);
			}
				break;
			case Direction::DOWNRIGHT:
				if (state != State::IDLE) {
					playershape.move(dashspeed * deltatime * 15, dashspeed * deltatime * 15);
				}
				break;
			case Direction::DOWNLEFT:
				if (state != State::IDLE) {
					playershape.move(-dashspeed * deltatime * 15, dashspeed * deltatime * 15);
				}
				break;*/
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
