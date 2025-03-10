#include "Player.h"

Player::Player() : hp(5), speed(70), gravity(9.81), jumpspeed(40), lastKey('D'), state(State::IDLE)
{
	playershape.setFillColor(Color::Cyan);
	playershape.setSize({ 25,25 });
	playershape.setOrigin(12.5, 12.5);
	playershape.setPosition(100, 800);
}

void Player::update(float deltatime)
{
	coutState();
	handleInput(deltatime);
	jump(deltatime);
	dash(deltatime);
}

void Player::draw(RenderWindow& window) { window.draw(playershape); }

void Player::handleInput(float deltatime)
{
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		lastKey = 'Q';
		playershape.move(-speed * deltatime * 10, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		lastKey = 'D';
		playershape.move(speed * deltatime * 10, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (playershape.getPosition().y >= 800 && state != State::JUMPING) {
			state = State::JUMPING;
			time = 0; 
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::LShift) && cd.getElapsedTime().asSeconds() > 3) {
		cd.restart();
		state = State::DASHING;
	}
}

void Player::jump(float deltatime)
{
	time += deltatime;
	
	if (state == State::JUMPING) {
		jumpspeed -= deltatime * 100;
		playershape.move(0, -jumpspeed * deltatime * 40);
		if (jumpspeed <= 0) {
			state = State::IDLE;
			jumpspeed = 40;
		}
	}
	else if (state != State::DASHING){
		if (playershape.getPosition().y <= 800) {
			playershape.setPosition(playershape.getPosition().x, playershape.getPosition().y + gravity * deltatime * 50);
		}
	}
}

void Player::dash(float deltatime)
{
	if (state == State::DASHING) {
		speed = 200;
		switch (lastKey) {
		case 'D':
			playershape.move(speed * deltatime * 15, 0);
			break;
		case 'Q':
			playershape.move(-speed * deltatime * 15, 0);
			break;
		}
		if (cd.getElapsedTime().asSeconds() > 0.1f) {
			speed = 70.f;
			state = State::IDLE;
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
	case State::DOUBLEJUMP:
		cout << "State : DoubleJump" << endl;
		break;
	case State::DASHING:
		cout << "State : Dashing" << endl;
		break;
	}
}
