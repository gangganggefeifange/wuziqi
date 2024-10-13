#include "Man.h"
void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::AssignedOpening()
{
	for (int i = 0;i < 3;i++) {
		go();
	}
}

bool Man::ThreeHandExchange()
{
	int is_change;
	//获取窗口句柄
	HWND hnd = GetHWnd();
	is_change = MessageBox(hnd, "三手交换", "是否进行三手交换", MB_OKCANCEL);
	if (is_change == IDOK)
	{
		return true;
	}
	else if (IDCANCEL == is_change)
	{
		return false;
	}
}

void Man::FiveHands_N_Dozen(ChessPos FiveHand[5])
{
	std::cout << "5手N打N为："; std::cin >> FiveN;
	std::cout << "给出n个打点坐标（行，列）：" << std::endl;
	for (int i = 0; i < FiveN; i++) {
		std::cin >> FiveHand[i].row >> FiveHand[i].col;
	}
	
}

void Man::go() {
	// 等待棋士有效落子
	MOUSEMSG msg;
	ChessPos pos;
	std::cout << "MAN走棋" << std::endl;
	// 落子
	chess_kind_t kind = chess->get_playerFlag() ? CHESS_BLACK : CHESS_WHITE;



	while (1) {
		msg = GetMouseMsg();
		//玩家点击棋盘下棋
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			chess->ChessDown(pos);
			break;
		}
		//玩家点击悔棋
		if (msg.uMsg == WM_LBUTTONDOWN && chess->IsRetract(msg.x, msg.y)) {
			if (chess->get_step() > 3) {
				chess->Retrack(chess->lastpos());
				chess->Retrack(chess->lastpos());
				std::cout << "悔棋" << endl;
			}
			else {
				chess->Retrack(chess->lastpos());
			}

			break;
		}
	}


}