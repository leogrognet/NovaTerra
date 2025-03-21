#include "Menu.h"
#include "Game.h"

Menu::Menu(RenderWindow& win) : window(win), selectedItemIndex(0) {
	if (!backgroundTexture.loadFromFile("assets/menu/background.png")) {
		cerr << "Erreur de chargement du background" << endl;
	}
	if (!playTexture.loadFromFile("assets/menu/play.png")) {
		cerr << "Erreur de chargement de la texture du bouton play" << endl;
	}
	if (!settingsTexture.loadFromFile("assets/menu/options.png")) {
		cerr << "Erreur de chargement de la texture du bouton settings" << endl;
	}
	if (!exitTexture.loadFromFile("assets/menu/exit.png")) {
		cerr << "Erreur de chargement de la texture du bouton exit" << endl;
	}
	if (!creditsTexture.loadFromFile("assets/menu/credits.png")) {
		cerr << "Erreur de chargement de la texture du bouton credits" << endl;
	}
	if (!editTexture.loadFromFile("assets/menu/edit.png")) {
		cerr << "Erreur de chargement de la texture du bouton editor" << endl;
	}

	backgroundSprite.setTexture(backgroundTexture);
	playSprite.setTexture(playTexture);
	settingsSprite.setTexture(settingsTexture);
	exitSprite.setTexture(exitTexture);
	creditsSprite.setTexture(creditsTexture);
	editSprite.setTexture(editTexture);

	playSprite.setScale(0.3, 0.3);
	settingsSprite.setScale(0.3, 0.3);
	exitSprite.setScale(0.3, 0.3);
	creditsSprite.setScale(0.1, 0.1);
	editSprite.setScale(0.4, 0.4);

	backgroundSprite.setPosition(0, 0);

	playSprite.setPosition(450, 175);
	settingsSprite.setPosition(450, 330);
	editSprite.setPosition(450, 450);
	exitSprite.setPosition(450, 550);
	
}

void Menu::draw() {

	window.draw(backgroundSprite);
	window.draw(playSprite);
	window.draw(settingsSprite);
	window.draw(exitSprite);
	window.draw(creditsSprite);
	window.draw(editSprite);
}

int Menu::handleMouseClick(Vector2i mousePos) {
	cout << "Mouse Click at: " << mousePos.x << ", " << mousePos.y << endl;

	if (playSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		cout << "Play button clicked!" << endl;
		return 0; // Play
	}
	if (settingsSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		cout << "Settings button clicked!" << endl;
		return 1; // Settings
	}
	if (editSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		cout << "Edit button clicked" << endl;
		return 2;
	}
	if (exitSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		cout << "Exit button clicked!" << endl;
		return 3; // Exit
	}

	cout << "No button clicked!" << endl;
	return -1; // Aucun bouton cliqué
}


MenuSettings::MenuSettings(RenderWindow& win) : window(win), selectedItemIndex(0) {
	if (!backgroundTexture.loadFromFile("assets/menu/background.png")) {
		cerr << "Erreur de chargement du background" << endl;
	}
	if (!backTexture.loadFromFile("assets/menu/exit.png")) {
		cerr << "Erreur de chargement de la texture du bouton back" << endl;
	}
	if (!keyTexture.loadFromFile("assets/menu/keys.png")) {
		cerr << "Erreur de chargement de la texture du bouton keys" << endl;
	}
	if (!soundTexture.loadFromFile("assets/menu/sound.png")) {
		cerr << "Erreur de chargement de la texture du bouton sound" << endl;
	}

	backgroundSprite.setTexture(backgroundTexture);
	backSprite.setTexture(backTexture);
	keySprite.setTexture(keyTexture);
	soundSprite.setTexture(soundTexture);

	backSprite.setScale(0.3, 0.3);

	backgroundSprite.setPosition(0, 0);
	backSprite.setPosition(450, 450);

}

void MenuSettings::draw() {

	window.draw(backgroundSprite);
	window.draw(backSprite);
	window.draw(keySprite);
	window.draw(soundSprite);

}

int MenuSettings::handleMouseClick(Vector2i mousePos) {

	if (keySprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		return 0; // Keys
	}
	if (soundSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		return 1; // Sound
	}
	if (backSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
		return 2; // Back
	}
	return -1;

}