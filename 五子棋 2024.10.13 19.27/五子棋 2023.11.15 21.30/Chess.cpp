#include "Chess.h"
#include <conio.h>

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}


Chess::Chess(int gradeSize, int marginX, int marginY, double chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			chessMap[i][j] = 0;
		}
	}
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	if (x < 547 && y < 537) {
		int col = (int)(x - margin_x) / chessSize;
		int row = (int)(y - margin_y) / chessSize;

		int leftTopPosX = (int)(margin_x + chessSize * col);
		int leftTopPosY = (int)(margin_y + chessSize * row);
		int offset = (int)(chessSize * 0.4); // 20 �������ģ����������

		int len;
		bool selectPos = false;

		do {
			len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
			if (len < offset) {
				pos->row = row;
				pos->col = col;
				if (chessMap[pos->row][pos->col] == 0) {
					selectPos = true;
				}
				break;
			}

			// �������Ͻǵľ���
			len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
			if (len < offset) {
				pos->row = row;
				pos->col = col + 1;
				if (chessMap[pos->row][pos->col] == 0) {
					selectPos = true;
				}
				break;
			}

			// �������½ǵľ���
			len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
			if (len < offset) {
				pos->row = row + 1;
				pos->col = col;
				if (chessMap[pos->row][pos->col] == 0) {
					selectPos = true;
				}
				break;
			}

			// �������½ǵľ���
			len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
			if (len < offset) {
				pos->row = row + 1;
				pos->col = col + 1;

				if (chessMap[pos->row][pos->col] == 0) {
					selectPos = true;
				}
				break;
			}
		} while (0);

		return selectPos;
	}
	return false;
}

void Chess::Init()
{
	initgraph(752, 554);
	loadimage(0, "res/����.png");
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);

	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			step[i][j].step = 0;
			step[i][j].kind = CHESS_NONE;
			chessMap[i][j] = 0;
		}
	}
	playerFlag = true;

}

void Chess::PrintChess()
{
	cleardevice();
	
	/*initgraph(752, 537);*/
	loadimage(0, "res/����.png");
	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			int x = (int)(margin_x + j * chessSize - 0.5 * chessSize);
			int y = (int)(margin_y + i * chessSize - 0.5 * chessSize);

			if (i == 0)	y = 0;

			if (chessMap[i][j] == -1) {
				putimagePNG(x, y, &chessWhiteImg);
			}
			else if (chessMap[i][j] == 1) {
				putimagePNG(x, y, &chessBlackImg);
			}
		}
	}
}

bool Chess::IsRetract(int x, int y)
{
	if (x >= 560 && x <= 737 && y >= 74 && y <= 126)	return true;
	return false;
}

