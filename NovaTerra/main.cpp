#include <SFML/Graphics.hpp>
#include "LevelEditor.h"
#include "Game.h"

//int main()
//{
//    // Cr�er une fen�tre SFML
//    RenderWindow window(VideoMode(800, 600), "Level Editor");
//
//    // Cr�er un objet LevelEditor
//    LevelEditor editor(window);
//
//    // D�finir le deltaTime
//    Clock clock;
//
//    View tileView = window.getView();
//    View Ui_View = window.getView();
//
//
//
//    // Boucle principale du jeu
//
//    while (window.isOpen())
//    {
//        // Calculer le deltaTime
//        float deltaTime = clock.restart().asSeconds();
//
//        // G�rer les �v�nements
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        // Appeler la fonction de gestion des entr�es (g�re aussi la molette de la souris)
//        //editor.handleInput(window, tileView, event, deltaTime);
//
//        // Mise � jour du jeu (si n�cessaire)
//        editor.update(window, tileView, Ui_View, event, deltaTime);
//
//        // Effacer l'�cran
//        //window.clear();
//
//        // Dessiner les �l�ments
//        //editor.draw(window,tileView, Ui_View);
//
//        // Dessiner le menu d�roulant
//
//        // Afficher la fen�tre
//        //window.display();
//    }
//
//    return 0;
//
// }

int main() {
	Game* game = new Game(1920, 1080);
	game->run();
	delete game;
	return 0;

}