#include "Game.h"
#include "TextureLoader.h"

//TextureLoader textureloader;

Background background("assets/parallaxe/bg.png", -50);

Game::Game(const int _WIDTH, const int _HEIGHT)
    : WIDTH(_WIDTH), HEIGHT(_HEIGHT), window(VideoMode(WIDTH, HEIGHT), "NovaTerra 1.0") {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    night.setSize(sf::Vector2f(2000, 2000));
    night.setFillColor(sf::Color(0, 0, 0, 200));
}

Game::~Game() {
    cout << "Le jeu est détruit\n";
}

void Game::run() {
    Clock clock;

    vector<shared_ptr<Entity>> vec;
    string image = "assets/map/map_tileset";
    loadertest.loadTexture(image, textureListTest);
    View view;
    view.zoom(0.9f);


    string mapFile = "../NovaTerra/assets/map/lobby.txt";

    Map map(mapFile, window);

    vec = map.generateTiles(textureListTest, vec);

    Cycle* cycle = new Cycle();

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
        //scroll->applyView(window);
        float deltatime = clock.restart().asSeconds();

        window.clear();
       
        //player.update(deltatime, vec);
        background.draw(window);
        if (cycle->getState() == Cycle::State::Night) {
            window.draw(night);
        }
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
            if (entityvec->getID() == 1) {
                //background.update(deltatime, entityvec->getSprite().getPosition());
                view.setCenter(entityvec->getSprite().getPosition().x +200,entityvec->getSprite().getPosition().y);
            }
        }
        window.setView(view);
        window.display();
    }
}