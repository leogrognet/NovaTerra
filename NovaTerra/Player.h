#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>
#include <vector>
#include "RigidBody.h"

using namespace std;
using namespace sf;

class Player {
public:

	RigidBody body;
	enum class State { JUMPING, IDLE, MIDAIR, DASHING };
	enum class Action { DASHING, HOOK, REVERSEHOOK, GRABING, NONE };
	enum class Direction { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

    Player();

	void update(float deltatime, vector<RectangleShape>& shape);
	void updateDirection();

	void draw(RenderWindow& window);
	void handleInput();

	void dash();
	void grapplinshoot(vector<RectangleShape>& shape);
	void grabing();

    void coutState();

private:
    const float m_dashspeed = 150.f;

    float m_deltatime = 0;
    float m_time = 0;

    int m_hp;

	RectangleShape m_playershape;
	RectangleShape m_hook;
	float m_hookSize = 0;

	Clock m_hookCd;
	Clock m_grabCd;

	State m_state;
	Direction m_direction;
	Action m_action;

	FloatRect m_intersection;
	Vector2f m_grabPos = { 0,0 };

	// Variable pour changer en fonction de la direction (enum) (0,1) pour bas par exemple
	Vector2f m_stockedDirection = { 0, 0 };

	bool m_jumpButtonPressed = false;
	bool m_canJump = false;
    bool m_jumpKeyPressed = false; 
};