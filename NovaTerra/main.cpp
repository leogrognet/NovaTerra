#include <SFML/Graphics.hpp>
#include <iostream>
#include "RigidBody.h"

using namespace sf;

// Classe pour g�rer la simulation du joueur
class Player : public RigidBody {
public:
    RectangleShape shape;  // RectangleShape pour le joueur

    Player(float x, float y) {
        position = Vector2f(x, y);
        velocity = Vector2f(0, 0);
        acceleration = Vector2f(0, 0);
        mass = 1.0f; // Masse du joueur

        // Initialiser le RectangleShape
        shape.setSize(Vector2f(50, 50));  // Taille du rectangle
        shape.setFillColor(Color::Blue);  // Couleur du rectangle
        shape.setPosition(position);      // Position initiale du joueur
    }

    void applyGravity() {
        Vector2f gravity(0, 9.8f); // Gravit�, ici positive en y
        applyForce(gravity);
    }

    void movePlayer(float deltaTime) {
        applyGravity();

        // Mouvement avec ZQSD
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            velocity.y = -100.0f; // D�placer vers le haut
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            velocity.y = 100.0f; // D�placer vers le bas
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            velocity.x = -100.0f; // D�placer vers la gauche
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            velocity.x = 100.0f; // D�placer vers la droite
        }

        // Mise � jour de la position avec move()
        shape.move(velocity * deltaTime);
    }

    void moveupdate(float deltaTime) {
        movePlayer(deltaTime);
    }

    // Permet d'obtenir la forme du joueur sous forme de FloatRect
    FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

int main() {
    // Cr�er la fen�tre SFML
    RenderWindow window(VideoMode(800, 600), "Player Collision Test");

    // Cr�er un joueur
    Player player(100, 100);

    // Cr�er des objets de collision (sol et mur)
    RectangleShape ground(Vector2f(800, 50));
    ground.setPosition(0, 550);
    ground.setFillColor(Color::Green);

    RectangleShape wall(Vector2f(50, 600));
    wall.setPosition(700, 0);
    wall.setFillColor(Color::Red);

    // Liste de colliders
    std::vector<RectangleShape> colliders = { ground, wall };

    // Boucle principale de la fen�tre
    Clock clock;
    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // Gestion des �v�nements
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Appliquer la gravit� et mettre � jour le joueur
        player.applyGravity();
        player.update(dt);
        player.moveupdate(dt);
        // D�tecter les collisions avec le sol et le mur
        FloatRect playerShape = player.getBounds(); // Forme du joueur
        player.groundCollision(colliders, playerShape);

        // Dessiner
        window.clear();

        // Dessiner le joueur comme un rectangle
        window.draw(player.shape);

        // Dessiner le sol et le mur
        window.draw(ground);
        window.draw(wall);

        window.display();
    }

    return 0;
}
