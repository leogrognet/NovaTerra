#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Entity.h"

using namespace std;
using namespace sf;


namespace fs = std::filesystem;

enum mouseState {
	SELECT,
	SET_TILE,
	DELETE_TILE,
};

class LevelEditor {
public:
	LevelEditor();
	void run();
	void loadLevel(const string& filename);
	void savelevel(const string& filename);
private:
	entityType m_entityTile;
	mouseState m_mouseEditorState;
	bool leftclick;
	int m_currentTile;
	void handleInput(RenderWindow& window, View& view, Event& event, float deltaTime);
	void update();
	void draw(RenderWindow& window);
	void dropDownMenu(RenderWindow& window);
	map<pair<int, int>, int> m_tiles;
	vector<RectangleShape> m_tilesShape;
	vector<RectangleShape> m_tilesMenu;
	const int TILE_SIZE = 32;

	

};
