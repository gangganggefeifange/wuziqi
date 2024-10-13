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
	
	// �洢������λ�������������ΪAI��������
	int scoreMap[15][15];

	void calculateScore();

	//	�洢ָ�����ֵ�3�����ӵ�λ��
	ChessPos AOpos[3];
	//	�洢����N���3�����ӵ�λ��
	int FiveN = 3;
	ChessPos FiveHand[5];
	ChessPos Five = FiveHand[0];

	ChessPos think();
};

