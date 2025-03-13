#include "Game.h"

Player player;

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "Test") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    bg.setSize({ 1000000, 2000 });
    bg.setFillColor(sf::Color::Cyan);
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::run() {
    Clock clock;
    RectangleShape rectangle({ 500,50 });
    rectangle.setFillColor(Color::Black);
    rectangle.setPosition(100, 800);
    RectangleShape rectangle1({ 50,400 });
    rectangle1.setFillColor(Color::Black);
    rectangle1.setPosition(300, 400);
    vector<RectangleShape> vec;
    vec.push_back(rectangle);
    vec.push_back(rectangle1);

    Map* map = new Map("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });
    Scroll* scroll = new Scroll(WIDTH, HEIGHT);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        //scroll->move(1.f, 0.f);
        scroll->applyView(window);
        float deltatime = clock.restart().asSeconds();


        window.clear();
        player.update(deltatime, vec);
        window.draw(bg); // Background
        map->draw(window);
        window.draw(rectangle);
        window.draw(rectangle1);
        player.draw(window);
        window.display();
    }
}