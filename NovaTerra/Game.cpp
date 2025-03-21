
#include "Game.h"
#include "TextureLoader.h"

//TextureLoader textureloader;

Background background("assets/parallaxe/bg.png", -50);

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "NovaTerra 1.0"), menuState(MenuState::MENU), menu(window), settingsMenu(window), menuPlay(window) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
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
        menuState = MenuState::MENU_PLAY;
        break;
    case 1:
        cout << "Switching to SETTINGS mode!" << endl;
        menuState = MenuState::SETTINGS;
        break;
    case 2:
        cout << "Exiting game!" << endl;
        window.close();
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
        menuState = MenuState::EXIT;
        break;
    default:
        break;
    }

}

void Game::processPlayMenu() {
    Vector2i mousePos = Mouse::getPosition(window);
    int selected = menuPlay.handleMouseClick(mousePos);

    switch (selected) {
    case 0:
        menuState = MenuState::PLAY;
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
    vec.push_back(make_shared<Plateform>(100, 800, Vector2f(10, 1), true, true, textureListTest));
    vec.push_back(make_shared<Plateform>(300, 400, Vector2f(5, 5), true, true, textureListTest));
    vec.push_back(make_shared<Bounce>(700, 700, Vector2f(1, 1), true, true));
    vec.push_back(make_shared<MovePlat>(100, 400, Vector2f(1, 1), true, true));
    vec.push_back(make_shared<Vine>(100, 600, 50, 50, true, false, textureListTest));

    vec.push_back(make_shared<GolemEnemy>(500, 700, false, false));

    vec.push_back(make_shared<Player>(vec, 100, 600, false, true));

    Map* map = new Map("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });

    Scroll* scroll = new Scroll(WIDTH, HEIGHT);
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (menuState == MenuState::MENU && event.type == Event::MouseButtonPressed) {
                processMenu();
            }
            else if (menuState == MenuState::SETTINGS && event.type == Event::MouseButtonPressed) {
                processSettingsMenu();
            }
            else if (menuState == MenuState::MENU_PLAY && event.type == Event::MouseButtonPressed) {
                processPlayMenu();
            }
        }

        window.clear();

        switch (menuState) {
        case MenuState::MENU:
            menu.draw();
            break;
        case MenuState::MENU_PLAY:
            menuPlay.draw();
            break;
        case MenuState::PLAY:
            float deltaTime = clock.restart().asSeconds();
            scroll->applyView(window);
            background.update(deltaTime);
            background.draw(window);
            map->draw(window);

            for (auto& entity : vec) {
                entity->update(deltaTime, vec);
                entity->draw(window);
            }
            break;
        case MenuState::SETTINGS:
            settingsMenu.draw();
            break;
        case MenuState::CREDITS:
            // Afficher les crédits ici
            break;
        case MenuState::EXIT:
            window.close();
            break;
        default:
            break;
        }

        window.display();
    }

    delete map;
    delete scroll;

}
