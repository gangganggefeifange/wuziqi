#pragma once
#include "Man.h"
#include "AI.h"
class ChessGame
{
public:
	ChessGame(Man* man, AI* ai, Chess* chess);

	void menu();

	void rule();

	void play();

private:
	Man* man;
	AI* ai;
	Chess* chess;
	ChessPos FiveHand[5];
	int sequence = 1;
};