void Chess::ChessDown(ChessPos pos)
{
	//������������
	step[pos.row][pos.col].step = num;
	step[pos.row][pos.col].kind = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	chessMap[pos.row][pos.col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	//0std::cout << "������" << num << "���꣺" << pos.row << "," << pos.col << std::endl;
	give_pos(pos.row, pos.col);
	num++;	//����+1
	retrack = false;//	���Ļ����־
	playerFlag = !playerFlag;//����
	PrintChess();
}

void Chess::Retrack(ChessPos pos)
{
	num--;//����-1
	retrack = true;//	���Ļ����־
	//������������
	step[pos.row][pos.col].step = 0;
	step[pos.row][pos.col].kind = CHESS_NONE;
	chessMap[pos.row][pos.col] = 0;
	//playerFlag = !playerFlag;//����
	PrintChess();
}

void Chess::AssignedOpening(ChessPos pos[3])
{
	int i;
	for (i = 0; i < 3; i++) {
		ChessDown(pos[i]);
	}
}

void Chess::ThreeHandExchange()
{
	int is_change;
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	is_change = MessageBox(hnd, "�������ֽ���", "���ֽ���", MB_OKCANCEL);
}


bool Chess::checkWin()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	int ban;
	// ˮƽ����
	int row = lastpos().row;
	int col = lastpos().col;

	//��������
	int num = 0;
	for (int i = 1; i < 5; i++)
	{//��������
		if (row - i >= 0 && row + i <= gradeSize && chessMap[row + i][col] == chessMap[row][col])
			num++;
		if (row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col] == chessMap[row][col])
			num++;
		if (row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col] == 0)
			continue;		if (row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col] == -chessMap[row][col])
			break;
	}
	if (num > 4 && chessMap[row][col] == 1)
	{
		ban = MessageBox(hnd, "���ֽ���", "������ֳ�������", MB_OKCANCEL);
		return false;
	}

	num = 0;
	for (int i = 1; i < 5; i++)
	{//�᷽����
		if (col - i >= 0 && col + i < gradeSize && chessMap[row][col + i] == chessMap[row][col])
			num++;
		if (col - i >= 0 && col + i < gradeSize && chessMap[row][col - i] == chessMap[row][col])
			num++;
		if (col - i >= 0 && col + i < gradeSize && chessMap[row][col + i] == -chessMap[row][col])
			break;
		if (col - i >= 0 && col + i < gradeSize && chessMap[row][col - i] == -chessMap[row][col])
			break;
	}
	if (num > 4 && chessMap[row][col] == 1)
	{
		ban = MessageBox(hnd, "���ֽ���", "������ֳ�������", MB_OKCANCEL);
		return false;
	}
	num = 0;
	for (int i = 1; i < 5; i++)
	{//���Խ��߷���
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col + i] == chessMap[row][col])
			num++;
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row + i][col - i] == chessMap[row][col])
			num++;
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col + i] == -chessMap[row][col])
			break;
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row + i][col - i] == -chessMap[row][col])
			break;
	}
	if (num > 4 && chessMap[row][col] == 1)
	{
		ban = MessageBox(hnd, "���ֽ���", "������ֳ�������", MB_OKCANCEL);
		return false;
	}

	for (int i = 1; i < 5; i++)
	{//���Խ��߷���
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row + i][col + i] == chessMap[row][col])
			num++;
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col - i] == chessMap[row][col])
			num++;
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row + i][col + i] == -chessMap[row][col])
			break;
		if (col - i >= 0 && col + i < gradeSize && row - i >= 0 && row + i <= gradeSize && chessMap[row - i][col - i] == -chessMap[row][col])
			break;
	}
	if (num > 4 && chessMap[row][col] == 1)
	{
		ban = MessageBox(hnd, "���ֽ���", "������ֳ�������", MB_OKCANCEL);
		return false;
	}


	// ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	for (int i = 0; i < 5; i++)
	{
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// ��ֱ����(��������4��)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
			return true;
	}

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
			return true;
	}
	//���ִ������� �����㸺
	int tree = 0;//�ж���������
	int four = 0;//�ж����Ľ���
	for (int y = -1; y <= 0; y++)
	{        //Y�ķ�Χ����-1�� 0
		for (int x = -1; x <= 1; x++)
		{    //X�ķ�Χ�� -1,0,1
			if (y == 0 && x == 0) continue;
			if (y == 0 && x != 1) continue; //��y=0ʱ��������x=1
			// ��������ڸ�λ�����ӣ��ṹ��ʲô����
			int personNum = 0;
			int emptyNum = 0;
			for (int i = 1; i <= 4; i++)
			{
				int curRow = row + i * y;
				int curCol = col + i * x;

				if (curRow >= 0 && curRow < gradeSize &&
					curCol >= 0 && curCol < gradeSize &&//����
					chessMap[curRow][curCol] == 1) {
					personNum++;
				}
				else if (curRow >= 0 && curRow < gradeSize &&
					curCol >= 0 && curCol < gradeSize &&
					chessMap[curRow][curCol] == 0) {
					emptyNum++;
					break;
				}
				else {
					break;
				}
			}

			// �����������
			for (int i = 1; i <= 4; i++)
			{
				int curRow = row - i * y;
				int curCol = col - i * x;

				if (curRow >= 0 && curRow < gradeSize &&
					curCol >= 0 && curCol < gradeSize &&
					chessMap[curRow][curCol] == 1) {
					personNum++;
				}
				else if (curRow >= 0 && curRow < gradeSize &&
					curCol >= 0 && curCol < gradeSize &&
					chessMap[curRow][curCol] == 0) {
					emptyNum++;
					break;
				}
				else {
					break;
				}
			}
			if (personNum == 2 && emptyNum == 2)//����
			{
				tree++;
			}
			else if (personNum == 3 && emptyNum == 2)//����
			{
				four++;
			}
		}
	}
	if (tree >= 2 && chessMap[row][col] == 1)//��������
	{
		ban = MessageBox(hnd, "���ֽ���", "������ֽ���", MB_OKCANCEL);
		return false;
	}
	if (four >= 2 && chessMap[row][col] == 1)//���Ľ���
	{
		ban = MessageBox(hnd, "���ֽ���", "������ֽ���", MB_OKCANCEL);
		return false;
	}
	if (num > 255)	return true;

	return false;

}

