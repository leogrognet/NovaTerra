#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
    m_mouseEditorState = SELECT;
    m_lastState = DELETE_TILE;
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

    if (std::find_if(m_tilesMenu.begin(), m_tilesMenu.end(), [&](const auto& tileMenu) {
        return tileMenu->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)));
        }) != m_tilesMenu.end()) {
        m_mouseEditorState = SELECT;
    }
    else {
        m_mouseEditorState =  m_lastState;;
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
        
    }
   

    if (Mouse::isButtonPressed(Mouse::Left)) {
        switch (m_mouseEditorState)
        {
        case SELECT:
            for (auto& tileMenu : m_tilesMenu) {
                if (tileMenu->getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
                    tileMenu->setOutlineColor(Color::White); 
                    tileMenu->setOutlineThickness(5);
                }
                else {
                    tileMenu->setOutlineColor(Color::Transparent); 
                    tileMenu->setOutlineThickness(0);
                }
            }
            break;
        case DELETE_TILE:
            if (m_tiles.find({ mouseTilePosition.x, mouseTilePosition.y }) != m_tiles.end()) {
                m_tiles.erase({ mouseTilePosition.x, mouseTilePosition.y });
            }
            break;

        case SET_TILE:
            m_tiles[{mouseTilePosition.x, mouseTilePosition.y}] = m_entityTile;
            break;
        }
    }

    float scrollSpeed = 100000;
    float zoomFactor = 0.8f;
    float minScrollY = 50; 
    float maxScrollY = window.getSize().y - m_tilesMenu.back()->getSize().y - 50; 
    cout << m_mouseEditorState << endl;
    if (event.type == Event::MouseWheelScrolled) {
        switch (m_mouseEditorState)
        {

        case SELECT:
            if (event.mouseWheelScroll.delta > 0) {

                if (m_tilesMenu.back()->getPosition().y >= minScrollY ) {
                    for (auto& tilesButton : m_tilesMenu) {
                        tilesButton->move(0, -scrollSpeed * deltaTime);
                    }
                }
                event.mouseWheelScroll.delta = 0;

            }
            else if (event.mouseWheelScroll.delta < 0) {
                if ( m_tilesMenu.front()->getPosition().y <= maxScrollY) {
                    for (auto& tilesButton : m_tilesMenu) {
                        tilesButton->move(0, scrollSpeed * deltaTime);
                    }
                }
                event.mouseWheelScroll.delta = 0;
            }
            break;
        case DELETE_TILE:
            if (event.mouseWheelScroll.delta > 0) {
                //zoomFactor *= 0.9f;
                //for (auto& tilesButton : m_tilesMenu) {
                //    Vector2f initialSize = tilesButton->getSize();
                //    tilesButton->setSize(Vector2f(initialSize.x, initialSize.y) * zoomFactor);
                //    tilesButton->setPosition(Vector2f(view.getCenter().x - tilesButton->getLocalBounds().width / 2,
                //        view.getCenter().y - tilesButton->getLocalBounds().height / 2));
                //}
            }
            else if (event.mouseWheelScroll.delta < 0) {
                //zoomFactor *= 1.1f;
                //for (auto& tilesButton : m_tilesMenu) {
                //    Vector2f initialSize = tilesButton->getSize();
                //    tilesButton->setSize(Vector2f(initialSize.x, initialSize.y) * zoomFactor);
                //    tilesButton->setPosition(Vector2f(view.getCenter().x - tilesButton->getLocalBounds().width / 2,
                //        view.getCenter().y - tilesButton->getLocalBounds().height / 2));
                //}
            }
            view.setSize(window.getSize().x * zoomFactor, window.getSize().y * zoomFactor);
            break;
        case SET_TILE:
            if (event.mouseWheelScroll.delta > 0) {
                //zoomFactor *= 0.9f;
                //for (auto& tilesButton : m_tilesMenu) {
                //    Vector2f initialSize = tilesButton->getSize();
                //    tilesButton->setSize(Vector2f(initialSize.x, initialSize.y) * zoomFactor);
                //    tilesButton->setPosition(Vector2f(view.getCenter().x - tilesButton->getLocalBounds().width / 2,
                //        view.getCenter().y - tilesButton->getLocalBounds().height / 2));
                //}
            }
            else if (event.mouseWheelScroll.delta < 0) {
               //zoomFactor *= 1.1f;
               //for (auto& tilesButton : m_tilesMenu) {
               //    Vector2f initialSize = tilesButton->getSize();
               //    tilesButton->setSize(Vector2f(initialSize.x, initialSize.y) * zoomFactor);
               //    tilesButton->setPosition(Vector2f(view.getCenter().x - tilesButton->getLocalBounds().width / 2,
               //        view.getCenter().y - tilesButton->getLocalBounds().height / 2));
               //}
            }
            view.setSize(window.getSize().x * zoomFactor, window.getSize().y * zoomFactor);
            break;
        }
    }
}

void LevelEditor::update()
{
}

void LevelEditor::draw(RenderWindow& window)
{

    // Dessiner les tiles du niveau
    for (auto& tile : m_tilesShape) {
        window.draw(*tile);
    }

    // Dessiner le menu
    for (auto& tileButton : m_tilesMenu) {
        window.draw(*tileButton);
    }
    for (auto& menuButton : m_selectorMenu) {
        window.draw(*menuButton);
    }
}




void LevelEditor::dropDownMenu(RenderWindow& window)
{
    // Créer des boutons avec une taille et une position
    auto rect1 = make_unique<RectangleShape>();
    rect1->setSize(Vector2f(50.f, 50.f));  // Taille du rectangle
    rect1->setPosition(50.f, 100.f);  // Position du rectangle
    rect1->setFillColor(Color::Blue);
    m_tilesMenu.push_back(move(rect1));

    auto rect2 = make_unique<RectangleShape>();
    rect2->setSize(Vector2f(50.f, 50.f));  // Taille du rectangle
    rect2->setPosition(50.f, 200.f);  // Position du rectangle
    rect2->setFillColor(Color::Red);

    m_tilesMenu.push_back(move(rect2));

    auto rect3 = make_unique<RectangleShape>();
    rect3->setSize(Vector2f(50.f, 50.f));  // Taille du rectangle
    rect3->setPosition(50.f, 300.f);  // Position du rectangle
    rect3->setFillColor(Color::Green);

    m_tilesMenu.push_back(move(rect3));
}

void LevelEditor::updateTiles()
{
}

void LevelEditor::selectButtonMenu(RenderWindow& window)
{
    auto rect1 = make_unique<RectangleShape>();
    rect1->setSize(Vector2f(50.f, 30.f));  // Taille du rectangle
    rect1->setPosition(200.f, 100.f);  // Position du rectangle
    rect1->setFillColor(Color::Blue);
    m_selectorMenu.push_back(move(rect1));

    auto rect2 = make_unique<RectangleShape>();
    rect2->setSize(Vector2f(50.f, 30.f));  // Taille du rectangle
    rect2->setPosition(300.f, 100.f);  // Position du rectangle
    rect2->setFillColor(Color::Red);
    m_selectorMenu.push_back(move(rect2));
}

