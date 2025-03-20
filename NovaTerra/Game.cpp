#include "Game.h"
#include "TextureLoader.h"

//TextureLoader textureloader;

Background background("assets/parallaxe/bg.png", - 50);

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "NovaTerra 1.0") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    night.setFillColor(sf::Color(0, 0, 0, 200));
    night.setSize(sf::Vector2f(2000, 2000));
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::run() {
    Clock clock;

    vector<shared_ptr<Entity>> vec;

    string image =  "assets/map/map_tileset";
    loadertest.loadTexture(image, textureListTest);
    while (true) {
        vec.push_back(make_shared<Plateform>(100, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(200, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(300, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(400, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(500, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(600, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(700, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(800, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(900, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(1000, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(1100, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(1200, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(1300, 800, Vector2f(10, 1), true, true, textureListTest));
        vec.push_back(make_shared<Plateform>(1400, 800, Vector2f(10, 1), true, true, textureListTest));
        break;
    }

    vec.push_back(make_shared<Player>(vec, 100, 600, false, true));

    Cycle* cycle = new Cycle();
    vec.push_back(make_shared<Firecamp>(800, 700, true, true));

    //Map* map = new Map("assets/map/lobby.txt", "assets/map/map_tileset/Tileset_Grass.png", 32, { 65 });
    shared_ptr<Player> playerPtr = nullptr;
    for (auto& entity : vec) {
        playerPtr = dynamic_pointer_cast<Player>(entity);
        if (playerPtr) break;
    }

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
        if (cycle->getState() == Cycle::State::Night) {
            window.draw(night);
        }
        //map->draw(window);
        for (auto& entity : vec) {
            playerPtr = dynamic_pointer_cast<Player>(entity);
            if (playerPtr) break;
        }
        for (auto entityvec : vec) {
            entityvec->update(deltatime, vec);
            if (Keyboard::isKeyPressed(Keyboard::O)) {
                entityvec->interact(*cycle, *playerPtr);
            }
            entityvec->draw(window);
            entityvec->update(deltatime, vec);
        }

        window.display();
    }
}