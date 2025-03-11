#include "Game.h"

int main() {
	Game* game = new Game(1200, 900);
	game->run();
	delete game;
	return 0;
}