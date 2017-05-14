/*1650254 尤尧寅 计算机1班*/
#include"90-b1.h"
//end提示函数
bool end(int x, int y)
{
	setcolor(hout, 0, 7);
	if (x != -1 && y != -1)
		gotoxy(hout, x, y);
	cout << "请输入end返回菜单:            ";
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
void add_random_ball(int *temp)
{
	*temp = rand() % MAX_BALL + 1;
}
void random_ball_origin(int p, int a[][MAX_COLUMN], int *row, int *column)
{
	if (p != -1&& p!=11)
		shuru(row, column);
	for (int i = 0; i < *row; i++)
		for (int j = 0; j < *column; j++)
		{
			if (a[i][j] == 0)
			{
				add_random_ball(&a[i][j]);
				if (p == 11)
				{
					printf_ball(a[i][j],(j + 1) * 4 - 2 , (i + 1) * 2 - 1);
					Sleep(SPEED);
				}
			}
		}
}
void shuru(int *a, int *b)
{
	system("cls");
	while (1)
	{
		gotoxy(hout, 0, 0);
		cout << "请输入行数(5-9)：                ";
		gotoxy(hout, 18, 0);
		*a = _getch() - '0';
		cout << *a;
		if (*a >= 5 && *a <= 9)
			break;
	}
	while (1)
	{
		gotoxy(hout, 0, 2);
		cout << "请输入列数(5-9)：               ";
		gotoxy(hout, 18, 2);
		*b = _getch() - '0';
		cout << *b;
		if (*b >= 5 && *b <= 9)
			break;
	}
	cout << endl;
}
void output(char *name)
{
	cout << name;
	while (1)
		if (_getch() == '\r')
			break;
}
int judge_delete(int row, int column, int a[][MAX_COLUMN], int click_x, int click_y, int count)
{
	int sum = 1;
	int i = click_x + step[count][0];
	int j = click_y + step[count][1];
	while (i >= 0 && i < row&&j >= 0 && j < column)
	{
		if (a[i][j] == a[click_x][click_y])
			sum++;
		else
			break;
		i += step[count][0];
		j += step[count][1];
	}
	i = click_x - step[count][0];
	j = click_y - step[count][1];
	while (i >= 0 && i < row&&j >= 0 && j < column)
	{
		if (a[i][j] == a[click_x][click_y])
			sum++;
		else
			break;
		i -= step[count][0];
		j -= step[count][1];
	}
	if (sum >= 3)
		return sum;
	else
		return 0;
}
int judge_color(int row, int column, int a[][MAX_COLUMN], int click_x, int click_y, int count, int book[][MAX_COLUMN])
{
	int sum = 1;
	int i = click_x + step[count][0];
	int j = click_y + step[count][1];
	book[click_x][click_y] = a[click_x][click_y];
	while (i >= 0 && i < row&&j >= 0 && j < column)
	{
		if (a[i][j] == a[click_x][click_y])
			book[i][j] = a[i][j];
		else
			break;
		i += step[count][0];
		j += step[count][1];
	}
	i = click_x - step[count][0];
	j = click_y - step[count][1];
	while (i >= 0 && i < row&&j >= 0 && j < column)
	{
		if (a[i][j] == a[click_x][click_y])
			book[i][j] = a[i][j];
		else
			break;
		i -= step[count][0];
		j -= step[count][1];
	}
	return 0;
}
int delete_ball(int row, int column, int a[][MAX_COLUMN], int book[][MAX_COLUMN])
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			if (book[i][j] == a[i][j])
				a[i][j] = 0;
	return 0;
}
int down_ball(int row, int column, int a[][MAX_COLUMN])
{
	for (int i = row - 1; i > 0; i--)
		for (int j = 0; j < column; j++)
		{
			if (a[i][j] == 0)
			{
				int temp = i - 1;
				while (1)
				{
					if (a[temp][j] != 0||temp==0)
						break;
					temp--;
				}
				a[i][j] = a[temp][j];
				a[temp][j] = 0;
			}
		}
	return 0;
}
int reset(int a[][MAX_COLUMN])
{
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			a[i][j] = 0;
	return 0;
}
int all_judge(int row, int column, int a[][MAX_COLUMN], int book[][MAX_COLUMN])
{
	int flag = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			for (int count = 0; count < 2; count++)
			{
				if (judge_delete(row, column, a, i, j, count))
				{
					flag = 1;
					judge_color(row, column, a, i, j, count, book);
				}
			}
	return flag;
}
void set_sign(int book[][MAX_COLUMN],int a[][MAX_COLUMN])
{
	for(int i=0;i<MAX_ROW;i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			if (a[i][j] == 0)
				book[i][j] = 1;
}
int autojudge(int row, int column, int a[][MAX_COLUMN],int book[][MAX_COLUMN],int moveable[][MAX_COLUMN])
{
	int ball_step[4][2] = { {0,1},{0,-1},{1,0} ,{-1,0} };
	int flag = 0;
	for (int i = 0; i<row; i++)
		for (int j = 0; j < column; j++)
			for (int m = 0; m < 4; m++)
				if (i + ball_step[m][0] >= 0 && i + ball_step[m][0] < row&&j + ball_step[m][1] >= 0 && j + ball_step[m][1] < column)
				{
					int temp;
					temp = a[i + ball_step[m][0]][j + ball_step[m][1]];
					a[i + ball_step[m][0]][j + ball_step[m][1]] = a[i][j];
					a[i][j] = temp;
					if (all_judge(row, column, a, book))
					{
						moveable[i][j] = 1;
						flag = 1;
					}
					temp = a[i + ball_step[m][0]][j + ball_step[m][1]];
					a[i + ball_step[m][0]][j + ball_step[m][1]] = a[i][j];
					a[i][j] = temp;
				}
	return flag;
}
int cal_defeng(int book[][MAX_COLUMN])
{
	int sum = 0;
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			if (book[i][j] != 0)
				sum++;
	return sum;
}