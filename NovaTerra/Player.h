#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>
#include <vector>
#include "RigidBody.h"
#include "Entity.h"

using namespace std;
using namespace sf;

class Player : public Entity {
public:

	enum class State { JUMPING, IDLE, MIDAIR, DASHING };
	enum class Action { DASHING, HOOK, REVERSEHOOK, GRABING, NONE };
	enum class Direction { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

    Player(vector<shared_ptr<Entity>>& shape, float posX, float posY, bool isStatic);

	void update(float deltaTime, const vector<shared_ptr<Entity>>& colliders) override;
	void updateDirection();

	void draw(RenderWindow& window) override;
	void handleInput();

	void dash();
	void grapplinshoot();
	void grabing();

	void setGrabLiane(bool value);

	int getID() override;

	void ForceMove() override;

	RectangleShape getHitBox()override;

private:

    float m_deltatime = 0;
	float m_hookSize = 0;
    int m_hp;
	
	RectangleShape m_hook;

	Clock m_hookCd;
	Clock m_grabCd;

	State m_state;
	Direction m_direction;
	Action m_action;

	FloatRect m_intersection;
	Vector2f m_grabPos = { 0,0 };

	Texture m_texture;

	vector<shared_ptr<Entity>> m_wallvec;

	// Variable pour changer en fonction de la direction (enum) (0,1) pour bas par exemple
	Vector2f m_stockedDirection = { 0, 0 };

	bool m_jumpButtonPressed = false;
	bool m_canJump = false;
    bool m_jumpKeyPressed = false; 

	bool grabLiane = true;
};