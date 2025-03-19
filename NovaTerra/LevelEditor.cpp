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
    m_vectorIndex = 0;


    m_textureId = 0;
    string map_tileSet = "assets\\map\\map_tileset";
    loadTexture.loadTexture(map_tileSet, m_FileTileTextures);

    
    std::cout << "Nombre de textures : " << m_FileTileTextures.size() << std::endl;

    
    
    m_SperatedTileTextures_1 = getNonTransparentTiles(128, 128, 0);
    m_SperatedTileTextures_2 = getNonTransparentTiles(485, 120, 2);
    if (!m_FileTileTextures.empty()) {
        auto firstElement = m_FileTileTextures.front(); 

        m_SperatedTileTextures_1.insert(m_SperatedTileTextures_1.begin(), std::move(firstElement));

        m_SperatedTileTextures_2.insert(m_SperatedTileTextures_2.begin(), m_FileTileTextures.front()); // Copie du shared_ptr
    }

    dropDownMenu(window, m_FileTilesBordersMenu, m_FileTilesScrollMenu, m_FileTileTextures);



    dropDownMenu(window, m_SeperatedTilesBordersMenu_1, m_SeperatedTilesScrollMenu_1, m_SperatedTileTextures_1);
    dropDownMenu(window, m_SeperatedTilesBordersMenu_2, m_SeperatedTilesScrollMenu_2, m_SperatedTileTextures_2);
    
    addSelectorButton(Color::Blue, "Set");
    addSelectorButton(Color::Red, "Delete");
    addSelectorButton(Color::Green, "Save");
    addSelectorButton(Color::Yellow, "Load");

    m_ActualTileTexture = m_SperatedTileTextures_1;
    m_SeperatedTilesBordersMenuType = m_SeperatedTilesBordersMenu_1;
    m_SeperatedTilesScrollMenuType = m_SeperatedTilesScrollMenu_1;
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
        textFile << pos.first << " " << pos.second << " " << tileData.first<<tileData.second << endl;
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
    const float spacing = 50.f;
    const float startX = 50.f;
    const float sizeX = 50.f;
    const float sizeY = 50.f;
    const float startY = 100.f;

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
            cout << "vide";
            newY = startY;
        }

        // Vérification de la validité de texturePtr
        if (texturePtr == nullptr) {
            std::cerr << "Erreur : texturePtr est nullptr !" << std::endl;
            continue;  // Passer à l'itération suivante si la texture est invalide
        }

        // Créer un sprite
        auto sprite = std::make_shared<sf::Sprite>();

        // Assigner la texture au sprite
        sprite->setTexture(*texturePtr);

        // Positionner le sprite
        sprite->setPosition(startX, newY);

        float spriteWidth = sprite->getGlobalBounds().width;
        float spriteHeight = sprite->getGlobalBounds().height;

        // Calculer le facteur de mise à l'échelle
        float scaleX = sizeX / spriteWidth;
        float scaleY = sizeY / spriteHeight;

        sprite->setScale(scaleX, scaleY);
        // Créer un rectangle pour la bordure
        auto border = std::make_shared<sf::RectangleShape>();

        // Définir la taille du rectangle comme celle du sprite
        sf::Vector2u textureSize = texturePtr->getSize();
        border->setSize(sf::Vector2f(sizeX, sizeY));

        // Définir la position de la bordure (identique à celle du sprite)
        border->setPosition(startX, newY);

        // Définir la couleur du contour
        border->setFillColor(sf::Color::Transparent);  // Remplissage transparent

        // Ajouter le sprite et la bordure aux listes
        tileBordersMenu.push_back(border);  // Ajouter la bordure
        tilesScrollMenu.push_back(sprite);  // Ajouter ensuite le sprite
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
    timeClicked += deltaTime;
    if (timeClicked > 0.1f) {
        timeClicked = 0;
        if (Mouse::isButtonPressed(Mouse::Left) && find_if(m_selectorMenu.begin(), m_selectorMenu.end(), [&](const auto& button) {
            return button->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))); }) == m_selectorMenu.end())
        {
            switch (m_mouseEditorState)
            {
            case SELECT:
                if (!m_subMenu) {
                   m_vectorIndex = 0;
                    for (auto& tileMenu : m_FileTilesBordersMenu) {
                        if (tileMenu->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
                            tileMenu->setOutlineColor(Color::White);
                            tileMenu->setOutlineThickness(5);
                            if (tileMenu == m_FileTilesBordersMenu.at(m_vectorIndex)) {
                                if (m_vectorIndex < 3) {
                                    m_entityTile = static_cast<entityType>(m_vectorIndex);
                                }
                                if (m_vectorIndex < 3) {
                                    m_tileState = static_cast<tileState>(m_vectorIndex);
                                }
                                m_subMenu = true;
                                m_textureId = m_vectorIndex;
                            }
                        }
                        else {
                            tileMenu->setOutlineColor(Color::Transparent);
                            tileMenu->setOutlineThickness(0);
                        }
                        if (m_vectorIndex < m_FileTilesScrollMenu.size()) {
                            m_vectorIndex++;
                        }
                    }
                }
                else if (m_subMenu && m_tileState == 0) {
                    m_vectorIndex = 1;
                    subMenuHandler(m_SeperatedTilesBordersMenuType, window, m_vectorIndex);
                }
                else if (m_subMenu && m_tileState == 1) {
                    m_vectorIndex = 1;
                    subMenuHandler(m_SeperatedTilesBordersMenuType, window, m_vectorIndex);
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
                    m_tiles[{mouseTilePosition.x, mouseTilePosition.y}] = { m_entityTile, m_textureType };
                    auto rect = make_unique<RectangleShape>();
                    cout << "Index" << m_textureId << m_ActualTileTexture.size() << endl;
                    tileSetter(move(rect), mouseTilePosition, m_textureId);
                }
                break;
            }

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
    float minScrollY = 50;
    float maxScrollY = window.getSize().y - m_FileTilesScrollMenu.back()->getGlobalBounds().height - 50;
    if (event.type == Event::MouseWheelScrolled) {

        switch (m_mouseEditorState)
        {

        case SELECT:
            if (event.mouseWheelScroll.delta > 0) {

                if (m_FileTilesScrollMenu.back()->getPosition().y >= maxScrollY) {
                    for (auto& tilesButton : m_FileTilesScrollMenu) {
                        tilesButton->move(0, -scrollSpeed * deltaTime);
                    }
                    for (auto& tilesButton : m_FileTilesBordersMenu) {
                        tilesButton->move(0, -scrollSpeed * deltaTime);
                    }
                }
                event.mouseWheelScroll.delta = 0;

            }
            else if (event.mouseWheelScroll.delta < 0) {
                if (m_FileTilesScrollMenu.front()->getPosition().y <= minScrollY) {
                    for (auto& tilesButton : m_FileTilesScrollMenu) {
                        tilesButton->move(0, scrollSpeed * deltaTime);
                    }
                    for (auto& tilesButton : m_FileTilesBordersMenu) {
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
#pragma endregion


#pragma region 5. Méthodes de gestion des textures

bool LevelEditor::isTileTransparent(const Texture& texture, const IntRect& rect)
{
    Image image = texture.copyToImage();

    // Nombre total de pixels dans le rectangle
    int totalPixels = rect.width * rect.height;
    int nonTransparentPixels = 0;

    for (int y = rect.top; y < rect.top + rect.height; ++y) {
        for (int x = rect.left; x < rect.left + rect.width; ++x) {
            sf::Color pixelColor = image.getPixel(x, y);
            if (pixelColor.a > 0) {  // Si le pixel est non transparent
                nonTransparentPixels++;
            }
        }
    }


    // Vérifier si le nombre de pixels non transparents est supérieur à la moitié du total
    return nonTransparentPixels < totalPixels / 2;
}

vector<shared_ptr<Texture>> LevelEditor::getNonTransparentTiles( int tileWidth, int tileHeight, int index)
{


    vector<shared_ptr<Texture>> tiles;
    int textureWidth = m_FileTileTextures.at(index).get()->getSize().x;
    int textureHeight = m_FileTileTextures.at(index).get()->getSize().y;

    // Découpe toutes les tuiles non transparentes et les ajoute
    for (int y = 0; y < textureHeight; y += tileHeight) {
        for (int x = 0; x < textureWidth; x += tileWidth) {
            sf::IntRect rect(x, y, tileWidth, tileHeight);

            // Vérifie si la tuile n'est pas transparente
            if (!isTileTransparent(*m_FileTileTextures.at(index).get(), rect)) {
                // Crée une nouvelle texture découpée et l'ajoute
                auto tileTexture = std::make_shared<sf::Texture>();
                tileTexture->loadFromImage(m_FileTileTextures.at(index)->copyToImage(), rect);
                tiles.push_back(tileTexture); // Ajoute la texture découpée
            }
        }
    }
    return tiles;
}
#pragma endregion



#pragma region 6. Méthodes Update

void LevelEditor::update(RenderWindow& window, View& tileView, View& Ui_view, Event& event, float deltaTime)
{

    if (m_FileTilesScrollMenu.empty()) {
        return;
    }
    switch (m_tileState)
    {
    case BIOME_1:
        m_ActualTileTexture = m_SperatedTileTextures_1;
        m_SeperatedTilesBordersMenuType = m_SeperatedTilesBordersMenu_1;
        m_SeperatedTilesScrollMenuType = m_SeperatedTilesScrollMenu_1;
        break;
    case BIOME_2:
        m_ActualTileTexture = m_SperatedTileTextures_2;
        m_SeperatedTilesBordersMenuType = m_SeperatedTilesBordersMenu_2;
        m_SeperatedTilesScrollMenuType = m_SeperatedTilesScrollMenu_2;

        break;
    case BIOME_3:
        break;
    default:
        break;
    }


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

    if (!m_subMenu) {
        for (auto& tileButton : m_FileTilesBordersMenu) {
            window.draw(*tileButton);
        }
        for (auto& tileButton : m_FileTilesScrollMenu) {
            window.draw(*tileButton);
        }
    }
    else if (m_subMenu) {
        for (auto& tileButton : m_SeperatedTilesBordersMenuType) {
            window.draw(*tileButton);
        }
        for (auto& tileButton : m_SeperatedTilesScrollMenuType) {
            window.draw(*tileButton);
        }
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
        tileSetter(move(rect), Vector2i(pos.first, pos.second), tileID.second);
    }
}

void LevelEditor::tileSetter(shared_ptr<RectangleShape> tile, Vector2i MousTilePos, int textureIndex)
{

    tile->setSize(Vector2f(TILE_SIZE, TILE_SIZE));
    tile->setPosition(Vector2f(MousTilePos.x * TILE_SIZE, MousTilePos.y * TILE_SIZE));
    if (!m_ActualTileTexture.empty()) {
        tile->setTexture(m_ActualTileTexture.at(textureIndex).get());
    }
    m_tilesShape.push_back(move(tile));

}
#pragma endregion



#pragma region 7. Fonction de Menu de Tiles
void LevelEditor::subMenuHandler(std::vector<std::shared_ptr<RectangleShape>>& tileMenu, RenderWindow& window, int index) {
    for (auto& tileMenuPtr : tileMenu) {

        if (tileMenuPtr->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
            // Si la souris est au-dessus de l'élément du menu
            tileMenuPtr->setOutlineColor(Color::White);
            tileMenuPtr->setOutlineThickness(5);

            if (tileMenuPtr == tileMenu.at(0)) {
                m_subMenu = false;
                m_textureId = index;
            }
            if (tileMenuPtr == tileMenu.at(index) && index !=0) {
                m_textureId = index;
            }
        }
        else {
            // Sinon, on réinitialise l'apparence de l'élément
            tileMenuPtr->setOutlineColor(Color::Transparent);
            tileMenuPtr->setOutlineThickness(0);
        }
        if (m_vectorIndex < m_ActualTileTexture.size()) {
            cout << "Index" << m_textureId << m_ActualTileTexture.size() << endl;

            m_vectorIndex++;
        }
    }
}

#pragma endregion
