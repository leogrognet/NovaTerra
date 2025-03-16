#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {
    // Crée une fenêtre
    RenderWindow window(VideoMode(800, 600), "SFML Zoom Example");

    // Crée un rectangle pour tester le zoom
    RectangleShape shape(Vector2f(100, 50));  // Taille du rectangle (100x50)
    shape.setFillColor(Color::Green);
    shape.setPosition(350, 275); // Position initiale du rectangle

    // Crée une vue initiale
    View view = window.getView();

    // Variable de zoom
    float zoomFactor = 1.0f;  // Facteur de zoom initial (1.0 signifie taille normale)
    Vector2f initialSize = shape.getSize();
    // Boucle principale
    while (window.isOpen()) {
        // Gère les événements
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Gestion du défilement de la molette de la souris pour le zoom
            if (event.type == Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    // Molette vers le haut = zoom avant
                    zoomFactor *= 0.9f;  // Réduit le facteur de zoom (zoom avant)
                    std::cout << "Zoom avant" << std::endl;
                }
                else if (event.mouseWheelScroll.delta < 0) {
                    // Molette vers le bas = zoom arrière
                    zoomFactor *= 1.1f;  // Augmente le facteur de zoom (zoom arrière)
                    std::cout << "Zoom arrière" << std::endl;
                }

                // Applique le zoom à la vue
                std::cout << shape.getLocalBounds().width;
                shape.setSize(Vector2f(shape.getLocalBounds().width, shape.getLocalBounds().height) * zoomFactor);
                shape.setPosition(Vector2f(view.getCenter().x - shape.getLocalBounds().width/2, view.getCenter().y - shape.getLocalBounds().height/2));// Ajuste la taille du rectangle
                view.setSize(window.getSize().x * zoomFactor, window.getSize().y * zoomFactor);
               // std::cout << shape.getSize().x;

               // std::cout << view.getCenter().x;
            }
        }

        // Applique la vue modifiée à la fenêtre
        window.setView(view);

        // Efface la fenêtre
        window.clear();

        // Ajuste la taille du rectangle en fonction de la taille de la vue
        Vector2f viewSize = view.getSize();  // Récupère la taille de la vue

       
        //shape.setPosition(shape.getPosition() * zoomFactor);
        // Dessine le rectangle sans affecter sa taille visuelle
        window.draw(shape);

        // Affiche tout ce qui a été dessiné
        window.display();
    }

    return 0;
}
