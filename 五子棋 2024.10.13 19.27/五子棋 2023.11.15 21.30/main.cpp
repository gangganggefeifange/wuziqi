#include <iostream>
#include "ChessGame.h"

int main(void) {
	//Chess chess;
	Chess chess(15, 20, 16, 36);
	Man man;
	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}