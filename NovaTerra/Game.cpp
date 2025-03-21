#include "Game.h"
#include "TextureLoader.h"

Background background("assets/parallaxe/bg.png", -50);

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "NovaTerra 1.0"),menu(window), menuState(MenuState::MENU),settingsMenu(window) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    night.setSize(sf::Vector2f(2000, 2000));
    night.setFillColor(sf::Color(0, 0, 0, 200));
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::processMenu() {
    Vector2i mousePos = Mouse::getPosition(window);
    int selected = menu.handleMouseClick(mousePos);

    cout << "Selected Menu Index: " << selected << endl;

    switch (selected) {
    case 0:
        cout << "Switching to PLAY mode!" << endl;
        menuState = MenuState::PLAY;
        break;
    case 1:
        cout << "Switching to SETTINGS mode!" << endl;
        menuState = MenuState::SETTINGS;
        break;
    case 2:
        cout << "Exiting game!" << endl;
        window.close();
        break;
    case 3:
        cout << "Switching to EDITOR mode!" << endl;
        menuState = MenuState::EDIT;
        break;
    default:
        break;
    }
}

void Game::processSettingsMenu() {
    Vector2i mousePos = Mouse::getPosition(window);
    int selected = settingsMenu.handleMouseClick(mousePos);

    switch (selected) {
    case 0:
        cout << "Ouverture du menu de réglages" << endl;
        break;
    case 1:
        cout << "Ouverture du menu du son" << endl;
        break;
    case 2:
        menuState = MenuState::MENU;
        break;
    default:
        break;
    }

}

void Game::run() {
    Clock clock;

    vector<shared_ptr<Entity>> vec;
    string image = "assets/map/map_tileset";
    loadertest.loadTexture(image, textureListTest);
    View view;
    view.zoom(0.65f);


    string mapFile = "../NovaTerra/assets/map/lobby.txt";

    Map map(mapFile, window);

    vec = map.generateTiles(textureListTest, vec);

    Cycle* cycle = new Cycle();

    shared_ptr<Player> playerPtr = nullptr;
    for (auto& entity : vec) {
        playerPtr = dynamic_pointer_cast<Player>(entity);
        if (playerPtr) break;
    }

    Scroll* scroll = new Scroll(WIDTH, HEIGHT);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::L)) {
                isMainMenu = false;
            }

            if (menuState == MenuState::MENU && event.type == Event::MouseButtonPressed) {
                processMenu();
            }
            else if (menuState == MenuState::SETTINGS && event.type == Event::MouseButtonPressed) {
                processSettingsMenu();
            }
        }
        float deltatime = clock.restart().asSeconds();

        window.clear();
        if (isMainMenu) {
            if (menuState == MenuState::MENU) {
                menu.draw();
            }
            else if (menuState == MenuState::PLAY) {
                isMainMenu = false;
            }
            else if (menuState == MenuState::SETTINGS) {
                settingsMenu.draw();
            }
            else if (menuState == MenuState::CREDITS) {
            }
            else if (menuState == MenuState::EXIT) {
                window.close();
            }
            window.display();
            continue;
        }

        background.draw(window);
        if (cycle->getState() == Cycle::State::Night) {
            window.draw(night);
        }
        for (auto& entity : vec) {
            playerPtr = dynamic_pointer_cast<Player>(entity);
            if (playerPtr) break;
        }
        for (auto entityvec : vec) {
            entityvec->update(deltatime, vec);
            if (Keyboard::isKeyPressed(Keyboard::O)) {
                entityvec->interact(*cycle, *playerPtr);
            }
            entityvec->draw(window);
            entityvec->update(deltatime, vec);
            if (entityvec->getID() == 1) {
                view.setCenter(entityvec->getSprite().getPosition().x +200,entityvec->getSprite().getPosition().y);
            }
        }
        window.setView(view);
        window.display();
    }
}