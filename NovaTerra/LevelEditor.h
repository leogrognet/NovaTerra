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
	SAVE_FILE,
	LOAD_FILE,
};

class LevelEditor {
public:
	LevelEditor();
	void run();
	void loadLevel(const string& filename);
	void savelevel(const string& filename);
	entityType m_entityTile;
	MouseState m_mouseEditorState;

	bool leftclick;
	int m_currentTile;
	string m_currentLevel;
	void handleInput(RenderWindow& window, View& tileView, Event& event, float deltaTime);
	void update();
	void draw(RenderWindow& window, View& tileView, View& Ui_View);
	void dropDownMenu(RenderWindow& window);

	void tileSetter(unique_ptr<RectangleShape> tile, Vector2i MousTilePos, Color color);



	void updateTiles();

	void addSelectorButton(sf::Color color);


	map<pair<int, int>, int> m_tiles;
	RectangleShape m_tileScrollBox;
	vector<unique_ptr<RectangleShape>> m_tilesShape;
	vector<unique_ptr<RectangleShape>> m_tilesScrollMenu;
	vector<unique_ptr<RectangleShape>> m_selectorMenu;
	const int TILE_SIZE = 32;
private:
	
	MouseState m_lastState;
	

};
