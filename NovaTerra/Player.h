#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Player {
public:

	Player();

	void update(float deltatime);
	void draw(RenderWindow& window);
	void handleInput(float deltatime);
	void jump(float deltatime);
	void dash(float deltatime);

private:

	float speed;
	float jumpspeed;
	float gravity;

	float time = 0;

	bool isJumping = false;
	bool isDashing = false;

	int hp;

	RectangleShape playershape;
	Clock cd;

	char lastKey;
};