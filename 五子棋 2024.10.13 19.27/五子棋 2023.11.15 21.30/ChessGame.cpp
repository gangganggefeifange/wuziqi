#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;


	man->init(chess);
	ai->init(chess);
}

void ChessGame::menu()
{
	std::cout << "1.我方先手" << std::endl;
	std::cout << "2.对方先手" << std::endl;
	std::cin >> sequence;
}

void ChessGame::rule()
{
	menu();
	switch (sequence) {
	case 1:
			ai->AssignedOpening();
			if (man->ThreeHandExchange()) {
				chess->ThreeHandExchange();
				ai->go();
				man->FiveHands_N_Dozen(FiveHand);
				ai->man_FiveHands_N_Dozen(FiveHand);
			}
			else {
				man->go();
				ai->FiveHands_N_Dozen();
				sequence = 2;
			}
			break;
	case 2:
			man->AssignedOpening();
			if(ai->ThreeHandExchange()) {
				chess->ThreeHandExchange();
				man->go();
				ai->FiveHands_N_Dozen();
			}
			else {
				ai->go();
				man->FiveHands_N_Dozen(FiveHand);
				ai->man_FiveHands_N_Dozen(FiveHand);
				sequence = 1;
			}
			break;
	}
}

void ChessGame::play()
{
	chess->Init();
	rule(); chess->PrintChess();
	switch (sequence) {
	case 1:
		while (1) {
			ai->go();
			chess->PrintChess();
			if (chess->checkOver()) {
				break;
			}
			man->go();
			chess->PrintChess();
			if (chess->isretrack())	continue;
			if (chess->checkOver()) {
				break;
			}
		}
		
	case 2:
		while (1) {
			man->go();
			if (chess->isretrack())	continue;
			if (chess->checkOver()) {
				break;
			}
			ai->go();
			if (chess->checkOver()) {
				break;
			}
		}
	}
	
}