bool Chess::checkOver()
{
	if (checkWin()) {
		//��ȡ���ھ��
		HWND hnd = GetHWnd();
		if (num > 255) { //ƽ��
			int is_ok = MessageBox(hnd, "ƽ��", "�Ծֽ���", MB_OKCANCEL);
			save();
			return true;
		}
		if (playerFlag == false) {  //����Ӯ�����Ӯ��,��ʱ����Ѿ���ת���ֵ���������
			int is_ok = MessageBox(hnd, "����ʤ", "�Ծֽ���", MB_OKCANCEL);
			save();
			return true;
		}
		else {
			int is_ok = MessageBox(hnd, "����ʤ", "�Ծֽ���", MB_OKCANCEL);
			save();
			return true;
		}
		
		
	}
	
	return false;
}

bool Chess::get_playerFlag()
{
	return playerFlag;
}

int Chess::get_step()
{
	return num;
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

ChessPos Chess::lastpos()
{
	num--;
	ChessPos temp;
	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (step[i][j].step == num) {
				temp.row = i;
				temp.col = j;
				break;
			}
		}
	}
	num++;
	return temp;
}

ChessPos Chess::appointpos(int n)
{
	ChessPos temp;
	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (step[i][j].step == n) {
				temp.row = i;
				temp.col = j;
				break;
			}
		}
	}
	return temp;
}

bool Chess::isretrack()
{
	return retrack;
}

void Chess::save()
{
	num--;
	ChessPos p;
	/*std::ofstream outfile;
	std::cout << "���ļ�" << std::endl;
	outfile.open("C:\Users\Doctor\Desktop\��������Ĵ���\������ 2023.11.15 21.30\�����ļ�.txt", ios::out);*/
	char colour = 'B';
	for (int s = 0; s < num; s++) {
		p.row = appointpos(s).row;
		p.col = appointpos(s).col;
		if (step[p.row][p.col].kind == CHESS_WHITE)	colour = 'A';
		else if (step[p.row][p.col].kind == CHESS_WHITE)	colour = 'B';
		/*outfile << colour << "(" << ch_col[p.col] << "," << ch_row[p.row] << ");";*/
		std::cout << colour << "(" << ch_col[p.col] << "," << ch_row[p.row] << ");" << std::endl;
	}
	/*std::cout << "д��ɹ�" << std::endl;
	outfile.close();
	std::cout << "�ر��ļ�" << std::endl;*/
}

void Chess::temp_ChessDown(ChessPos temp)
{
	//������������
	chessMap[temp.row][temp.col] = 1;
}

void Chess::temp_Retrack(ChessPos pos)
{
	chessMap[pos.row][pos.col] = 0;
}

void Chess::give_pos(int row, int col)
{
	std::cout << "{" << ch_col[col] << "," << ch_row[row] << "}" << std::endl;
}


