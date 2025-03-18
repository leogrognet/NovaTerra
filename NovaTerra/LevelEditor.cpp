#include "LevelEditor.h"

LevelEditor::LevelEditor(RenderWindow& window)
{
    m_mouseEditorState = SELECT;
    viewOffsetSpeed = 500.f;

    if (!m_font.loadFromFile("assets/font/default.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police" << std::endl;
    }

    m_textureId = 0;
    string map_tileSet = "assets\\map\\map_tileset";
    loadTexture.loadTexture(map_tileSet, m_tileTextures);
    dropDownMenu(window);
    dropDownMenu(window);
    addSelectorButton(Color::Blue, "Set");
    addSelectorButton(Color::Red, "Delete");
    addSelectorButton(Color::Green, "Save");
    addSelectorButton(Color::Yellow, "Load");
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
    m_tilesShape.clear(); 

    int x, y, tileID;
    while (file >> x >> y >> tileID) {
        m_tiles[{x, y}] = tileID;
    }

    file.close();
    std::cout << "Niveau chargé depuis " << filename << std::endl;

    updateTiles();
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

void LevelEditor::openFileExplorer() {
    const char* filterPatterns[] = { "*.txt" };
    const char* filePath = tinyfd_openFileDialog(
        "Choisir un fichier .txt",  
        "", 
        1,  
        filterPatterns,  
        NULL,  
        0  
    );

    if (filePath) {
        std::cout << "Fichier sélectionné : " << filePath << std::endl;
        m_currentLevel = filePath;
    }
    else {
        std::cout << "Aucun fichier sélectionné." << std::endl;
    }

}


void LevelEditor::handleInput(RenderWindow& window, View& tileView, Event& event, float deltaTime)
{
    Vector2f worldMousePos = window.mapPixelToCoords(Mouse::getPosition(window), tileView);
    Vector2i mouseTilePosition(worldMousePos.x / TILE_SIZE, worldMousePos.y / TILE_SIZE);


    if (m_tileScrollBox.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
        m_mouseEditorState = SELECT;
    }
    else {
        m_mouseEditorState = static_cast<MouseState>(m_lastState);

        if (m_selectorMenu.at(0)->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                m_selectorMenu.at(0)->setOutlineColor(Color::White);
                m_selectorMenu.at(0)->setOutlineThickness(5);
                m_mouseEditorState = SET_TILE;
                m_lastState = m_mouseEditorState;
            }

        }
        else if (m_selectorMenu.at(1)->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                m_selectorMenu.at(1)->setOutlineColor(Color::White);
                m_selectorMenu.at(1)->setOutlineThickness(5);
                m_mouseEditorState = DELETE_TILE;
                m_lastState = m_mouseEditorState;
            }
        }
        else if (m_selectorMenu.at(2)->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                m_selectorMenu.at(2)->setOutlineColor(Color::White);
                m_selectorMenu.at(2)->setOutlineThickness(5);
                m_mouseEditorState = SAVE_FILE;
                m_lastState = m_mouseEditorState;
                openFileExplorer();
                savelevel(m_currentLevel);
            }
        }

        else if (m_selectorMenu.at(3)->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                m_selectorMenu.at(3)->setOutlineColor(Color::White);
                m_selectorMenu.at(3)->setOutlineThickness(5);
                m_mouseEditorState = LOAD_FILE;
                m_lastState = m_mouseEditorState;
                openFileExplorer();
                if (!m_currentLevel.empty()) {
                    loadLevel(m_currentLevel);
                }
            }
        }
        else {
            for (auto& selectorMenu : m_selectorMenu) {
                if (!m_selectorMenu.empty() ) {
                    if (m_lastState != SELECT) {
                        if (selectorMenu != m_selectorMenu.at(m_lastState)) {
                            selectorMenu->setOutlineColor(Color::Transparent);
                            selectorMenu->setOutlineThickness(0);
                        }

                    }
                   
                }
            }
        }
        
    }
   

    if (Mouse::isButtonPressed(Mouse::Left) && find_if(m_selectorMenu.begin(), m_selectorMenu.end(), [&](const auto& button) {
        return button->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))); }) == m_selectorMenu.end()) 
    {
        int index = 0;
        switch (m_mouseEditorState)
        {
        case SELECT:
            
            for (auto& tileMenu : m_tilesScrollMenu) {
                if (tileMenu->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
                    tileMenu->setOutlineColor(Color::White);
                    tileMenu->setOutlineThickness(5);
                    if (tileMenu == m_tilesScrollMenu.at(index)) {
                        m_entityTile = static_cast<entityType>(index);
                    }
                }
                else {
                    tileMenu->setOutlineColor(Color::Transparent);
                    tileMenu->setOutlineThickness(0);
                }
                if (index < m_tilesScrollMenu.size()) {
                    index++;
                }
            }
            break;
        case DELETE_TILE:
            if (m_tiles.find({ mouseTilePosition.x, mouseTilePosition.y }) != m_tiles.end()) {

                m_tiles.erase({ mouseTilePosition.x, mouseTilePosition.y });


                m_tilesShape.erase(
                    remove_if(m_tilesShape.begin(), m_tilesShape.end(),
                        [&](const unique_ptr<RectangleShape>& rect) {
                            return rect->getPosition() ==
                                Vector2f(mouseTilePosition.x * TILE_SIZE,
                                    mouseTilePosition.y * TILE_SIZE);
                        }),
                    m_tilesShape.end());
            }
            break;

        case SET_TILE:
            if (m_tiles.find({ mouseTilePosition.x, mouseTilePosition.y }) == m_tiles.end() ||
                std::find_if(m_tiles.begin(), m_tiles.end(), [](const auto& tile) {
                    return tile.second == entityType::NOTYPE;
                    }) != m_tiles.end())
            {
                m_tiles[{mouseTilePosition.x, mouseTilePosition.y}] = m_entityTile;
                auto rect = make_unique<RectangleShape>();
                switch (m_entityTile)
                {
                case GOLEM:
                    tileSetter(move(rect), mouseTilePosition);
                    break;
                case PLAYER:
                    tileSetter(move(rect), mouseTilePosition);

                    break;
                case TILE:
                    tileSetter(move(rect), mouseTilePosition);
                    break;

                }
            }
            break;
        }
       
    }

    
    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        tileView.move(0, viewOffsetSpeed * deltaTime);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Q))
    {
        tileView.move(viewOffsetSpeed * deltaTime, 0);

    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        tileView.move(0, -viewOffsetSpeed * deltaTime);

    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        tileView.move(-viewOffsetSpeed *deltaTime, 0);
    }


    float scrollSpeed = 100000;
    float baseZoom = 1.0f;
    float zoomAmont = 0.3f  ;
    float minScrollY = 50; 
    float maxScrollY = window.getSize().y - m_tilesScrollMenu.back()->getSize().y - 50; 
    if (event.type == Event::MouseWheelScrolled) {

        switch (m_mouseEditorState)
        {

        case SELECT:
            if (event.mouseWheelScroll.delta > 0) {

                if (m_tilesScrollMenu.back()->getPosition().y >= minScrollY) {
                    for (auto& tilesButton : m_tilesScrollMenu) {
                        tilesButton->move(0, -scrollSpeed * deltaTime);
                    }
                }
                event.mouseWheelScroll.delta = 0;

            }
            else if (event.mouseWheelScroll.delta < 0) {
                if (m_tilesScrollMenu.front()->getPosition().y <= maxScrollY) {
                    for (auto& tilesButton : m_tilesScrollMenu) {
                        tilesButton->move(0, scrollSpeed * deltaTime);
                    }
                }
                event.mouseWheelScroll.delta = 0;
            }
            break;
        default:
            if (event.mouseWheelScroll.delta > 0) {
                baseZoom *= baseZoom - zoomAmont;
                event.mouseWheelScroll.delta = 0;
            }
            else if (event.mouseWheelScroll.delta < 0) {
                baseZoom *= baseZoom + zoomAmont;
                event.mouseWheelScroll.delta = 0;
            }
            break;
        }
    }
    tileView.zoom(baseZoom);
}

