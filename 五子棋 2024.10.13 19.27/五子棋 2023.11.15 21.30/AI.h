#pragma once
#include "Chess.h"
#include <vector>

class AI
{
public:
	void init(Chess* chess);
	void AssignedOpening();
	bool ThreeHandExchange();
	void FiveHands_N_Dozen();
	void man_FiveHands_N_Dozen(ChessPos FiveHand[5]);
	void go();
	void giveFiveHand();
private:
	Chess* chess;
	
	// 存储各个点位的评分情况，作为AI下棋依据
	int scoreMap[15][15];

	void calculateScore();

	//	存储指定开局的3颗棋子的位置
	ChessPos AOpos[3];
	//	存储五手N打的3颗棋子的位置
	int FiveN = 3;
	ChessPos FiveHand[5];
	ChessPos Five = FiveHand[0];

	ChessPos think();
};

