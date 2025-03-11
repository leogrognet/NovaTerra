#include "Game.h"
#include"Map.h"
Game::Game()
    : window(sf::VideoMode(1200, 900), "Test") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

Game::~Game() {
    std::cout << "Le jeu est détruit\n";
}

void Game::run() {
    Map* map = new Map("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        map->draw(window);
        window.display();
    }
}