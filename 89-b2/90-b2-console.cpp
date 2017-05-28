/*1650254 尤尧寅 计1*/
//cmd图形界面
#include"90-b2.h"
void color_origin(int p, int a[][MAX_COLUMN], int *low, int *column)
{
	setfontsize(hout, L"点阵字体", 30);
	setconsoleborder(hout, (int)(*column + 3) * 2 + 1 + 10, (int)(*low + 3) + 2);
	system("cls");
	setcursor(hout, CURSOR_INVISIBLE);
	gotoxy(hout, 0, 0);
	for (int i = -1; i <= *low; i++)
	{
		for (int j = -1; j <= *column; j++)
		{
			setcolor(hout, 15, 0);
			if (i == -1 && j == -1)
				cout << "╔";
			else if (i == *low &&j == -1)
				cout << "╚";
			else if (i == -1 && j == *column)
				cout << "╗";
			else if (i == *low &&j == *column)
				cout << "╝";
			else if (i == -1 || i == *low)
				cout << "═";
			else if (j == -1 || j == *column)
				cout << "║";
			else
			{
				if (a[i][j] != 0)
				{
					setcolor(hout, 15, a_color[a[i][j] - 1]);
					cout << "●";
					setcolor(hout, 15, 0);
				}
				else
				{
					setcolor(hout, 15, 15);
					cout << "  ";
					setcolor(hout, 15, 0);
				}
			}
		}
		cout << endl;
	}

}
void color_origin_with(int p, int a[][MAX_COLUMN], int *low, int *column)
{
	gotoxy(hout, 0, 0);
	for (int i = 0; i < 2 * *low + 1; i++)
	{
		for (int j = 0; j < 2 * *column + 1; j++)
		{
			setcolor(hout, 15, 0);
			if (i == 0 && j == 0)
				cout << "╔";
			else if (i == 2 * *low&& j == 0)
				cout << "╚";
			else if (i == 0 && j == 2 * *column)
				cout << "╗";
			else if (i == 2 * *low && j == 2 * *column)
				cout << "╝";
			else if (i == 0 && j % 2 == 0)
				cout << "╦";
			else if (i == 2 * *low && j % 2 == 0)
				cout << "╩";
			else if (i % 2 == 0 && j == 0)
				cout << "╠";
			else if (i % 2 == 0 && j == 2 * *column)
				cout << "╣";
			else if (i % 2 != 0 && j % 2 == 0)
				cout << "║";
			else if (i % 2 == 0 && j % 2 != 0)
				cout << "═";
			else if (i % 2 == 0 && j % 2 == 0 && i != 2 * *low && j != 2 * *column)
				cout << "╬";
			else
			{
				if ((i % 2 != 0 && j % 2 != 0 && j < 2 * * column && i < 2 * * low  && a[(i - 1) / 2][(j - 1) / 2] != 0))
				{
					setcolor(hout, 15, a_color[a[(i - 1) / 2][(j - 1) / 2] - 1]);
					cout << "●";
					setcolor(hout, 15, 0);
				}
				else
				{
					setcolor(hout, 15, 15);
					cout << "  ";
					setcolor(hout, 15, 0);
				}
			}
		}
		cout << endl;
	}

}
int auto_color(int p, int a[][MAX_COLUMN], int low, int column)
{
	int b[MAX_ADD], rout[2][MAX_SPACE], step[MAX_LOW][MAX_COLUMN] = { 0 }, start_x, start_y, end_x, end_y, X = 0, Y = 0, action, loop = 1;
	while (1)
	{
		for (int i = 0; i < MAX_ADD; i++)
			b[i] = rand() % MAX_BALL;
		if (check_60(p, a, low, column, 0.6))
		add_random_ball(MAX_ADD, low, column, a, b);
			break;
	}
	origin_ball(column, low);
	color_origin_with(p, a, &low, &column);
	while (1)
	{
		while (1)
		{
			read_x_y(p, a, low, column, &start_y, &start_x, &action, &loop);
			if (action == MOUSE_LEFT_BUTTON_CLICK&&start_x < low&&start_y < column&&a[start_x][start_y] != 0)
				break;
			else if (action == MOUSE_RIGHT_BUTTON_CLICK)
				return 0;
		}
		printf_after_move(a, start_x, start_y);
		while (1)
		{
			read_x_y(p, a, low, column, &end_y, &end_x, &action, &loop);
			if (action == MOUSE_LEFT_BUTTON_CLICK&&a[end_x][end_y] == 0 && (!(end_x == start_x&&end_y == start_y)))
				break;
			else if (action == MOUSE_RIGHT_BUTTON_CLICK)
				return 0;
		}
		if (!BFS(low, column, a, start_x, start_y, end_x, end_y, step, rout))
		{
			gotoxy(hout, 0, 2 * low + 1);
			cout << "无法移动至目标点                ";
			Sleep(1000);
			printf_ball(a[start_x][start_y], (start_y + 1) * 4 - 2, (start_x + 1) * 2 - 1);
		}
		else
		{
			CHange_array(rout, step, start_x, start_y, end_x, end_y);
			reform(step, rout);
			move(rout, a, low, column);
			a[end_x][end_y] = a[start_x][start_y];
			a[start_x][start_y] = 0;
			break;
		}
	}
	return 0;
}
void read_x_y(int p, int a[][MAX_COLUMN], int low, int column, int *X, int *Y, int *action, int *loop)
{
	enable_mouse(hin);
	if (p == 7 || p == 6)
		*action = read_mouse(hin, *X, *Y);
	if (p == 8)
		*action = read_mouse_and_key(hin, *X, *Y, 1);
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

} //end of while(1)
void move(int rout[][MAX_SPACE], int a[][MAX_COLUMN], int low, int column)
{
	int i = 0, j = 0, k = 0;
	while (rout[0][i + 1] != -1)
	{
		j = 0;
		k = 0;
		while (1)
		{
			cal((rout[1][i] + 1) * 4 - 2 + j, (rout[0][i] + 1) * 2 - 1 + k, low, column);
			j += (rout[1][i + 1] - rout[1][i]) * 2;
			k += rout[0][i + 1] - rout[0][i];
			printf_ball(a[rout[0][0]][rout[1][0]], (rout[1][i] + 1) * 4 - 2 + j, (rout[0][i] + 1) * 2 - 1 + k);
			if (j == -4 || j == 4 || k == 2 || k == -2)
				break;
			Sleep(100);
		}
		i++;
		Sleep(100);
	}
}
void printf_ball(int a, int x, int y)
{
	gotoxy(hout, x, y);
	setcolor(hout, 15, a_color[a - 1]);
	cout << "●";
	setcolor(hout, 15, 0);
}
int cal(int i, int j, int low, int column)
{
	gotoxy(hout, i, j);
	setcolor(hout, 15, 0);
	if (i % 4 == 0)
		cout << "║";
	else if (j % 2 == 0)
		cout << "═";
	else
	{
		setcolor(hout, 15, 15);
		cout << "  ";
		setcolor(hout, 15, 0);
	}
	return 0;
}
int random_next_three(int b[MAX_ADD])
{
	for (int i = 0; i < 3; i++)
		b[i] = rand() % 7;
	return 0;
}
int color_game(int p, int a[][MAX_COLUMN], int low, int column)
{
	int b[MAX_ADD], num, start_x, start_y, end_x, end_y, count_num = 0, flag = -10, k = 0, del_num = 0, X = 0, Y = 0, action = 0, loop = 1;
	random_next_three(b);
	origin_ball(column, low);
	while (1)
	{
		while (1)
		{
			color_origin_with(p, a, &low, &column);
			print_nextthree_color(b, low, column, action);
			printf_defeng(count_num, low, column);
			printf_detail(low, column, a, k, 0, action);
			while (1)
			{
				read_x_y(p, a, low, column, &start_y, &start_x, &action, &loop);
				if (action == MOUSE_LEFT_BUTTON_CLICK&&start_x < low&&start_y < column&&a[start_x][start_y] != 0)
					break;
				else if (action == MOUSE_RIGHT_BUTTON_CLICK)
					return 0;
				else if (action == -2)
					action_2(a, &count_num, b, low, column, k, action,p);
				else if (action == -1)
					print_nextthree_color(b, low, column, action);
				else if (action == -3)
					printf_detail(low, column, a, k, 0, action);
			}
			printf_after_move(a, start_x, start_y);
			while (1)
			{
				read_x_y(p, a, low, column, &end_y, &end_x, &action, &loop);
				if (action == MOUSE_LEFT_BUTTON_CLICK&&end_x < low&&end_y < column)
					break;
				else if (action == MOUSE_RIGHT_BUTTON_CLICK)
					return 0;
				else if (action == -2)
					action_2(a, &count_num, b, low, column, k, action,p);
				else if (action == -1)
					print_nextthree_color(b, low, column, action);
				else if (action == -3)
					printf_detail(low, column, a, k, 0, action);

			}
			int rout[2][MAX_SPACE], step[MAX_LOW][MAX_COLUMN] = { 0 };
			if (a[end_x][end_y] != 0 || (end_x == start_x&&end_y == start_y)||!BFS(low, column, a, start_x, start_y, end_x, end_y, step, rout) )
			{
				gotoxy(hout, 0, 2 * low + 1);
				cout << "无法移动至目标点!      " << endl;
				printf_ball(a[start_x][start_y], (start_y + 1) * 4 - 2, (start_x + 1) * 2 - 1);
			}
			else
			{
				CHange_array(rout, step, start_x, start_y, end_x, end_y);
				reform(step, rout);
				move(rout, a, low, column);
				k = a[start_x][start_y];
				a[end_x][end_y] = a[start_x][start_y];
				a[start_x][start_y] = 0;
				num = judge_delete_ball_aftermove(low, column, a, end_x, end_y);
				del_num = num;
				if (num != 0)
					count_num += (num - 1)*(num - 2);
				printf_defeng(count_num, low, column);
				printf_detail(low, column, a, k, del_num, action);
				color_origin_with(p, a, &low, &column);
				if (!num)
				{
					flag = check_win_lose(a, low, column);
					break;
				}
				print_nextthree_color(b, low, column, action);
				color_origin_with(p, a, &low, &column);
			}
		}
		if (flag == 0 || flag == -1)
			break;
		add_random_ball(3, low, column, a, b);
		flag = check_win_lose(a, low, column);
		if (flag == 0 || flag == -1)
			break;
		random_next_three(b);
	}
	color_origin_with(p, a, &low, &column);
	if (flag == 0)
		cout << "游戏成功！            " << endl;
	else if (flag == -1)
		cout << "格子已满，游戏结束         " << endl;
	printf_detail(low, column, a, k, 0, action);
	return 0;
}
void action_2(int a[][MAX_COLUMN],int *count_num,int b[MAX_ADD],int low,int column,int k,int action,int p)
{
	clear(a);
	*count_num = 0;
	random_ball_origin(-1, a, &low, &column);
	random_next_three(b);
	color_origin_with(p, a, &low, &column);
	print_nextthree_color(b, low, column, action);
	printf_defeng(*count_num, low, column);
	printf_detail(low, column, a, k, 0, action, 1);
}
void print_nextthree_color(int *b, int low, int column, int k)
{
	static int l = 1;
	if (k == -1)
		l *= k;
	if (l == 1)
	{
		setcolor(hout, 15, 0);
		gotoxy(hout, 4 * column + 4, 4);
		for (int i = 0; i < 5; i++)
			if (i == 0)
				cout << "╔";
			else if (i == 4)
				cout << "╗";
			else
				cout << "═";
		for (int i = 0; i < 3; i++)
		{
			gotoxy(hout, 4 * column + 4, 5);
			setcolor(hout, 15, 0);
			if (i == 0)
				cout << "║";
			printf_ball(*(b + i) + 1, 4 * column + 6 + 2 * i, 5);
			if (i == 2)
				cout << "║";
		}
		gotoxy(hout, 4 * column + 4, 6);
		for (int i = 0; i < 5; i++)
			if (i == 0)
				cout << "╚";
			else if (i == 4)
				cout << "╝";
			else
				cout << "═";
	}
	else
		for (int i = 0; i < 3; i++)
		{
			setcolor(hout, 0, 0);
			gotoxy(hout, 4 * column + 4, 4 + i);
			cout << "                       ";
		}

}
void printf_defeng(int num, int low, int column)
{
	setcolor(hout, 15, 0);
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

}
void printf_detail(int low, int column, int a[][MAX_COLUMN], int k, int num, int l,int clear_ball)
{
	int b[MAX_BALL+1] = { 0,0,0,0,0,0,0,0 };
	static int del[MAX_BALL + 1] = { 0,0,0,0,0,0,0,0 }, flag = 1;
	if (clear_ball == 1)
		for (int i = 0; i < (MAX_BALL + 1); i++)
			del[i] = 0;
	for (int i = 0; i < num; i++)
		del[k]++;
	del[0] = 0;
	for (int i = 0; i < low; i++)
		for (int j = 0; j < column; j++)
			b[a[i][j]]++;
	if (l == -3)
		flag *= -1;
	if (flag > 0)
	{
		setcolor(hout, 15, 0);
		gotoxy(hout, 4 * column + 4, 8);
		for (int i = 0; i < 14; i++)
			if (i == 0)
				cout << "╔";
			else if (i == 13)
				cout << "╗";
			else
				cout << "═";
		for (int i = 0; i < 8; i++)
		{
			setcolor(hout, 15, 0);
			gotoxy(hout, 4 * column + 4, 9 + i);
			cout << "║";
			if (i != 0)
				printf_ball(i, 4 * column + 6, 9 + i);
			else
				cout << "  ";
			cout << ":" << setw(2) << b[i] << "/" << setiosflags(ios::fixed) << setprecision(2) << setw(5) << (double)(b[i] * 100.0 / (low*column)) << "%" << "   del-" << setw(4) << del[i] << " ║";
		}
		gotoxy(hout, 4 * column + 4, 17);
		for (int i = 0; i < 14; i++)
			if (i == 0)
				cout << "╚";
			else if (i == 13)
				cout << "╝";
			else
				cout << "═";
	}
	else
		for (int i = 0; i < 10; i++)
		{
			setcolor(hout, 0, 0);
			gotoxy(hout, 4 * column + 4, 8 + i);
			cout << "                            ";
		}

}
void origin_ball(int column, int low)
{
	system("cls");
	setfontsize(hout, L"点阵字体", 30);
	setconsoleborder(hout, (int)(2 * column + 3) * 2 + 1 + 30, (int)(2 * low + 3) + 2);
	setcursor(hout, CURSOR_INVISIBLE);
}
void printf_after_move(int a[][MAX_COLUMN], int i, int j)
{
	gotoxy(hout, (j + 1) * 4 - 2, (i + 1) * 2 - 1);
	setcolor(hout, a_color[a[i][j] - 1], 15);
	cout << "◎";
	setcolor(hout, 15, 0);
}
void clear(int a[][MAX_COLUMN])
{
	setcolor(hout, 0, 7);
	for (int i = 0; i < MAX_LOW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			a[i][j] = 0;
}
