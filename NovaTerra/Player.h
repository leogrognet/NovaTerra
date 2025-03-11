#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>
#include "RigidBody.h"


using namespace std;
using namespace sf;

class Player {
public:
	
	RigidBody moncorps;
	enum class State { JUMPING, DOUBLEJUMP, DASHING, IDLE, MOVING, MIDAIR };
	enum class Direction { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

	Player();

	void update(float deltatime);
	void draw(RenderWindow& window);
	void handleInput();
	void jump();
	void dash();

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
	Clock cd;

	State state;
	Direction direction;
};