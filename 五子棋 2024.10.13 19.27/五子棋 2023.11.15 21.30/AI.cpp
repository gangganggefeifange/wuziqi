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
	std::cout << "5手N打 N值为" << FiveN << std::endl;
}

bool AI::ThreeHandExchange()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	int ban;
	ban = MessageBox(hnd, "三手交换", "进行三手交换", MB_OKCANCEL);
	return true;
}

void AI::FiveHands_N_Dozen()
{
	for (int i = 0;i < FiveN;i++) {
		FiveHand[i] = think();
		chess->temp_ChessDown(FiveHand[i]);
	}
	std::cout << "我方给出打点坐标：" << std::endl;
	for (int i = 0; i < FiveN; i++) {
		chess->give_pos(FiveHand[i].row,FiveHand[i].col);
	}
	std::cout << "对方选择（行，列）：";	std::cin >> Five.row >> Five.col;
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
	std::cout << "选择打点坐标（行，列）：" << Five.row << " " << Five.col << std::endl;
	chess->ChessDown(Five);
}

void AI::calculateScore()
{
	int continuetree = 0;
	int continuefour = 0;
	int personNum = 0; //棋手方（黑棋）多少个连续的棋子
	int aiNum = 0; //AI方（白棋）连续有多少个连续的棋子
	int emptyNum = 0; // 该方向上空白位的个数

	// 评分向量数组清零
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			scoreMap[i][j] = 0;
		}
	}
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//对每个点进行计算
			if (chess->getChessData(row, col)) continue;

			for (int y = -1; y <= 0; y++) {        //Y的范围还是-1， 0
				for (int x = -1; x <= 1; x++) {    //X的范围是 -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //当y=0时，仅允许x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// 假设黑棋在该位置落子，会构成什么棋型
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

					// 反向继续计算
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

					if (personNum == 1) { //连2
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

					// 假设白棋在该位置落子，会构成什么棋型
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
					if (aiNum == 0)                      // 普通下子
						scoreMap[row][col] += 5;
					else if (aiNum == 1)                 // 活二
						scoreMap[row][col] += 10;
					else if (aiNum == 2)
					{
						if (emptyNum == 1)                // 死三
							scoreMap[row][col] += 25;
						else if (emptyNum == 2)			// 活三
						{
							scoreMap[row][col] += 50;
							continuetree++;
						}
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1)                // 死四
							scoreMap[row][col] += 55;
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 10000;
							continuefour++;
						}// 活四
					}
					else if (aiNum >= 4)
						scoreMap[row][col] += 30000;   // 活五，应该具有最高优先级
				}
			}
			if (continuetree >= 2 || continuefour >= 2)
				scoreMap[row][col] -= 50000;
		}
	}

}

ChessPos AI::think()
{
	// 计算评分
	calculateScore();

	// 从评分中找出最大分数的位置
	int maxScore = 0;
	//std::vector<std::pair<int, int>> maxPoints;
	vector<ChessPos> maxPoints;
	int k = 0;

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++)
		{
			// 前提是这个坐标是空的
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore)          // 找最大的数和坐标
				{
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {   // 如果有多个最大的数，都存起来
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	// 随机落子，如果有多个点的话
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}


void AI::go()
{
	//chess->Time_Start();
	std::cout << "AI走棋" << std::endl;
	ChessPos pos = think();
	chess->ChessDown(pos);
	//chess->Time_pause();
	//chess->get_time();
}

