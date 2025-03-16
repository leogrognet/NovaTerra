#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
}

void LevelEditor::run()
{
}

void LevelEditor::loadLevel(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de charger le fichier " << filename << std::endl;
        return;
    }

    m_tiles.clear();
    int x, y, tileID;
    while (file >> x >> y >> tileID) {
        m_tiles[{x, y}] = tileID;
    }

    file.close();
    std::cout << "Niveau chargé depuis " << filename << std::endl;
}

void LevelEditor::savelevel(const string& filename)
{
    ofstream textFile(filename);
    if (!textFile.is_open()) {
        std::cerr << "Erreur : Impossible de sauvegarder le fichier " << filename << std::endl;
        return;
    }
    for (auto& [pos, tileID] : m_tiles) {
        textFile << pos.first << " " << pos.second << " " << tileID << endl;

    }
}

void LevelEditor::handleInput(RenderWindow& window, View& view, Event& event, float deltaTime)
{
    Vector2i mouseTilePosition = Mouse::getPosition(window) / TILE_SIZE;

    if (Mouse::getPosition(window) == Vector2i(0, 0)) {
        m_mouseEditorState = SELECT;
    }
    else if (Mouse::getPosition(window) == Vector2i(1, 1))
    {
        m_mouseEditorState = SET_TILE;
    }
    else if (Mouse::getPosition(window) == Vector2i(2, 2)) {
        m_mouseEditorState = DELETE_TILE;
    }


    if (Mouse::isButtonPressed(Mouse::Left)) {
        switch (m_mouseEditorState)
        {
        case 1:
            m_tiles[{mouseTilePosition.x, mouseTilePosition.y}] = m_entityTile;
            break;
        case 2:
            if (m_tiles.find({ mouseTilePosition.x, mouseTilePosition.y }) != m_tiles.end()) {
                m_tiles.erase({ mouseTilePosition.x, mouseTilePosition.y });
            }
            break;

        case 3:


            break;
        }
    }

    float scrollSpeed = 10;
    float zoomFactor = 0.8;
    if (event.type == Event::MouseWheelScrolled) {
        switch (m_mouseEditorState)
        {
        case SELECT:
            if (event.mouseWheelScroll.delta > 0) {
                for (auto& tilesButton : m_tilesMenu) {
                    tilesButton.move(0, -scrollSpeed * deltaTime);
                }

            }
            else if (event.mouseWheelScroll.delta < 0) {
                for (auto& tilesButton : m_tilesMenu) {
                    tilesButton.move(0, scrollSpeed * deltaTime);
                }
            }
            break;
        case DELETE_TILE || SET_TILE:
            if (event.mouseWheelScroll.delta > 0) {
                zoomFactor *= 0.9f;
                for (auto& tilesButton : m_tilesMenu) {
                }

            }
            else if (event.mouseWheelScroll.delta < 0) {
                zoomFactor *= 1.1f;
                for (auto& tilesButton : m_tilesMenu) {
                }
            }
            view.setSize(window.getSize().x* zoomFactor, window.getSize().y* zoomFactor);

            break;
        }
    }




}

void LevelEditor::update()
{
}

void LevelEditor::draw(RenderWindow& window)
{
}

void LevelEditor::dropDownMenu(RenderWindow& window)
{
    

}
