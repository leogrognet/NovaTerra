#include "Game.h"

Player player;

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "Test") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    bg.setSize({ 2000, 2000 });
    bg.setFillColor(sf::Color::Cyan);
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::run() {
    Clock clock;

    Map* map = new Map("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });
    Scroll* scroll = new Scroll(WIDTH, HEIGHT);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        scroll->move(2.f, 0.f);
        scroll->applyView(window);
        float deltatime = clock.restart().asSeconds();
        window.clear();
        player.update(deltatime);
        window.draw(bg); // Background
        map->draw(window);
        player.draw(window);
        window.display();
    }
}