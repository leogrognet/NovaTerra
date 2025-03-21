#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <type_traits>
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

enum tileState {
    NORMAL_TILE,
    BIOME_1,
    BIOME_2,
    BIOME_3,
};

class LevelEditor {
public:
    // 1. Constructeur
    LevelEditor(RenderWindow& window);

    // 2. M�thode principale de mise � jour
    bool update(RenderWindow& window, View& tileView, View& Ui_view, Event& event, float deltaTime);
    vector<shared_ptr<Texture>> m_SperatedTileTextures_1;
    vector<shared_ptr<Texture>> m_SperatedTileTextures_2;
    vector<shared_ptr<Texture>> m_FileTileTextures;



private:
    // 3. Variables membres
    entityType m_entityTile;
    MouseState m_mouseEditorState;
    tileState m_tileState;


    int m_textureType;
    bool m_subMenu;
    bool m_isOpen;
    int m_currentTile;
    string m_currentLevel;
    float viewOffsetSpeed;
    int m_textureId;
    int m_lastState;
    const int TILE_SIZE = 32;


    // 4. Structures de donn�es

    map<pair<int, int>, pair<int, int>> m_tiles;
    vector<shared_ptr<RectangleShape>> m_tilesShape;


    vector<shared_ptr<Sprite>> m_TilesScrollMenu;
    vector<shared_ptr<RectangleShape>> m_TilesBordersMenu;

    vector<shared_ptr<RectangleShape>> m_selectorMenu;
    vector<unique_ptr<Text>> m_selectorMenuTexts;


    vector<vector<shared_ptr<Texture>>> m_allTextureVector;

    // 5. Objets SFML
    RectangleShape m_tileScrollBox;
    Font m_font;
    TextureLoader loadTexture;

    // 6. M�thodes priv�es

    // 6.1 Gestion des niveaux
    void loadLevel(const string& filename);
    void savelevel(const string& filename);
    void openFileExplorer();

    // 6.2 Interface utilisateur
    void dropDownMenu(RenderWindow& window, vector<shared_ptr<RectangleShape>>& tileBordersMenu, vector<shared_ptr<Sprite>>& tilesScrollMenu, vector<shared_ptr<Texture>>& tileTextures);
    void addSelectorButton(sf::Color color, const std::string& label);

    // 6.3 Gestion des entr�es
    void handleInput(RenderWindow& window, View& tileView, Event& event, float deltaTime);

    void handleMenuScroll(Event& event, float deltaTime, std::vector<std::shared_ptr<Sprite>>& scrollMenu, std::vector<std::shared_ptr<RectangleShape>>& bordersMenu, float scrollSpeed, float minScrollY, float maxScrollY);

    // 6.4 Dessin des �l�ments
    void draw(RenderWindow& window, View& tileView, View& Ui_View);
    void updateTiles();
    void tileSetter(shared_ptr<RectangleShape> tile, Vector2i MousTilePos, int textureIndex, int vectorIndex);

    void subMenuHandler(std::vector<std::shared_ptr<RectangleShape>>& tileMenu, RenderWindow& window);


    // 6.5 M�thodes utilitaires
    bool isTileTransparent(const Texture& texture, const IntRect& rect);
    vector<shared_ptr<Texture>> getNonTransparentTiles(int tileWidth, int tileHeight, int index);




};