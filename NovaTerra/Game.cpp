#include "Game.h"
#include"Map.h"

Player player;

Game::Game()
    : window(VideoMode(1200, 900), "Test") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::run() {
    Clock clock;

    Map* map = new Map("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        float deltatime = clock.restart().asSeconds();
        window.clear();
        player.update(deltatime);
        player.draw(window);
        map->draw(window);
        window.display();
    }
}