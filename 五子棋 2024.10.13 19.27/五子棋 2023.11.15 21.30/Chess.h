#pragma once
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <math.h>
#include <string.h>
#include "clock.h"
using namespace std;

//棋子种类
typedef enum {
	CHESS_WHITE = -1,  // 白方
	CHESS_BLACK = 1,    // 黑方
	CHESS_NONE = 0		//没有落子
} chess_kind_t;

//棋盘坐标
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

//步数和棋子种类
struct Step {
	int step;
	chess_kind_t kind;
	Step(int s = 0, chess_kind_t k = CHESS_NONE) : step(s), kind(k) {}
};

static bool is_ban = false;//白棋是否出现禁手

class Chess
{
public:
	// 棋盘的初始化：加载棋盘的图片资源，初始化棋盘的相关数据
	Chess(int gradeSize, int marginX, int marginY, double chessSize);

	// 判断在指定坐标(x,y)位置，是否是有效点击
	// 如果是有效点击，把有效点击的位置(行，列）保存在参数pos中
	bool clickBoard(int x, int y, ChessPos* pos);
	//	是否点击到悔棋键
	bool IsRetract(int x, int y);

	//	初始化棋盘
	void Init();

	//	输出棋盘
	void PrintChess();

	//	落子
	void ChessDown(ChessPos pos);

	//	撤销棋子
	void Retrack(ChessPos pos);

	//	指定开局
	void AssignedOpening(ChessPos pos[3]);

	//	三手交换
	void ThreeHandExchange();


	//	判断是否出现禁手 输赢
	bool checkWin();
	bool checkOver();

	//	获取当前下棋方
	bool get_playerFlag();

	//	获取当前步数
	int get_step();

	//	获取棋盘尺寸
	int getGradeSize();
	// 获取指定位置是黑棋，还是白棋，还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//	获取最后下子位置
	ChessPos lastpos();
	ChessPos appointpos(int n);

	//	判断是否点击到悔棋键
	bool isretrack();

	//	对局结束，保存棋谱
	void save();

	//	临时落子，用于5手N打
	void temp_ChessDown(ChessPos temp);
	void temp_Retrack(ChessPos pos);

	//	根据行列输出坐标
	void give_pos(int row,int col);

private:
	//	存储棋盘数据的变量
	int gradeSize;//棋盘尺寸
	int margin_x;//上边界
	int margin_y;//左边界
	double chessSize;//棋子大小（棋盘方格大小）

	IMAGE chessBlackImg;//	黑棋
	IMAGE chessWhiteImg;//	白棋

	//	存储棋盘每个点是第几步下的 下的什么棋
	Step step[15][15];
	int num = 1;//该变量方便给step数组中的step赋值

	//	存储棋盘中每个点的值
	int chessMap[15][15] = { 0 };

	//	判断棋子种类 true 黑棋 ，false 白棋
	bool playerFlag;

	bool retrack = false;	//设置悔棋标志，防止悔棋后AI走棋

	char ch_col[15] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O' };
	int ch_row[15] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };

};


