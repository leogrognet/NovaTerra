#include <SFML/Graphics.hpp>
#include "LevelEditor.h"

int main()
{
    // Créer une fenêtre SFML
    RenderWindow window(VideoMode(800, 600), "Level Editor");

    // Créer un objet LevelEditor
    LevelEditor editor(window);

    // Définir le deltaTime
    Clock clock;

    View tileView = window.getView();
    View Ui_View = window.getView();



    // Boucle principale du jeu

    while (window.isOpen())
    {
        // Calculer le deltaTime
        float deltaTime = clock.restart().asSeconds();

        // Gérer les événements
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Appeler la fonction de gestion des entrées (gère aussi la molette de la souris)
        //editor.handleInput(window, tileView, event, deltaTime);

        // Mise à jour du jeu (si nécessaire)
        editor.update(window, tileView, Ui_View, event, deltaTime);

        // Effacer l'écran
        //window.clear();

        // Dessiner les éléments
        //editor.draw(window,tileView, Ui_View);

        // Dessiner le menu déroulant

        // Afficher la fenêtre
        //window.display();
    }

    return 0;
}