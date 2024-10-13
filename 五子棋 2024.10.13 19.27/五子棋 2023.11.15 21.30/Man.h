#pragma once
#include "Chess.h"
class Man
{
public:
	void init(Chess* chess);
	void AssignedOpening();
	bool ThreeHandExchange();
	void FiveHands_N_Dozen(ChessPos FiveHand[5]);
	void go();
private:
	Chess* chess;
	//	存储指定开局的3颗棋子的位置
	ChessPos AOpos[3];
	//	存储五手N打的3颗棋子的位置
	int FiveN = 3;
	ChessPos FiveHand[5];
	ChessPos Five = FiveHand[0];
};

