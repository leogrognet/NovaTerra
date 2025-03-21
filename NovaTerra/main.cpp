#include "Game.h"
#include "Menu.h"

enum class MenuState {
    MENU,
    MENU_PLAY,
    MENU_SELECT_LEVEL,
    PLAY,

    SETTINGS,
    EXIT,
    CREDITS
};

int main() {
	RenderWindow window(VideoMode(1920, 1080), "NovaTerra 1.0");
    Menu* menu = new Menu(window);
	MenuPlay menuPlay(window);
	MenuSettings settingsMenu(window);

	Game* game = nullptr;

	MenuState menuState = MenuState::MENU;
    
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

        window.clear();

        switch (menuState) {
        case MenuState::MENU:
            menu->draw();
            break;
        case MenuState::MENU_PLAY:
            menuPlay.draw();
            break;
        case MenuState::PLAY:
            if(!game){
				game = new Game(1920, 1080);
				game->run();
                delete game;
				game = nullptr;
            }
            break;
        case MenuState::SETTINGS:
            settingsMenu.draw();
            break;
        case MenuState::CREDITS:
            // Afficher les crédits ici
            break;
        case MenuState::EXIT:
            window.close();
            break;
        default:
            break;
        }

		window.display();

	}

	delete game;
	return 0;

}