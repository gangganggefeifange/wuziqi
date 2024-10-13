#include "Chess.h"
#include <conio.h>

void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
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
		int offset = (int)(chessSize * 0.4); // 20 鼠标点击的模糊距离上限

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

			// 距离右上角的距离
			len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
			if (len < offset) {
				pos->row = row;
				pos->col = col + 1;
				if (chessMap[pos->row][pos->col] == 0) {
					selectPos = true;
				}
				break;
			}

			// 距离左下角的距离
			len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
			if (len < offset) {
				pos->row = row + 1;
				pos->col = col;
				if (chessMap[pos->row][pos->col] == 0) {
					selectPos = true;
				}
				break;
			}

			// 距离右下角的距离
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
	loadimage(0, "res/棋盘.png");
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
	loadimage(0, "res/棋盘.png");
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
	//更改棋盘数据
	step[pos.row][pos.col].step = num;
	step[pos.row][pos.col].kind = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	chessMap[pos.row][pos.col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	//0std::cout << "步数：" << num << "坐标：" << pos.row << "," << pos.col << std::endl;
	give_pos(pos.row, pos.col);
	num++;	//步数+1
	retrack = false;//	更改悔棋标志
	playerFlag = !playerFlag;//换手
	PrintChess();
}

void Chess::Retrack(ChessPos pos)
{
	num--;//步数-1
	retrack = true;//	更改悔棋标志
	//更改棋盘数据
	step[pos.row][pos.col].step = 0;
	step[pos.row][pos.col].kind = CHESS_NONE;
	chessMap[pos.row][pos.col] = 0;
	//playerFlag = !playerFlag;//换手
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
	//获取窗口句柄
	HWND hnd = GetHWnd();
	is_change = MessageBox(hnd, "进行三手交换", "三手交换", MB_OKCANCEL);
}


bool Chess::checkWin()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	int ban;
	// 水平方向
	int row = lastpos().row;
	int col = lastpos().col;

	//长连禁手
	int num = 0;
	for (int i = 1; i < 5; i++)
	{//竖方向上
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
		ban = MessageBox(hnd, "出现禁手", "黑棋出现长连禁手", MB_OKCANCEL);
		return false;
	}

	num = 0;
	for (int i = 1; i < 5; i++)
	{//横方向上
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
		ban = MessageBox(hnd, "出现禁手", "黑棋出现长连禁手", MB_OKCANCEL);
		return false;
	}
	num = 0;
	for (int i = 1; i < 5; i++)
	{//正对角线方向
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
		ban = MessageBox(hnd, "出现禁手", "黑棋出现长连禁手", MB_OKCANCEL);
		return false;
	}

	for (int i = 1; i < 5; i++)
	{//反对角线方向
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
		ban = MessageBox(hnd, "出现禁手", "黑棋出现长连禁手", MB_OKCANCEL);
		return false;
	}


	// 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
	for (int i = 0; i < 5; i++)
	{
		// 往左5个，往右匹配4个子，20种情况
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// 竖直方向(上下延伸4个)
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

	// “/"方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			// 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// “\“ 方向
	for (int i = 0; i < 5; i++)
	{
		// 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
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
	//禁手处不能下 下子算负
	int tree = 0;//判断三三禁手
	int four = 0;//判断四四禁手
	for (int y = -1; y <= 0; y++)
	{        //Y的范围还是-1， 0
		for (int x = -1; x <= 1; x++)
		{    //X的范围是 -1,0,1
			if (y == 0 && x == 0) continue;
			if (y == 0 && x != 1) continue; //当y=0时，仅允许x=1
			// 假设黑棋在该位置落子，会构成什么棋型
			int personNum = 0;
			int emptyNum = 0;
			for (int i = 1; i <= 4; i++)
			{
				int curRow = row + i * y;
				int curCol = col + i * x;

				if (curRow >= 0 && curRow < gradeSize &&
					curCol >= 0 && curCol < gradeSize &&//黑子
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

			// 反向继续计算
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
			if (personNum == 2 && emptyNum == 2)//活三
			{
				tree++;
			}
			else if (personNum == 3 && emptyNum == 2)//活四
			{
				four++;
			}
		}
	}
	if (tree >= 2 && chessMap[row][col] == 1)//三三禁手
	{
		ban = MessageBox(hnd, "出现禁手", "黑棋出现禁手", MB_OKCANCEL);
		return false;
	}
	if (four >= 2 && chessMap[row][col] == 1)//四四禁手
	{
		ban = MessageBox(hnd, "出现禁手", "黑棋出现禁手", MB_OKCANCEL);
		return false;
	}
	if (num > 255)	return true;

	return false;

}

bool Chess::checkOver()
{
	if (checkWin()) {
		//获取窗口句柄
		HWND hnd = GetHWnd();
		if (num > 255) { //平局
			int is_ok = MessageBox(hnd, "平局", "对局结束", MB_OKCANCEL);
			save();
			return true;
		}
		if (playerFlag == false) {  //黑棋赢（玩家赢）,此时标记已经反转，轮到白棋落子
			int is_ok = MessageBox(hnd, "黑棋胜", "对局结束", MB_OKCANCEL);
			save();
			return true;
		}
		else {
			int is_ok = MessageBox(hnd, "白棋胜", "对局结束", MB_OKCANCEL);
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
	std::cout << "打开文件" << std::endl;
	outfile.open("C:\Users\Doctor\Desktop\计算机博弈大赛\五子棋 2023.11.15 21.30\棋谱文件.txt", ios::out);*/
	char colour = 'B';
	for (int s = 0; s < num; s++) {
		p.row = appointpos(s).row;
		p.col = appointpos(s).col;
		if (step[p.row][p.col].kind == CHESS_WHITE)	colour = 'A';
		else if (step[p.row][p.col].kind == CHESS_WHITE)	colour = 'B';
		/*outfile << colour << "(" << ch_col[p.col] << "," << ch_row[p.row] << ");";*/
		std::cout << colour << "(" << ch_col[p.col] << "," << ch_row[p.row] << ");" << std::endl;
	}
	/*std::cout << "写入成功" << std::endl;
	outfile.close();
	std::cout << "关闭文件" << std::endl;*/
}

void Chess::temp_ChessDown(ChessPos temp)
{
	//更改棋盘数据
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


