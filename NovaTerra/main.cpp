#include <SFML/Graphics.hpp>
#include "LevelEditor.h"

int main()
{
    // Cr�er une fen�tre SFML
    RenderWindow window(VideoMode(800, 600), "Level Editor");

    // Cr�er un objet LevelEditor
    LevelEditor editor;

    // D�finir le deltaTime
    Clock clock;

    View view = window.getView();
    editor.dropDownMenu(window);
    editor.selectButtonMenu(window);
    // Boucle principale du jeu
    while (window.isOpen())
    {
        // Calculer le deltaTime
        float deltaTime = clock.restart().asSeconds();

        // G�rer les �v�nements
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Appeler la fonction de gestion des entr�es (g�re aussi la molette de la souris)
        editor.handleInput(window, view, event, deltaTime);

        // Mise � jour du jeu (si n�cessaire)
        editor.update();

        // Effacer l'�cran
        window.clear();

        // Dessiner les �l�ments
        editor.draw(window);

        // Dessiner le menu d�roulant

        // Afficher la fen�tre
        window.display();
    }

    return 0;
}
