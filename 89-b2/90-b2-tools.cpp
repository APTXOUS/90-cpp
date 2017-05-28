/*1650254 尤尧寅 计1*/
//存放公用函数]
#include"90-b2.h"
int CHange_array(int root[][MAX_SPACE], int step[][MAX_COLUMN], int start_x, int start_y, int end_x, int end_y)
{
	root[0][0] = end_x;
	root[1][0] = end_y;
	int tail = 0;
	while (1)
	{

		root[0][tail + 1] = root[0][tail] - a_step[step[root[0][tail]][root[1][tail]] - 1][0];
		root[1][tail + 1] = root[1][tail] - a_step[step[root[0][tail]][root[1][tail]] - 1][1];
		tail++;
		if (root[0][tail] == start_x&&root[1][tail] == start_y)
			break;
	}
	int i = 0, j = tail;
	while (i < j)
	{
		int temp[2];
		temp[0] = root[0][i];
		temp[1] = root[1][i];
		root[0][i] = root[0][j];
		root[1][i] = root[1][j];
		root[0][j] = temp[0];
		root[1][j] = temp[1];
		i++;
		j--;
	}
	root[0][tail + 1] = -1;
	root[1][tail + 1] = -1;
	return 0;
}
void reform(int step[][MAX_COLUMN], int root[][MAX_SPACE])
{
	for (int i = 0; i < MAX_LOW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			step[i][j] = 0;
	int i = 0;
	while (root[0][i] != -1)
	{
		step[root[0][i]][root[1][i]] = 1;
		i++;
	}
}
int BFS(int low, int column, int a[][MAX_COLUMN], int start_x, int start_y, int end_x, int end_y, int step[][MAX_COLUMN], int rout[][MAX_SPACE])
{
	int a_num[MAX_LOW][MAX_COLUMN] = { 0 }, quene[3][MAX_SPACE], head = 0, tail = 0;
	quene[0][tail] = start_x;
	quene[1][tail] = start_y;
	quene[2][tail++] = 0;
	a_num[start_x][start_y] = 1;
	bool flag = 0;
	while (head < tail)
	{
		for (int i = 0; i < 4; i++)
		{
			int temp_x = quene[0][head] + a_step[i][0], temp_y = quene[1][head] + a_step[i][1];
			if (temp_x < 0 || temp_x >= low || temp_y < 0 || temp_y >= column)
				continue;
			if (a[temp_x][temp_y] == 0 && a_num[temp_x][temp_y] == 0)
			{
				a_num[temp_x][temp_y] = 1;
				quene[0][tail] = temp_x;
				quene[1][tail] = temp_y;
				quene[2][tail++] = quene[2][head] + 1;
				step[temp_x][temp_y] = i + 1;
			}
			if (temp_x == end_x&&temp_y == end_y)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
		head++;
	}
	if (flag == 1)
		return 1;
	else
		return 0;
}
//判断移动后是否消除小球
int judge_delete_low(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y)
{
	int sum = 1;
	if (click_x != 0)
		for (int i = click_x - 1; i >= 0; i--)
			if (a[i][click_y] == a[click_x][click_y])
				sum++;
			else
				break;

	if (click_x != low - 1)
		for (int i = click_x + 1; i < low; i++)
			if (a[i][click_y] == a[click_x][click_y])
				sum++;
			else
				break;
	if (sum >= 5)
		return sum;
	else
		return 0;
}
int judge_delete_column(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y)
{
	int sum = 1;
	if (click_y != 0)
		for (int i = click_y - 1; i >= 0; i--)
			if (a[click_x][i] == a[click_x][click_y])
				sum++;
			else
				break;
	if (click_y != column - 1)
		for (int i = click_y + 1; i < column; i++)
			if (a[click_x][i] == a[click_x][click_y])
				sum++;
			else
				break;
	if (sum >= 5)
		return sum;
	else
		return 0;
}
int judge_delete_angle(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y)
{
	int sum = 1;
	if (click_x != 0 || click_y != 0)
		for (int i = click_x - 1, j = click_y - 1; i >= 0, j >= 0; i--, j--)
			if (a[i][j] == a[click_x][click_y])
				sum++;
			else
				break;
	if (click_x != low - 1 || click_y != column - 1)
		for (int i = click_x + 1, j = click_y + 1; i < low, j < column; i++, j++)
			if (a[i][j] == a[click_x][click_y])
				sum++;
			else
				break;
	if (sum >= 5)
		return sum;
	else
		return 0;
}
int judge_delete_angle_anti(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y)
{
	int sum = 1;
	if (click_x != 0 || click_y != column - 1)
		for (int i = click_x - 1, j = click_y + 1; i >= 0, j >= 0; i--, j++)
			if (a[i][j] == a[click_x][click_y])
				sum++;
			else
				break;
	if (click_x != low - 1 || click_y != 0)
		for (int i = click_x + 1, j = click_y - 1; i < low, j < column; i++, j--)
			if (a[i][j] == a[click_x][click_y])
				sum++;
			else
				break;
	if (sum >= 5)
		return sum;
	else
		return 0;
}
void delete_ball(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y, int temp1, int temp2, int temp3, int temp4)
{
	if (temp1)
	{
		if (click_x != 0)
			for (int i = click_x - 1; i >= 0; i--)
				if (a[i][click_y] == a[click_x][click_y])
					a[i][click_y] = 0;
				else
					break;
		if (click_x != low - 1)
			for (int i = click_x + 1; i < low; i++)
				if (a[i][click_y] == a[click_x][click_y])
					a[i][click_y] = 0;
				else
					break;
	}
	if (temp2)
	{
		if (click_y != 0)
			for (int i = click_y - 1; i >= 0; i--)
				if (a[click_x][i] == a[click_x][click_y])
					a[click_x][i] = 0;
				else
					break;
		if (click_y != column - 1)
			for (int i = click_y + 1; i < column; i++)
				if (a[click_x][i] == a[click_x][click_y])
					a[click_x][i] = 0;
				else
					break;
	}
	if (temp3)
	{
		if (click_x != 0 || click_y != 0)
			for (int i = click_x - 1, j = click_y - 1; i >= 0, j >= 0; i--, j--)
				if (a[i][j] == a[click_x][click_y])
					a[i][j] = 0;
				else
					break;
		if (click_x != low - 1 || click_y != column - 1)
			for (int i = click_x + 1, j = click_y + 1; i < low, j < column; i++, j++)
				if (a[i][j] == a[click_x][click_y])
					a[i][j] = 0;
				else
					break;
	}
	if (temp4)
	{
		if (click_x != 0 || click_y != column - 1)
			for (int i = click_x - 1, j = click_y + 1; i >= 0, j >= 0; i--, j++)
				if (a[i][j] == a[click_x][click_y])
					a[i][j] = 0;
				else
					break;
		if (click_x != low - 1 || click_y != 0)
			for (int i = click_x + 1, j = click_y - 1; i < low, j < column; i++, j--)
				if (a[i][j] == a[click_x][click_y])
					a[i][j] = 0;
				else
					break;
	}
}

int judge_delete_ball_aftermove(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y)
{
	int temp1 = judge_delete_low(low, column, a, click_x, click_y);
	int temp2 = judge_delete_column(low, column, a, click_x, click_y);
	int temp3 = judge_delete_angle(low, column, a, click_x, click_y);
	int temp4 = judge_delete_angle_anti(low, column, a, click_x, click_y);
	delete_ball(low, column, a, click_x, click_y, temp1, temp2, temp3, temp4);
	if (temp1 != 0 || temp2 != 0 || temp3 != 0 || temp4 != 0)
		a[click_x][click_y] = 0;
	return temp1 + temp2 + temp3 + temp4;
}
//end提示函数
bool end(int x, int y)
{
	setcolor(hout, 0, 7);
	if (x != -1 && y != -1)
		gotoxy(hout, x, y);
	cout << "请输入end返回菜单:";
	while (1)
	{
		char ans[100];
		cin >> ans;
		if ((ans[0] == 'e' || ans[0] == 'E') && (ans[1] == 'n' || ans[1] == 'N') && (ans[2] == 'd' || ans[2] == 'D'))
			break;
		else
		{
			gotoxy(hout, x, y);
			cout << "请输入end返回菜单:                                            ";
			gotoxy(hout, x + 18, y);
		}
	}
	return 1;
}
void shuru(int *a, int *b)
{
	system("cls");
	while (1)
	{
		gotoxy(hout, 0, 0);
		cout << "请输入行数(7-9)：                ";
		gotoxy(hout, 18, 0);
		*a = _getch() - '0';
		cout << *a;
		if (*a >= 7 && *a <= 9)
			break;
	}
	while (1)
	{
		gotoxy(hout, 0, 2);
		cout << "请输入列数(7-9)：               ";
		gotoxy(hout, 18, 2);
		*b = _getch() - '0';
		cout << *b;
		if (*b >= 7 && *b <= 9)
			break;
	}
	cout << endl;
}
int check_win_lose(int a[][MAX_COLUMN], int low, int column)
{
	int sum = 0;
	for (int i = 0; i < low; i++)
		for (int j = 0; j < column; j++)
			if (a[i][j] == 0)
				sum++;
	if (sum == 0)
		return -1;
	else if (sum == low*column)
		return 0;
	else
		return 1;
}
//加入随机小球
void add_random_ball(int n, int low, int col, int a[][MAX_COLUMN], int *x)
{
	int sum = 0;
	for (int i = 0; i < low; i++)
		for (int j = 0; j < col; j++)
			if (a[i][j] == 0)
				sum++;
	for (int i = 0; i < n; i++)
	{
		int temp_x = rand(), temp_y = rand();
		if (a[temp_x%low][temp_y%col] == 0)
			a[temp_x%low][temp_y%col] = *(x + i) + 1;
		else
			i--;
		if (i + 1 == sum)
			break;
		if (n == 3)
			judge_delete_ball_aftermove(low, col, a, temp_x%low, temp_y%col);
	}
}
bool check_60(int p, int a[][MAX_COLUMN], int low, int column, double c)
{
	int sum = low*column;
	for (int i = 0; i < low; i++)
		for (int j = 0; j < column; j++)
			if (a[i][j] == 0)
				sum--;
	if (sum >= (low*column*c))
		return 1;
	else
		return 0;
}
void random_ball_origin(int p, int a[][MAX_COLUMN], int *low, int *column)
{
	if (p != -1)
		shuru(low, column);
	int b[MAX_BALL_ORI];
	for (int i = 0; i < MAX_BALL_ORI; i++)
		b[i] = rand() % MAX_BALL;
	add_random_ball(MAX_BALL_ORI, *low, *column, a, b);
}
/***************************************************************************
函数名称：
功    能：读鼠标按键
输入参数：const HANDLE hout ：cmd窗口句柄
返 回 值：
说    明：下列说明来自鼠标定义文件
01.typedef struct _MOUSE_EVENT_RECORD      //鼠标事件结构体
02.{
03.    COORD dwMousePosition;      //当前鼠标在控制台窗口缓冲区的位置
04.    DWORD dwButtonState;        //鼠标按键的状态
05.    DWORD dwControlKeyState;    //控制键状态
06.    DWORD dwEventFlags;         //鼠标事件类型
07.} MOUSE_EVENT_RECORD;
08.
09.其中鼠标按键状态dwButtonState可能的值有
10.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
11.FROM_LEFT_1ST_BUTTON_PRESSED        最左边的鼠标键被按下      一般来说就是鼠标左键
12.FROM_LEFT_2ND_BUTTON_PRESSED        左起第二个鼠标键被按下    一般来说是鼠标中键，就是滚轮键
13.FROM_LEFT_3RD_BUTTON_PRESSED        左起第三个鼠标键被按下
14.FROM_LEFT_4TH_BUTTON_PRESSED        左起第四个鼠标键被按下
15.RIGHTMOST_BUTTON_PRESSED            最右边的鼠标键被按下      一般来说是鼠标右键
16.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
17.控制键状态dwControlKeyState与键盘事件的一样
18.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
19.ENHANCED_KEY        扩展键被按下
20.LEFT_ALT_PRESSED    左Alt键被按下
21.LEFT_CTRL_PRESSED   左Ctrl键被按下
22.RIGHT_ALT_PRESSED   右Alt键被按下
23.RIGHT_CTRL_PRESSED  右Ctrl键被按下
24.NUMLOCK_ON          数字锁定被打开
25.SCROLLLOCK_ON       滚动锁定被打开
26.CAPSLOCK_ON         大写锁定被打开
27.SHIFT_PRESSED       Shift键被按下
28.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
29.鼠标事件类型dwEventFlags有以下几种
30.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
31.DOUBLE_CLICK            双击，第一击只作为普通按键事件，第二击才作为双击事件
32.MOUSE_HWHEELED          水平鼠标滚轮移动
33.MOUSE_MOVED             鼠标移动
34.MOUSE_WHEELED           垂直鼠标滚轮移动
35.0                       当鼠标有键被按下或者释放
***************************************************************************/
int read_mouse_and_key(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{
	INPUT_RECORD    mouse_keyRec;
	DWORD           res;
	COORD           crPos;

	while (1) {
		/* 从hin中读输入状态（包括鼠标、键盘等） */

		ReadConsoleInput(hin, &mouse_keyRec, 1, &res);
		if (mouse_keyRec.Event.KeyEvent.bKeyDown == 1)
		{
			if (mouse_keyRec.Event.KeyEvent.wVirtualKeyCode == 0x72)
				return -1;
			if (mouse_keyRec.Event.KeyEvent.wVirtualKeyCode == 0x73)
				return -2;
			if (mouse_keyRec.Event.KeyEvent.wVirtualKeyCode == 0x74)
				return -3;
		}
		if (mouse_keyRec.EventType != MOUSE_EVENT)
			continue;
		/* 从返回中读鼠标指针当前的坐标 */
		crPos = mouse_keyRec.Event.MouseEvent.dwMousePosition;
		X = crPos.X;
		Y = crPos.Y;
		if (enable_read_mouse_moved && mouse_keyRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			return MOUSE_ONLY_MOVED;

		if (mouse_keyRec.Event.MouseEvent.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)) { //同时按下左右键
			return MOUSE_LEFTRIGHT_BUTTON_CLICK;
		}
		else if (mouse_keyRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //按下左键
			if (mouse_keyRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_LEFT_BUTTON_CLICK;
		}
		else if (mouse_keyRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { //按下右键
			if (mouse_keyRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_RIGHT_BUTTON_CLICK;
		}
		else //忽略其它按键操作（如果需要滚轮，则判断 FROM_LEFT_2ND_BUTTON_PRESSED）
		{
			;

		}

	} //end of while(1)

	return MOUSE_NO_ACTION; //此句应该执行不到，为避免某些编译器报不完全分支错误，加
}
//菜单项9废弃代码
/*
int read_moused(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{

	static unsigned int t1 = 6;
	static unsigned int t2 = 6;
	static  int i1 = 6;
	static  int i2 = 6;
	static unsigned int before = 1;
	//pri(i1, i2);
	while (i1 == 6)
	{
		i1 = read_mouse2(hin, X, Y, 1);
		t1 = GetTickCount();
		if (i1 == 6)
			return 6;
	}
	while (before)
	{
		while (1)
		{
			t2 = GetTickCount();
			if ((GetTickCount()) < (t1 + 1001) || (i2 = read_mouse2(hin, X, Y, 1)) != 0)
				break;
		}
		if (t2-t1 < 1000)
		{
			before = 1;
			if (i1 == MOUSE_LEFT_BUTTON_CLICK&&i2 == MOUSE_LEFT_BUTTON_CLICK)
			{
				cout << i1<<i2;
				i1 = 6;
				i2 = 6;
				t2 = 6;
				t1 = 6;
				return MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
			}
			else if (i1 == MOUSE_RIGHT_BUTTON_CLICK&&i2 == MOUSE_RIGHT_BUTTON_CLICK)
			{
				cout << "1231312";
				i1 = 6;
				i2 = 6;
				t2 = 6;
				t1 = 6;

				return MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
			}
			else if (i1 == MOUSE_LEFT_BUTTON_CLICK&&i2 == MOUSE_RIGHT_BUTTON_CLICK)
			{
				cout << "1231313";
				i1 = 6;
				i2 = 6;
				t2 = 6;
				t1 = 6;
				return MOUSE_LEFTRIGHT_BUTTON_CLICK;
			}
			else if (i1 == MOUSE_RIGHT_BUTTON_CLICK&&i2 == MOUSE_LEFT_BUTTON_CLICK)
			{
				cout << "1231314";
				i1 = 6;
				i2 = 6;
				t2 = 6;
				t1 = 6;
				return MOUSE_LEFTRIGHT_BUTTON_CLICK;
			}
		}
		else if (t2 - t1 > 1000)
		{
			before = 1;
			cout << 2;
			int temp = i1;
			i1 = i2;
			t1 = t2;
			return temp;
		}
	}
}
int read_mouse2(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos;

	while (1) {
		ReadConsoleInput(hin, &mouseRec, 1, &res);
		if (mouseRec.EventType != MOUSE_EVENT)
			continue;
		crPos = mouseRec.Event.MouseEvent.dwMousePosition;
		X = crPos.X;
		Y = crPos.Y;
		if (enable_read_mouse_moved && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			return MOUSE_ONLY_MOVED;
		if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键按下
			return MOUSE_LEFT_BUTTON_CLICK;
		else if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键按下
			return MOUSE_RIGHT_BUTTON_CLICK;
		else
			return 0;

	} //end of while(1)

	return MOUSE_NO_ACTION; //此句应该执行不到，为避免某些编译器报不完全分支错误，加
}
*/