void LevelEditor::update()
{
}




void LevelEditor::draw(RenderWindow& window, View& tileView, View& Ui_view) {
    window.setView(tileView);
    window.clear();

    for (auto& tile : m_tilesShape) {
        window.draw(*tile);
    }

    window.setView(Ui_view);
    window.draw(m_tileScrollBox);

    for (auto& tileButton : m_tilesScrollMenu) {
        window.draw(*tileButton);
    }

    for (auto& menuButton : m_selectorMenu) {
        window.draw(*menuButton);
    }

    for (auto& text : m_selectorMenuTexts) {
        window.draw(*text);
    }
}




void LevelEditor::dropDownMenu(RenderWindow& window)
{
    const float buttonWidth = 50.f;
    const float buttonHeight = 50.f;
    const float spacing = 50.f;
    const float startX = 50.f;
    const float startY = 100.f;

    m_tileScrollBox.setSize(Vector2f(50.f, window.getSize().y));
    m_tileScrollBox.setPosition(50.f, 0.f);
    m_tileScrollBox.setFillColor(Color::Transparent);
    m_tileScrollBox.setOutlineColor(Color::Transparent);
    m_tileScrollBox.setOutlineThickness(5);






    float newY;
    if (!m_tilesScrollMenu.empty()) {
        const auto& lastButton = m_tilesScrollMenu.back();
        newY = lastButton->getPosition().y + lastButton->getSize().y + spacing;
    }
    else {
        newY = startY;
    }
    
    auto rect = std::make_unique<sf::RectangleShape>();
    rect->setSize(sf::Vector2f(buttonWidth, buttonHeight));
    rect->setPosition(startX, newY);
    //rect->setFillColor(Color::Transparent);
    if (!m_tileTextures.empty()) {
        rect->setTexture(m_tileTextures.at(m_textureId).get());
    }
    m_tilesScrollMenu.push_back(std::move(rect));
    if (m_textureId < m_tileTextures.size()) {
        m_textureId++;
    }
}

