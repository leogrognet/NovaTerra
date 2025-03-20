#include "Game.h"

Background background("assets/parallaxe/bg.png", - 50);

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

    vector<shared_ptr<Entity>> vec;

    vec.push_back(make_shared<Plateforme>(100, 800, Vector2f(10, 1), true,true));
    vec.push_back(make_shared<Plateforme>(300, 400, Vector2f(5, 5), true,true));
    vec.push_back(make_shared<Bounce>(700, 700, Vector2f(1, 1), true,true));
    vec.push_back(make_shared<MovePlat>(100, 400, Vector2f(1, 1), true,true));

    vec.push_back(make_shared<GolemEnemy>(500, 700, false, false));

    vec.push_back(make_shared<Player>(vec, 100, 600, false, true));

    vec.push_back(make_shared<KillerEnemy>(600, 700, false, false));

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
		background.update(deltatime);
        //player.update(deltatime, vec);
        background.draw(window);
        map->draw(window);
        for (auto entityvec : vec) {
            entityvec->update(deltatime, vec);
            entityvec->draw(window);
            entityvec->update(deltatime, vec);
        }
        window.display();
    }
}