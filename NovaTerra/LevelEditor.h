#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Entity.h"
#include "tinyfiledialogs.h"
#include "TextureLoader.h"

using namespace std;
using namespace sf;


namespace fs = std::filesystem;

enum MouseState {
	
	SET_TILE,
	DELETE_TILE,
	SAVE_FILE,
	LOAD_FILE,
	SELECT,
};

class LevelEditor {
public:
	LevelEditor(RenderWindow& window);
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

	void tileSetter(unique_ptr<RectangleShape> tile, Vector2i MousTilePos);



	void updateFile();

	void updateTiles();

	void addSelectorButton(sf::Color color, const std::string& label);


	void openFileExplorer();

	float viewOffsetSpeed;
	int m_textureId;
	vector<shared_ptr<Texture>> m_tileTextures;
	map<pair<int, int>, int> m_tiles;
	RectangleShape m_tileScrollBox;
	vector<unique_ptr<RectangleShape>> m_tilesShape;
	vector<unique_ptr<RectangleShape>> m_tilesScrollMenu;
	vector<unique_ptr<RectangleShape>> m_selectorMenu;
	vector<unique_ptr<Text>> m_selectorMenuTexts;
	Font m_font;
	TextureLoader loadTexture;

	const int TILE_SIZE = 32;




private:
	
	int m_lastState;
	

};