void LevelEditor::tileSetter(unique_ptr<RectangleShape> tile, Vector2i MousTilePos)
{

    tile->setSize(Vector2f(TILE_SIZE, TILE_SIZE));  
    tile->setPosition(Vector2f(MousTilePos.x * TILE_SIZE, MousTilePos.y * TILE_SIZE));  
    if (!m_tileTextures.empty()) {
        tile->setTexture(m_tileTextures.at(m_entityTile).get());
    }
    m_tilesShape.push_back(move(tile));

}

void LevelEditor::updateFile()
{

}

void LevelEditor::updateTiles() {
    m_tilesShape.clear();
    for (const auto& [pos, tileID] : m_tiles) {
        auto rect = make_unique<RectangleShape>();
        m_entityTile = static_cast<entityType>(tileID);
        tileSetter(move(rect), Vector2i(pos.first, pos.second));
    }
}


void LevelEditor::addSelectorButton(sf::Color color, const std::string& label) {
    const float buttonWidth = 50.f;
    const float buttonHeight = 30.f;
    const float spacing = 30.f;
    const float startX = 200.f;
    const float startY = 100.f;

    float newX;
    if (!m_selectorMenu.empty()) {
        const auto& lastButton = m_selectorMenu.back();
        newX = lastButton->getPosition().x + lastButton->getSize().x + spacing;
    }
    else {
        newX = startX;
    }

    // Création du bouton
    auto rect = std::make_unique<sf::RectangleShape>();
    rect->setSize(sf::Vector2f(buttonWidth, buttonHeight));
    rect->setPosition(newX, startY);
    rect->setFillColor(color);
    m_selectorMenu.push_back(std::move(rect));

    // Création du texte
    auto text = std::make_unique<sf::Text>();
    text->setFont(m_font);
    text->setString(label);
    text->setCharacterSize(20);
    text->setFillColor(sf::Color::Black);
    text->setPosition(newX + 5, startY + 5);
    m_selectorMenuTexts.push_back(std::move(text));
}