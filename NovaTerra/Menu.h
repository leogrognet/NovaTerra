#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;


enum class MenuState {
	MENU,
	PLAY,
	SETTINGS,
	EXIT,
	CREDITS
};

class Menu {
private:
	Texture backgroundTexture, playTexture, settingsTexture, exitTexture, creditsTexture;
	Sprite backgroundSprite, playSprite, settingsSprite, exitSprite, creditsSprite;
	RenderWindow& window;
	int selectedItemIndex;
public:
	Menu(RenderWindow& win);
	void draw();
	int handleMouseClick(Vector2i mousePos);
};

class MenuSettings {
private:
	Texture backgroundTexture, backTexture, keyTexture, soundTexture;
	Sprite backgroundSprite, backSprite, keySprite, soundSprite;
	RenderWindow& window;
	int selectedItemIndex;
public:
	MenuSettings(RenderWindow& win);
	void draw();
	int handleMouseClick(Vector2i mousePos);
};




#endif // MENU_H
