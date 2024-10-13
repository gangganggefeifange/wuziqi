#include "AI.h"
#include <algorithm>

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			scoreMap[i][j] = 0;
		}
	}
}

void AI::AssignedOpening()
{
	AOpos[0].row = 7;	AOpos[0].col = 7;
	AOpos[1].row = 6;	AOpos[1].col = 7;
	AOpos[2].row = 7;	AOpos[2].col = 6;
	chess->AssignedOpening(AOpos);
	std::cout << "5��N�� NֵΪ" << FiveN << std::endl;
}

bool AI::ThreeHandExchange()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	int ban;
	ban = MessageBox(hnd, "���ֽ���", "�������ֽ���", MB_OKCANCEL);
	return true;
}

void AI::FiveHands_N_Dozen()
{
	for (int i = 0;i < FiveN;i++) {
		FiveHand[i] = think();
		chess->temp_ChessDown(FiveHand[i]);
	}
	std::cout << "�ҷ�����������꣺" << std::endl;
	for (int i = 0; i < FiveN; i++) {
		chess->give_pos(FiveHand[i].row,FiveHand[i].col);
	}
	std::cout << "�Է�ѡ���У��У���";	std::cin >> Five.row >> Five.col;
	Five.row = 15 - Five.row;
	for (int i = 0; i < FiveN; i++) {
		if (FiveHand[i].col != Five.col || FiveHand[i].row != Five.row)
			chess->temp_Retrack(FiveHand[i]);
	}
	chess->ChessDown(Five);
}

void AI::man_FiveHands_N_Dozen(ChessPos FiveHand[5])
{
	ChessPos Five;
	for (int i = 1; i < FiveN; i++) {
		int row = FiveHand[i].row;	int col = FiveHand[i].col;
		int row1 = FiveHand[i - 1].row;	int col1 = FiveHand[i - 1].col;
		std::cout << row << " " << col << endl;
		if (scoreMap[row1][col1] <= scoreMap[row][col]) {
			Five = FiveHand[i - 1];
		}
		else {
			Five = FiveHand[i];
		}
	}
	std::cout << "ѡ�������꣨�У��У���" << Five.row << " " << Five.col << std::endl;
	chess->ChessDown(Five);
}

void AI::calculateScore()
{
	int continuetree = 0;
	int continuefour = 0;
	int personNum = 0; //���ַ������壩���ٸ�����������
	int aiNum = 0; //AI�������壩�����ж��ٸ�����������
	int emptyNum = 0; // �÷����Ͽհ�λ�ĸ���

	// ����������������
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			scoreMap[i][j] = 0;
		}
	}
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//��ÿ������м���
			if (chess->getChessData(row, col)) continue;

			for (int y = -1; y <= 0; y++) {        //Y�ķ�Χ����-1�� 0
				for (int x = -1; x <= 1; x++) {    //X�ķ�Χ�� -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //��y=0ʱ��������x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// ��������ڸ�λ�����ӣ��ṹ��ʲô����
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					// �����������
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (personNum == 1) { //��2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;

						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] = 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] = 5000; //200
						}
					}
					else if (personNum == 4) {
						scoreMap[row][col] = 20000;
					}
					else if (personNum == 5) {
						scoreMap[row][col] = 40000;
					}

					// ��������ڸ�λ�����ӣ��ṹ��ʲô����
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}
					if (aiNum == 0)                      // ��ͨ����
						scoreMap[row][col] += 5;
					else if (aiNum == 1)                 // ���
						scoreMap[row][col] += 10;
					else if (aiNum == 2)
					{
						if (emptyNum == 1)                // ����
							scoreMap[row][col] += 25;
						else if (emptyNum == 2)			// ����
						{
							scoreMap[row][col] += 50;
							continuetree++;
						}
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1)                // ����
							scoreMap[row][col] += 55;
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 10000;
							continuefour++;
						}// ����
					}
					else if (aiNum >= 4)
						scoreMap[row][col] += 30000;   // ���壬Ӧ�þ���������ȼ�
				}
			}
			if (continuetree >= 2 || continuefour >= 2)
				scoreMap[row][col] -= 50000;
		}
	}

}

ChessPos AI::think()
{
	// ��������
	calculateScore();

	// ���������ҳ���������λ��
	int maxScore = 0;
	//std::vector<std::pair<int, int>> maxPoints;
	vector<ChessPos> maxPoints;
	int k = 0;

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++)
		{
			// ǰ������������ǿյ�
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore)          // ��������������
				{
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {   // ����ж������������������
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	// ������ӣ�����ж����Ļ�
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}


void AI::go()
{
	//chess->Time_Start();
	std::cout << "AI����" << std::endl;
	ChessPos pos = think();
	chess->ChessDown(pos);
	//chess->Time_pause();
	//chess->get_time();
}

