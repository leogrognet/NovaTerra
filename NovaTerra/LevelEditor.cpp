#include "LevelEditor.h"



#pragma region 1. Constructeurs
LevelEditor::LevelEditor(RenderWindow& window)
{
    m_subMenu = false;
    m_mouseEditorState = SELECT;
    viewOffsetSpeed = 500.f;

    if (!m_font.loadFromFile("assets/font/default.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police" << std::endl;
    }
    m_textureId = 0;
    string map_tileSet = "assets\\map\\map_tileset";
    loadTexture.loadTexture(map_tileSet, m_FileTileTextures);


    
    
    m_SperatedTileTextures_1 = getNonTransparentTiles(128, 128, 0);
    m_SperatedTileTextures_2 = getNonTransparentTiles(128, 128, 1);
    if (!m_FileTileTextures.empty()) {
        m_FileTileTextures.insert(m_FileTileTextures.begin(), std::move((m_FileTileTextures.back())));
        m_SperatedTileTextures_1.insert(m_SperatedTileTextures_1.begin(), m_FileTileTextures.front());

        m_SperatedTileTextures_2.insert(m_SperatedTileTextures_2.begin(), m_SperatedTileTextures_1.front());
    }

    
    addSelectorButton(Color::Blue, "Set");
    addSelectorButton(Color::Red, "Delete");
    addSelectorButton(Color::Green, "Save");
    addSelectorButton(Color::Yellow, "Load");

    m_allTextureVector.push_back(m_FileTileTextures);
    m_allTextureVector.push_back(m_SperatedTileTextures_1);
    m_allTextureVector.push_back(m_SperatedTileTextures_2);
    dropDownMenu(window, m_TilesBordersMenu, m_TilesScrollMenu, m_allTextureVector.at(0));

    
}
#pragma endregion

#pragma region 2. Méthodes de gestion des niveaux

void LevelEditor::loadLevel(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de charger le fichier " << filename << std::endl;
        return;
    }

    m_tiles.clear();
    m_tilesShape.clear(); 

    int x, y, tileID, textureIndex;
    while (file >> x >> y >> tileID >> textureIndex) {
        m_tiles[{x, y}] = { tileID, textureIndex };
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
    for (auto& [pos, tileData] : m_tiles) {
        textFile << pos.first << " " << pos.second << " " << tileData.first<< " " << tileData.second << endl;
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
#pragma endregion



#pragma region 3. Méthodes dinterface utilisateur

void LevelEditor::dropDownMenu(RenderWindow& window, vector<shared_ptr<RectangleShape>>& tileBordersMenu, vector<shared_ptr<Sprite>>& tilesScrollMenu, vector<shared_ptr<Texture>>& tileTextures)
{
    tileBordersMenu.clear();
    tilesScrollMenu.clear();
    const float spacing = 50.f;
    const float startX = 50.f;
    const float sizeX = 50.f;
    const float sizeY = 50.f;
    const float startY = 10.f;

    m_tileScrollBox.setSize(Vector2f(50.f, window.getSize().y));
    m_tileScrollBox.setPosition(50.f, 0.f);
    m_tileScrollBox.setFillColor(Color::Transparent);
    m_tileScrollBox.setOutlineColor(Color::Transparent);
    m_tileScrollBox.setOutlineThickness(5);

    float newY;
    for (auto& texturePtr : tileTextures) {
        if (!tilesScrollMenu.empty()) {
            const auto& lastButton = tilesScrollMenu.back();
            newY = lastButton->getPosition().y + lastButton->getGlobalBounds().height + spacing;
        }
        else {
            newY = startY;
        }

        if (texturePtr == nullptr) {
            std::cerr << "Erreur : texturePtr est nullptr !" << std::endl;
            continue;
        }

        auto sprite = std::make_shared<sf::Sprite>();

        sprite->setTexture(*texturePtr);

        sprite->setPosition(startX, newY);

        float spriteWidth = sprite->getGlobalBounds().width;
        float spriteHeight = sprite->getGlobalBounds().height;

        float scaleX = sizeX / spriteWidth;
        float scaleY = sizeY / spriteHeight;

        sprite->setScale(scaleX, scaleY);
        auto border = std::make_shared<sf::RectangleShape>();

        sf::Vector2u textureSize = texturePtr->getSize();
        border->setSize(sf::Vector2f(sizeX, sizeY));

        border->setPosition(startX, newY);

        border->setFillColor(sf::Color::Transparent);  

        tileBordersMenu.push_back(border);  
        tilesScrollMenu.push_back(sprite);  
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
    auto rect = std::make_shared<sf::RectangleShape>();
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
#pragma endregion


#pragma region 4. Méthodes de gestion des entrées

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
                if (!m_selectorMenu.empty()) {
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
            
                switch (m_mouseEditorState)
                {
                case SELECT:
                    
                    switch (m_tileState)
                    {
                    case BIOME_1:
                        subMenuHandler(m_TilesBordersMenu, window);
                        //dropDownMenu(window, m_TilesBordersMenu, m_TilesScrollMenu, m_allTextureVector.at(m_tileState));
                        break;
                    case BIOME_2:
                        subMenuHandler(m_TilesBordersMenu, window);
                       // dropDownMenu(window, m_TilesBordersMenu, m_TilesScrollMenu, m_allTextureVector.at(m_tileState));
                        break;
                    case BIOME_3:
                        break;
                    default:
                        for (auto& tileMenu : m_TilesBordersMenu) {
                            if (tileMenu->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
                                tileMenu->setOutlineColor(Color::White);
                                tileMenu->setOutlineThickness(5);
                                int position = std::distance(m_TilesBordersMenu.begin(), std::find(m_TilesBordersMenu.begin(), m_TilesBordersMenu.end(), tileMenu));
                                if (position > 0 && position < 3) {

                                    m_entityTile = static_cast<entityType>(position);
                                    m_tileState = static_cast<tileState>(position);
                                    if (position == 1) {
                                        m_entityTile = static_cast<entityType>(0);
                                    }
                                    m_subMenu = true;
                                    m_textureId = position;
                                }
                                else {
                                    m_entityTile = static_cast<entityType>(position);
                                    m_subMenu = false;
                                    m_textureId = position;
                                }

                            }
                            else {
                                tileMenu->setOutlineColor(Color::Transparent);
                                tileMenu->setOutlineThickness(0);
                            }
                        }
                        if (m_subMenu == true) {
                            dropDownMenu(window, m_TilesBordersMenu, m_TilesScrollMenu, m_allTextureVector.at(m_tileState));
                        }
                        break;
                    }

                    break;
                case DELETE_TILE:
                    if (m_tiles.find({ mouseTilePosition.x, mouseTilePosition.y }) != m_tiles.end()) {

                        m_tiles.erase({ mouseTilePosition.x, mouseTilePosition.y });


                        m_tilesShape.erase(
                            remove_if(m_tilesShape.begin(), m_tilesShape.end(),
                                [&](const shared_ptr<RectangleShape>& rect) {
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
                            return tile.second.first == entityType::NOTYPE;
                            }) != m_tiles.end())
                    {
                        if (m_tileState >0 && m_tileState < 3) {
                            m_tiles[{mouseTilePosition.x, mouseTilePosition.y}] = { m_tileState, m_textureId };
                        }
                        else {
                            m_tiles[{mouseTilePosition.x, mouseTilePosition.y}] = { m_entityTile, 0 };
                        }
                        auto rect = make_unique<RectangleShape>();
                        if (m_subMenu) {
                            tileSetter(move(rect), mouseTilePosition,  m_tileState,m_textureId);
                        }
                        else {
                            tileSetter(move(rect), mouseTilePosition,0, m_entityTile);
                        }
                    }
                    break;
                }
            }

        
    


    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        tileView.move(0, viewOffsetSpeed * deltaTime);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Q))
    {
        tileView.move(viewOffsetSpeed * deltaTime, 0);

    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        tileView.move(0, -viewOffsetSpeed * deltaTime);

    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        tileView.move(-viewOffsetSpeed * deltaTime, 0);
    }


    float scrollSpeed = 100000;
    float baseZoom = 1.0f;
    float zoomAmont = 0.3f;
    float minScrollY = 10;
    float maxScrollY = window.getSize().y - m_TilesScrollMenu.back()->getGlobalBounds().height - 10;
    if (event.type == Event::MouseWheelScrolled) {

        switch (m_mouseEditorState)
        {

        case SELECT:

            handleMenuScroll(event, deltaTime, m_TilesScrollMenu, m_TilesBordersMenu, scrollSpeed, minScrollY, maxScrollY);
            
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


void LevelEditor::handleMenuScroll(Event& event, float deltaTime,
    std::vector<std::shared_ptr<Sprite>>& scrollMenu,
    std::vector<std::shared_ptr<RectangleShape>>& bordersMenu,
    float scrollSpeed, float minScrollY, float maxScrollY)
{
    if (event.mouseWheelScroll.delta > 0) {
        // Défilement vers le haut
        if (scrollMenu.back()->getPosition().y >= maxScrollY) {
            for (auto& tilesButton : scrollMenu) {
                tilesButton->move(0, -scrollSpeed * deltaTime);
            }
            for (auto& tilesButton : bordersMenu) {
                tilesButton->move(0, -scrollSpeed * deltaTime);
            }
        }
    }
    else if (event.mouseWheelScroll.delta < 0) {
        // Défilement vers le bas
        if (scrollMenu.front()->getPosition().y <= minScrollY) {
            for (auto& tilesButton : scrollMenu) {
                tilesButton->move(0, scrollSpeed * deltaTime);
            }
            for (auto& tilesButton : bordersMenu) {
                tilesButton->move(0, scrollSpeed * deltaTime);
            }
        }
    }

    // Réinitialisation du delta pour éviter des problèmes futurs
    event.mouseWheelScroll.delta = 0;
}

#pragma endregion


#pragma region 5. Méthodes de gestion des textures

bool LevelEditor::isTileTransparent(const sf::Texture& texture, const sf::IntRect& rect)
{
    sf::Image image = texture.copyToImage();

    // Vérification pour éviter un dépassement des limites de l'image
    int imgWidth = image.getSize().x;
    int imgHeight = image.getSize().y;

    // Nombre total de pixels dans le rectangle
    int totalPixels = rect.width * rect.height;
    int nonTransparentPixels = 0;

    for (int y = rect.top; y < std::min(rect.top + rect.height, imgHeight); ++y) {
        for (int x = rect.left; x < std::min(rect.left + rect.width, imgWidth); ++x) {
            sf::Color pixelColor = image.getPixel(x, y); 
            if (pixelColor.a > 10) {  // Prendre en compte les pixels quasi-transparents
                nonTransparentPixels++;
            }
        }
    }

    // Vérifier si plus de 50% des pixels sont opaques
    return nonTransparentPixels < (totalPixels / 2);
}

vector<shared_ptr<Texture>> LevelEditor::getNonTransparentTiles(int tileWidth, int tileHeight, int index)
{

    vector<shared_ptr<Texture>> tiles;
    int textureWidth = m_FileTileTextures.at(index).get()->getSize().x;
    int textureHeight = m_FileTileTextures.at(index).get()->getSize().y;

    for (int y = 0; y < textureHeight; y += tileHeight) {
        for (int x = 0; x < textureWidth; x += tileWidth) {
            sf::IntRect rect(x, y, tileWidth, tileHeight);

            if (!isTileTransparent(*m_FileTileTextures.at(index).get(), rect)) {
                auto tileTexture = std::make_shared<sf::Texture>();
                tileTexture->loadFromImage(m_FileTileTextures.at(index)->copyToImage(), rect);
                tiles.push_back(tileTexture); 
            }
        }
    }

    return tiles;
}
#pragma endregion


#pragma region 6. Méthodes Update

void LevelEditor::update(RenderWindow& window, View& tileView, View& Ui_view, Event& event, float deltaTime)
{

    handleInput(window, tileView, event, deltaTime);
    window.clear();
    draw(window, tileView, Ui_view);
    window.display();
}

void LevelEditor::draw(RenderWindow& window, View& tileView, View& Ui_view) {
    window.setView(tileView);
    window.clear();

    for (auto& tile : m_tilesShape) {
        window.draw(*tile);
    }

    window.setView(Ui_view);
    window.draw(m_tileScrollBox);


    for (auto& tileButton : m_TilesBordersMenu) {
        window.draw(*tileButton);
    }
    for (auto& tileButton : m_TilesScrollMenu) {
        window.draw(*tileButton);
    }

    for (auto& menuButton : m_selectorMenu) {
        window.draw(*menuButton);
    }

    for (auto& text : m_selectorMenuTexts) {
        window.draw(*text);
    }
}

void LevelEditor::updateTiles() {
    m_tilesShape.clear();
    for (const auto& [pos, tileID] : m_tiles) {
        auto rect = make_unique<RectangleShape>();
        m_entityTile = static_cast<entityType>(tileID.first);
        m_tileState = static_cast<tileState>(tileID.first);
        m_textureId = tileID.second;
        if (tileID.first > 0 && tileID.first < 3) {
            tileSetter(move(rect), Vector2i(pos.first, pos.second), tileID.first, tileID.second);
        }
        else {
            tileSetter(move(rect), Vector2i(pos.first, pos.second),0, tileID.first);
        }
    }
}

void LevelEditor::tileSetter(shared_ptr<RectangleShape> tile, Vector2i MousTilePos,int vectorIndex, int textureIndex )
{

    tile->setSize(Vector2f(TILE_SIZE, TILE_SIZE));
    tile->setPosition(Vector2f(MousTilePos.x * TILE_SIZE, MousTilePos.y * TILE_SIZE));
    if (!m_allTextureVector.at(vectorIndex).empty()) {
        tile->setTexture(m_allTextureVector.at(vectorIndex).at(textureIndex).get());
    }
    m_tilesShape.push_back(move(tile));

}
#pragma endregion



#pragma region 7. Fonction de Menu de Tiles
void LevelEditor::subMenuHandler(std::vector<std::shared_ptr<RectangleShape>>& tileMenu, RenderWindow& window) {
    for (auto& tileMenuPtr : tileMenu) {
        
        if (tileMenuPtr->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
            int position = std::distance(tileMenu.begin(), std::find(tileMenu.begin(), tileMenu.end(), tileMenuPtr));
            tileMenuPtr->setOutlineColor(Color::White);
            tileMenuPtr->setOutlineThickness(5);
                if (position == 0) {  
                    m_tileState = NORMAL_TILE;
                }
                else {
                    m_textureId = position;
                }

        }
        else {
            tileMenuPtr->setOutlineColor(Color::Transparent);
            tileMenuPtr->setOutlineThickness(0);
        }
    }
    if (m_tileState == NORMAL_TILE) {
        dropDownMenu(window, m_TilesBordersMenu, m_TilesScrollMenu, m_allTextureVector.at(m_tileState));
    }
}


#pragma endregion
