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
	//	�洢ָ�����ֵ�3�����ӵ�λ��
	ChessPos AOpos[3];
	//	�洢����N���3�����ӵ�λ��
	int FiveN = 3;
	ChessPos FiveHand[5];
	ChessPos Five = FiveHand[0];
};

