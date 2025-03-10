#include "Player.h"

Player::Player() : hp(5), speed(100), gravity(9.81), jumpspeed(10), lastKey('D')
{
	playershape.setFillColor(Color::Cyan);
	playershape.setSize({ 25,25 });
	playershape.setOrigin(12.5, 12.5);
	playershape.setPosition(100, 800);
}

void Player::update(float deltatime)
{
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
		if (playershape.getPosition().y >= 800 && !isJumping) {
			isJumping = true;
			time = 0;
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::LShift) && cd.getElapsedTime().asSeconds() > 3) {
		cd.restart();
		isDashing = true;
	}
}

void Player::jump(float deltatime)
{
	time += deltatime;

	if (isJumping) {
		playershape.move(0, -jumpspeed * deltatime * 125);
		if (time >= 0.2f) {
			isJumping = false;
		}
	}
	else if (!isDashing){
		if (playershape.getPosition().y <= 800) {
			playershape.setPosition(playershape.getPosition().x, playershape.getPosition().y + gravity * deltatime * 125);
		}
	}
}

void Player::dash(float deltatime)
{
	if (isDashing) {
		speed = 200;
		//isJumping = true;
		switch (lastKey) {
		case 'D':
			playershape.move(speed * deltatime * 15, 0);
			break;
		case 'Q':
			playershape.move(-speed * deltatime * 15, 0);
			break;
		}
		if (cd.getElapsedTime().asSeconds() > 0.1f) {
			speed = 100.f;
			isDashing = false;
		}
	}
	
}
