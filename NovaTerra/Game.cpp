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

    Plateforme plat1(100,800,{ 10,1 },true);
    Plateforme plat2(300, 400, { 1,10 },true);

    vector<shared_ptr<Entity>> vec;

    vec.push_back(make_shared<Plateforme>(plat1));
    vec.push_back(make_shared<Plateforme>(plat2));

    Player player(vec,100,600,false);

    vec.push_back(make_shared<Player>(player));

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
        background.draw(window);
        map->draw(window);
        for (auto entityvec : vec) {
            entityvec->draw(window);
            entityvec->update(deltatime, vec);
        }
        window.display();
    }
}