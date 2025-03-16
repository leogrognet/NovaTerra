#include "Game.h"
#include "ScriptBox.h"

Player player;
Background background("assets/parallaxe/bg.png", -50);
Script scriptBox;

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "Test") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::run() {
    Clock clock;

    // Création des obstacles
    RectangleShape rectangle({ 500,50 });
    rectangle.setFillColor(Color::Black);
    rectangle.setPosition(100, 800);
    RectangleShape rectangle1({ 50,500 });
    rectangle1.setFillColor(Color::Black);
    rectangle1.setPosition(500, 400);
    vector<RectangleShape> vec = { rectangle, rectangle1 };

    // Chargement de la map et de la caméra
    std::unique_ptr<Map> map = std::make_unique<Map>("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, std::vector<int>{65});
    std::unique_ptr<Scroll> scroll = std::make_unique<Scroll>(WIDTH, HEIGHT);

    // Chargement du script
    scriptBox.loadScript("assets/scripts/");
    scriptBox.setScript();
    scriptBox.formatText(); // Formate le texte avant affichage

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Gestion de l'affichage rapide du texte ou passage au texte suivant
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    scriptBox.updateScriptBox(0.5f); // Force l'affichage rapide
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Mise à jour des éléments du jeu
        scroll->applyView(window);
        player.update(deltaTime, vec);
        background.update(deltaTime);
        scriptBox.updateScriptBox(deltaTime);

        // Affichage
        window.clear();
        background.draw(window);
        map->draw(window);
        window.draw(rectangle);
        window.draw(rectangle1);
        player.draw(window);
        scriptBox.drawBox(window); // Dessine la boîte de dialogue
        window.display();
    }
}
