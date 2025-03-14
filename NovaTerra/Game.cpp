#include "Game.h"

Player player;

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "Test") {
    world = new World("assets/map/lobby.txt");
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
    RectangleShape rectangle({ 5000,50 });
    rectangle.setFillColor(Color::Black);
    rectangle.setPosition(100, 800);
    //RectangleShape rectangle1({ 50,500 });
    //rectangle1.setFillColor(Color::Black);
    //rectangle1.setPosition(500, 400);
    vector<RectangleShape> vec;
    vec.push_back(rectangle);
    //vec.push_back(rectangle1);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        
        float deltatime = clock.restart().asSeconds();
        
        world->update(deltatime, player.body.getPosition());

        window.clear();
        player.update(deltatime, vec);
        window.draw(bg); // Background
        world->render(window);
        window.draw(rectangle);
        //window.draw(rectangle1);
        player.draw(window);
        window.display();
    }
}