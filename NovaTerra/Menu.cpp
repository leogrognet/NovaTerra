#include "Menu.h"

Button::Button(float x, float y, Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

bool Button::isHovered(const Vector2f& mousePos) {
    return sprite.getGlobalBounds().contains(mousePos);
}

Menu::Menu(RenderWindow& win) : window(win), menuState(MenuState::MAIN) {
    if (!backgroundTexture.loadFromFile("Assets\\menu\\background.jpg")) {
        cerr << "Error loading background image!\n";
    }
    background.setTexture(backgroundTexture);

    Texture playTexture, settingsTexture, leaveTexture, backTexture;
	playTexture.loadFromFile("Assets\\menu\\play.png");
	settingsTexture.loadFromFile("Assets\\menu\\settings.png");
	leaveTexture.loadFromFile("Assets\\menu\\leave.png");
	backTexture.loadFromFile("Assets\\menu\\back.png");

    mainMenu = {
        {300, 200, playTexture},
        {300, 300, settingsTexture},
        {300, 400, leaveTexture}
    };
    settingsMenu = {
        {300, 400, backTexture}
    };
}

void Menu::handleEvent(const Event& event) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (menuState == MenuState::MAIN) {
            if (mainMenu[0].isHovered(mousePos)) {
                cout << "Starting game...\n";
            }
            else if (mainMenu[1].isHovered(mousePos)) {
                menuState = MenuState::SETTINGS;
            }
            else if (mainMenu[2].isHovered(mousePos)) {
                window.close();
            }
        }
        else if (menuState == MenuState::SETTINGS) {
            if (settingsMenu[2].isHovered(mousePos)) {
                menuState = MenuState::MAIN;
            }
        }
    }
}

void Menu::render() {
	window.draw(background);
	for (auto& button : mainMenu) {
		window.draw(button.sprite);
	}
}