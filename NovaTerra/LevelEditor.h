#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Entity.h"

using namespace std;
using namespace sf;


namespace fs = std::filesystem;

enum MouseState {
	SELECT,
	SET_TILE,
	DELETE_TILE,
};

class LevelEditor {
public:
	LevelEditor();
	void run();
	void loadLevel(const string& filename);
	void savelevel(const string& filename);entityType m_entityTile;
	MouseState m_mouseEditorState;
	bool leftclick;
	int m_currentTile;
	void handleInput(RenderWindow& window, View& view, Event& event, float deltaTime);
	void update();
	void draw(RenderWindow& window);
	void dropDownMenu(RenderWindow& window);

	void updateTiles();

	void selectButtonMenu(RenderWindow& window);

	map<pair<int, int>, int> m_tiles;
	vector<unique_ptr<RectangleShape>> m_tilesShape;
	vector<unique_ptr<RectangleShape>> m_tilesMenu;
	vector<unique_ptr<RectangleShape>> m_selectorMenu;
	const int TILE_SIZE = 32;
private:
	
	MouseState m_lastState;
	

};
