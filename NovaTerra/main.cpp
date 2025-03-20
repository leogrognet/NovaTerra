#include <SFML/Graphics.hpp>
#include "LevelEditor.h"
#include "Game.h"

int main() {
	Game* game = new Game(1920, 1080);
	game->run();
	delete game;
	return 0;
}