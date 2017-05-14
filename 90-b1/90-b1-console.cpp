/*1650254 尤尧寅 计算机1班*/
#include"90-b1.h"
void output_color(struct type_name vect)
{
	setcolor(hout, vect.back_color, vect.front_color);
	cout << vect.name;
	setcolor(hout, BASE_COLOR, BASE_WORD);
}
void color_origin(int p, int a[][MAX_COLUMN], int *row, int *column)
{
	setconsoleborder(hout, (int)(*column + 3) * 2 + 1 + 10, (int)(*row + 3) + 2);
	system("cls");
	setcursor(hout, CURSOR_INVISIBLE);
	setfontsize(hout, L"新宋体", 16);
	gotoxy(hout, 0, 0);
	for (int i = -1; i <= *row; i++)
	{
		for (int j = -1; j <= *column; j++)
		{
			setcolor(hout, BASE_COLOR, BASE_WORD);
			if (i == -1 && j == -1)
				output_color(line[0]);
			else if (i == *row &&j == -1)
				output_color(line[7]);
			else if (i == -1 && j == *column)
				output_color(line[3]);
			else if (i == *row &&j == *column)
				output_color(line[9]);
			else if (i == -1 || i == *row)
				output_color(line[1]);
			else if (j == -1 || j == *column)
				output_color(line[10]);
			else
				output_color(ball[a[i][j]]);
		}
		cout << endl;
	}

}
void color_origin_with(int p, int a[][MAX_COLUMN], int *row, int *column, int book[][MAX_COLUMN],int sign)
{
	
	gotoxy(hout, 0, 0);
	for (int i = 0; i < 2 * *row + 1; i++)
	{
		for (int j = 0; j < 2 * *column + 1; j++)
		{
			setcolor(hout, 15, 0);
			if (i == 0 && j == 0)
				output_color(line[0]);
			else if (i == 2 * *row&& j == 0)
				output_color(line[7]);
			else if (i == 0 && j == 2 * *column)
				output_color(line[3]);
			else if (i == 2 * *row && j == 2 * *column)
				output_color(line[9]);
			else if (i == 0 && j % 2 == 0)
				output_color(line[2]);
			else if (i == 2 * *row && j % 2 == 0)
				output_color(line[8]);
			else if (i % 2 == 0 && j == 0)
				output_color(line[4]);
			else if (i % 2 == 0 && j == 2 * *column)
				output_color(line[6]);
			else if (i % 2 != 0 && j % 2 == 0)
				output_color(line[10]);
			else if (i % 2 == 0 && j % 2 != 0)
				output_color(line[1]);
			else if (i % 2 == 0 && j % 2 == 0 && i != 2 * *row && j != 2 * *column)
				output_color(line[5]);
			else
			{
				//getchar();
				if (i % 2 != 0 && j % 2 != 0 && j < 2 * * column && i < 2 * * row)
				{
					if (sign == 0)
					{
						if (book[(i - 1) / 2][(j - 1) / 2] != 0)
							output_color(ball_signed[a[(i - 1) / 2][(j - 1) / 2]]);
						else
							output_color(ball[a[(i - 1) / 2][(j - 1) / 2]]);
					}
					else
					{
						if (book[(i - 1) / 2][(j - 1) / 2] != 0)
						{
							output_color(signedball[a[(i - 1) / 2][(j - 1) / 2]]);
						}
						else
						{
							output_color(ball[a[(i - 1) / 2][(j - 1) / 2]]);

						}
					}
				}
			}
		}
		cout << endl;
	}
}
void down_ball_color(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	for (int i = *row - 1; i > 0; i--)
		for (int j = 0; j < *column; j++)
		{
			if (a[i][j] == 0)
			{
				int temp = i;
				while (1)
				{
					if (a[temp][j] != 0 || temp == 0)
						break;
					temp--;
				}
				if ((i != temp)&& !((a[temp][j] == 0 && temp == 0)))
				{
					move_ball(p, a, row, column, i, j, temp);
					a[i][j] = a[temp][j];
					a[temp][j] = 0;
				}
			}
		}
}
void move_ball(int p,int a[][MAX_COLUMN],int *row,int *column,int end,int now,int start)
{
	int i = start;
	int j = now;
	while (1)
	{
		if (i == end)
			break;
		int x=2*(i+1)-1;
		int y=(j+1)*4-2;
		while (1)
		{
			cal(y, x, *row, *column);
			x++;
			printf_ball(a[start][now], y,x);
			if ((x+1) % 2 == 0)
				break;
			Sleep(SPEED);
		}
		Sleep(SPEED);
		i++;
	}
}
int cal(int i, int j, int row, int column)
{
	gotoxy(hout, i, j);
	if (i % 4 == 0)
		output_color(line[10]);
	else if (j % 2 == 0)
		output_color(line[1]);
	else
		output_color(ball[0]);
	return 0;
}
void printf_ball(int a, int x, int y)
{
	gotoxy(hout, x, y);
	output_color(ball[a]);
}
void printf_ball_signed(int a, int x, int y)
{
	gotoxy(hout, x, y);
	output_color(ball_signed[a]);
}
int ball_moveable(int p, int(*a)[MAX_COLUMN], int *row, int *column,int record[][MAX_COLUMN],int moveable[][MAX_COLUMN])
{
	int flag = autojudge(*row, *column, a, record, moveable);
	if (!flag)
	{
		gotoxy(hout, 0, 2 * *row + 1);
		cout << "没有可以消除的项！       \n";
		end(0, 2 * *row + 1 + 1);
		return flag;
	}
	else
		color_origin_with(p, a, row, column, moveable, 1);
	return flag;
}
void read_x_y(int p, int a[][MAX_COLUMN], int low, int column, int *X, int *Y, int *action, int *loop)
{
	enable_mouse(hin);
	*action = read_mouse(hin, *X, *Y);
	//if(p==9)
	//	*action = read_moused(hin, *X, *Y, 1);
	if (*X % 4 == 2)
		*X = *X + 1;
	if ((*X + 1) % 4 == 0 && (*Y - 1) % 2 == 0 && *X <= 4 * column&&*Y <= 2 * low)
	{
		gotoxy(hout, 0, 2 * low + 1);
		cout << "[当前光标位置]" << setw(2) << (char)((*Y - 1) / 2 + 'A') << " 行" << setw(2) << (*X + 1) / 4 << "列" << *action;
		*Y = (*Y - 1) / 2;
		*X = (*X + 1) / 4 - 1;
	}
}
int read_loop(int p,int a[][MAX_COLUMN],int *row,int *column,int *start_y,int *start_x,int *action, int *loop,int moveable[][MAX_COLUMN])
{
	while (1)
	{
		read_x_y(p, a, *row, *column, start_y, start_x, action, loop);
		if (*action == MOUSE_LEFT_BUTTON_CLICK&&*start_x < *row&&*start_y < *column&& moveable[*start_x][*start_y] != 0)
			break;
		else if (*action == MOUSE_RIGHT_BUTTON_CLICK)
			return -1;
	}
	return 0;
}
void exchange_ball(int p, int a[][MAX_COLUMN], int low, int column, int *start_x, int *start_y,int *end_x,int *end_y )
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int temp = a[*end_x][*end_y];
	a[*end_x][*end_y] = a[*start_x][*start_y];
	a[*start_x][*start_y] = temp;
	if (!all_judge(low, column, a, record))
	{
		temp = a[*end_x][*end_y];
		a[*end_x][*end_y] = a[*start_x][*start_y];
		a[*start_x][*start_y] = temp;
		return;
	}
	if (*end_x == *start_x)
	{
		Sleep(SPEED*2);
		printf_ball(a[*end_x][*end_y], (*start_y + 1) * 4 - 2, (*start_x + 1) * 2 - 1);
		cal(((*start_y + 1) * 4 - 2 + (*end_y + 1) * 4 - 2) / 2, (*start_x + 1) * 2 - 1, low, column);
		printf_ball(a[*start_x][*start_y], (*end_y + 1) * 4 - 2, (*end_x + 1) * 2 - 1);
		Sleep(SPEED * 2);
		printf_ball(0, (*start_y + 1) * 4 - 2, (*start_x + 1) * 2 - 1);
		printf_ball(11, ((*start_y + 1) * 4 - 2 + (*end_y + 1) * 4 - 2) / 2, (*start_x + 1) * 2 - 1);
		printf_ball(0, (*end_y + 1) * 4 - 2, (*end_x + 1) * 2 - 1);
		Sleep(SPEED * 2);
	}
	if (*end_y == *start_y)
	{
		Sleep(SPEED * 2);
		printf_ball(a[*end_x][*end_y], (*start_y + 1) * 4 - 2, (*start_x + 1) * 2 - 1);
		cal((*start_y + 1) * 4 - 2, ((*start_x + 1) * 2 - 1 + (*end_x + 1) * 2 - 1) / 2, low, column);
		printf_ball(a[*start_x][*start_y], (*end_y + 1) * 4 - 2, (*end_x + 1) * 2 - 1);
		Sleep(SPEED * 2);
		printf_ball(0, (*start_y + 1) * 4 - 2, (*start_x + 1) * 2 - 1);
		printf_ball(11, (*start_y + 1) * 4 - 2, ((*start_x + 1) * 2 - 1 + (*end_x + 1) * 2 - 1) / 2);
		printf_ball(0, (*end_y + 1) * 4 - 2, (*end_x + 1) * 2 - 1);
		Sleep(SPEED * 2);
	}

}
void printf_defeng(int num, int low, int column)
{
	setcolor(hout, BASE_WORD, BASE_COLOR);
	gotoxy(hout, 4 * column + 4, 0);
	for (int i = 0; i < 7; i++)
		if (i == 0)
			cout << "╔";
		else if (i == 6)
			cout << "╗";
		else
			cout << "═";
	gotoxy(hout, 4 * column + 4, 1);
	cout << "║得分：" << setw(4) << num << "║";
	gotoxy(hout, 4 * column + 4, 2);
	for (int i = 0; i < 7; i++)
		if (i == 0)
			cout << "╚";
		else if (i == 6)
			cout << "╝";
		else
			cout << "═";
	setcolor(hout,BASE_COLOR,COLOR_HWHITE);

}
void mode4(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	output("\n\n\n按回车键显示图形界面...");
	color_origin(p, a, row, column);
	cout << "本小题结束，";
	end(-1, -1);
}
void mode5(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	output("\n\n\n按回车键显示图形界面...");
	system("cls");
	setfontsize(hout, L"点阵字体", 30);
	setconsoleborder(hout, (int)(2 * *column + 3) * 2 + 1, (int)(2 * *row + 3) + 2);
	setcursor(hout, CURSOR_INVISIBLE);
	color_origin_with(p, a, row, column, record);
	cout << "本小题结束，";
	end(-1, -1);
}
void mode6(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	setfontsize(hout, L"点阵字体", 30);
	setconsoleborder(hout, (int)(2 * *column + 3) * 2 + 1, (int)(2 * *row + 3) + 2);
	setcursor(hout, CURSOR_INVISIBLE);
	if (all_judge(*row, *column, a, record))
		color_origin_with(p, a, row, column, record);
	else
	{
		color_origin_with(p, a, row, column, record);
		cout << "初始没有可以消除的项\n";
	}
	end(-1, -1);
}
void mode7(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int book[MAX_ROW][MAX_COLUMN] = { 0 };
	int moveable[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	setfontsize(hout, L"点阵字体", 30);
	setconsoleborder(hout, (int)(2 * *column + 3) * 3 + 1, (int)(2 * *row + 3) + 2);
	setcursor(hout, CURSOR_INVISIBLE);
	if (all_judge(*row, *column, a, record))
	{
		while (all_judge(*row, *column, a, record))
		{
			color_origin_with(p, a, row, column, record);
			gotoxy(hout, 0, 2 * *row);
			if (p == 7)
				output("\n按回车键进行数组下落除0操作..");
			else
				Sleep(SPEED*10);
			delete_ball(*row, *column, a, record);
			color_origin_with(p, a, row, column, book);
			down_ball_color(p, a, row, column);
			reset(record);
			gotoxy(hout, 0, 2 * *row);
			if (p == 7)
				output("\n按回车键进行新值填充...                ");
			else
				Sleep(SPEED);
			random_ball_origin(11, a, row, column);
		}
		gotoxy(hout, 0, 2 * *row);
		if (p == 7)
			output("\n没有可以消除的项 按回车继续\n");
	}
	else
	{
		color_origin_with(p, a, row, column, record);
		if (p == 7)
			output("初始没有可以消除的项\n按回车继续\n");
	}
	ball_moveable(p, a, row, column, record, moveable);
	if (p == 7)
	{
		cout << "本小题结束                           ";
		end(0, 2 * *row + 1 + 1);
	}
}
void mode8(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	mode7(p, a, row, column);
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int book[MAX_ROW][MAX_COLUMN] = { 0 };
	int moveable[MAX_ROW][MAX_COLUMN] = { 0 }, start_x, start_y, end_x, end_y, action = 0, loop = 1, num = 0;

	while (ball_moveable(p, a, row, column, record, moveable))
	{
		printf_defeng(num, *row, *column);
		if (read_loop(p, a, row, column, &start_y, &start_x, &action, &loop, moveable) == -1)
			break;
		printf_ball_signed(a[start_x][start_y], (start_y + 1) * 4 - 2, (start_x + 1) * 2 - 1);
		if (read_loop(p, a, row, column, &end_y, &end_x, &action, &loop, moveable) == -1)
			break;
		if (!((end_x == start_x - 1 && end_y == start_y) || (end_x == start_x + 1 && end_y == start_y) || (end_x == start_x && end_y == start_y + 1) || (end_x == start_x && end_y == start_y - 1)))
			continue;
		printf_ball_signed(a[end_x][end_y], (end_y + 1) * 4 - 2, (end_x + 1) * 2 - 1);
		exchange_ball(p, a, *row, *column, &start_x, &start_y, &end_x, &end_y);
		reset(record);
		while (all_judge(*row, *column, a, record))
		{
			num += cal_defeng(record);
			printf_defeng(num, *row, *column);
			color_origin_with(p, a, row, column, record);
			Sleep(SPEED);
			delete_ball(*row, *column, a, record);
			color_origin_with(p, a, row, column, book);
			down_ball_color(p, a, row, column);
			reset(record);
			Sleep(SPEED);
			random_ball_origin(11, a, row, column);
		}
		reset(moveable);
	}
}
