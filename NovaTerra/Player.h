#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Player {
public:

	enum class State { JUMPING, IDLE, MIDAIR, DASHING }; // Ajout de DASHING
	enum class Action { DASHING, HOOK, NONE };
	enum class Direction { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

	Player();

	void update(float deltatime);
	void draw(RenderWindow& window);
	void handleInput();

	void jump();
	void dash();
	void grapplinshoot();

	void coutState();

private:
	const float dashspeed = 150.f;

	float speed;
	float jumpspeed;
	float gravity;

	float dtime = 0;
	float time = 0;

	int hp;

	RectangleShape playershape;
	RectangleShape hook;
	float hookSize = 0;

	Clock cd;

	State state;
	Direction direction;
	Action action;

	bool jumpKeyPressed = false;
};