#pragma once
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <math.h>
#include <string.h>
#include "clock.h"
using namespace std;

//��������
typedef enum {
	CHESS_WHITE = -1,  // �׷�
	CHESS_BLACK = 1,    // �ڷ�
	CHESS_NONE = 0		//û������
} chess_kind_t;

//��������
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};

//��������������
struct Step {
	int step;
	chess_kind_t kind;
	Step(int s = 0, chess_kind_t k = CHESS_NONE) : step(s), kind(k) {}
};

static bool is_ban = false;//�����Ƿ���ֽ���

class Chess
{
public:
	// ���̵ĳ�ʼ�����������̵�ͼƬ��Դ����ʼ�����̵��������
	Chess(int gradeSize, int marginX, int marginY, double chessSize);

	// �ж���ָ������(x,y)λ�ã��Ƿ�����Ч���
	// �������Ч���������Ч�����λ��(�У��У������ڲ���pos��
	bool clickBoard(int x, int y, ChessPos* pos);
	//	�Ƿ����������
	bool IsRetract(int x, int y);

	//	��ʼ������
	void Init();

	//	�������
	void PrintChess();

	//	����
	void ChessDown(ChessPos pos);

	//	��������
	void Retrack(ChessPos pos);

	//	ָ������
	void AssignedOpening(ChessPos pos[3]);

	//	���ֽ���
	void ThreeHandExchange();


	//	�ж��Ƿ���ֽ��� ��Ӯ
	bool checkWin();
	bool checkOver();

	//	��ȡ��ǰ���巽
	bool get_playerFlag();

	//	��ȡ��ǰ����
	int get_step();

	//	��ȡ���̳ߴ�
	int getGradeSize();
	// ��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//	��ȡ�������λ��
	ChessPos lastpos();
	ChessPos appointpos(int n);

	//	�ж��Ƿ����������
	bool isretrack();

	//	�Ծֽ�������������
	void save();

	//	��ʱ���ӣ�����5��N��
	void temp_ChessDown(ChessPos temp);
	void temp_Retrack(ChessPos pos);

	//	���������������
	void give_pos(int row,int col);

private:
	//	�洢�������ݵı���
	int gradeSize;//���̳ߴ�
	int margin_x;//�ϱ߽�
	int margin_y;//��߽�
	double chessSize;//���Ӵ�С�����̷����С��

	IMAGE chessBlackImg;//	����
	IMAGE chessWhiteImg;//	����

	//	�洢����ÿ�����ǵڼ����µ� �µ�ʲô��
	Step step[15][15];
	int num = 1;//�ñ��������step�����е�step��ֵ

	//	�洢������ÿ�����ֵ
	int chessMap[15][15] = { 0 };

	//	�ж��������� true ���� ��false ����
	bool playerFlag;

	bool retrack = false;	//���û����־����ֹ�����AI����

	char ch_col[15] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O' };
	int ch_row[15] = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };

};


