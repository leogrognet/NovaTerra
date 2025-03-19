#include <SFML/Graphics.hpp>
#include "LevelEditor.h"

int main()
{
    // Cr?er une fen?tre SFML
    RenderWindow window(VideoMode(800, 600), "Level Editor");

    // Cr?er un objet LevelEditor
    LevelEditor editor(window);

    // D?finir le deltaTime
    Clock clock;

    View tileView = window.getView();
    View Ui_View = window.getView();



    // Boucle principale du jeu

    while (window.isOpen())
    {
        // Calculer le deltaTime
        float deltaTime = clock.restart().asSeconds();

        // G?rer les ?v?nements
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Mise ? jour du jeu (si n?cessaire)
        editor.update(window, tileView, Ui_View, event, deltaTime);



        
    }
    return 0;
}