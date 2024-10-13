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
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	is_change = MessageBox(hnd, "���ֽ���", "�Ƿ�������ֽ���", MB_OKCANCEL);
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
	std::cout << "5��N��NΪ��"; std::cin >> FiveN;
	std::cout << "����n��������꣨�У��У���" << std::endl;
	for (int i = 0; i < FiveN; i++) {
		std::cin >> FiveHand[i].row >> FiveHand[i].col;
	}
	
}

void Man::go() {
	// �ȴ���ʿ��Ч����
	MOUSEMSG msg;
	ChessPos pos;
	std::cout << "MAN����" << std::endl;
	// ����
	chess_kind_t kind = chess->get_playerFlag() ? CHESS_BLACK : CHESS_WHITE;



	while (1) {
		msg = GetMouseMsg();
		//��ҵ����������
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			chess->ChessDown(pos);
			break;
		}
		//��ҵ������
		if (msg.uMsg == WM_LBUTTONDOWN && chess->IsRetract(msg.x, msg.y)) {
			if (chess->get_step() > 3) {
				chess->Retrack(chess->lastpos());
				chess->Retrack(chess->lastpos());
				std::cout << "����" << endl;
			}
			else {
				chess->Retrack(chess->lastpos());
			}

			break;
		}
	}


}