#include "../include/Game.h"

Game::Game()
    : window(sf::VideoMode(1200, 900), "Test") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

Game::~Game() {
    std::cout << "Le jeu est détruit\n";
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}