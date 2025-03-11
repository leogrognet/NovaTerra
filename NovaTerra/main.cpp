#include <SFML/Graphics.hpp>
#include "RigidBody.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "RigidBody Collision Test");

    RigidBody player({ 100, 100 }, 1.0f);
    sf::RectangleShape playerShape({ 50, 50 });
    playerShape.setFillColor(sf::Color::Red);

    // Liste des plateformes
    std::vector<sf::RectangleShape> colliders;

    sf::RectangleShape ground({ 800, 20 });
    ground.setPosition(0, 500);
    ground.setFillColor(sf::Color::Green);
    colliders.push_back(ground);

    sf::RectangleShape block({ 100, 20 });
    block.setPosition(300, 400);
    block.setFillColor(sf::Color::Blue);
    colliders.push_back(block);
    sf::RectangleShape block2({ 20, 100 });
    block2.setPosition(300, 300);
    block2.setFillColor(sf::Color::Blue);
    colliders.push_back(block2);

    float gravity = 1000000.0f;
    float speed = 200.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Appliquer la gravité
        if (!player.isGrounded) {
            player.applyForce({ 0, gravity * dt });
        }

        // Déplacement du joueur
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  player.applyForce({ -speed, 0 });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.applyForce({ speed, 0 });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.isGrounded)
            player.velocity.y = -200.0f; // Saut

        player.update(dt);

        // Gérer la collision avec le sol et obstacles
        player.groundCollision(colliders, playerShape.getGlobalBounds());

        // Mise à jour de la position visuelle
        playerShape.setPosition(player.position);

        // Dessin
        window.clear();
        for (const auto& collider : colliders)
            window.draw(collider);
        window.draw(playerShape);
        window.display();
    }

    return 0;
}
