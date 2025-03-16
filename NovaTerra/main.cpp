#include <SFML/Graphics.hpp>
#include "ScriptBox.h"

int main() {
    // Cr�ation de la fen�tre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test ScriptBox");
    window.setFramerateLimit(60);

    // Instanciation de la classe Script
    Script script;
    script.loadScript("C:/Users/leoam/Source/Repos/NovaTerra/NovaTerra/assets/Texte de Script"); // Charge les scripts depuis un dossier

    // Simulation d'un script (dans un vrai cas, on le chargerait dynamiquement)
    script.setScript();

    // Variables pour g�rer le temps d'affichage du texte
    sf::Clock clock;

    while (window.isOpen()) {
        // Gestion des �v�nements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mise � jour du texte progressivement
        float deltaTime = clock.restart().asSeconds();
        script.updateScriptBox(deltaTime);

        // Dessin des �l�ments
        window.clear(sf::Color(30, 30, 30)); // Fond sombre
        script.drawBox(window);
        window.display();
    }

    return 0;
}
