/*1650254 尤尧寅 计1*/
//内部数组
#include"90-b2.h"
void print_routinue_black(int low, int column, int astep[][MAX_COLUMN], int x, int y)
{
	gotoxy(hout, x, y);
	setcolor(hout, 0, 7);
	cout << "查找结果数组(显示所有查找过的点)：" << endl;
	cout << "     ";
	for (int i = 0; i < column; i++)
		cout << i + 1 << "  ";
	cout << endl << "---";
	for (int i = 0; i < column; i++)
		cout << "---";
	cout << endl;
	for (int i = 0; i < low; i++)
	{
		cout << (char)(65 + i) << " " << "|  ";
		for (int j = 0; j < column; j++)
			if (astep[i][j] != 0)
				cout << "*  ";
			else
				cout << "0  ";
		cout << endl;
	}
}
void print_routinue_colour(int low, int column, int astep[][MAX_COLUMN], int x, int y, int a[][MAX_COLUMN])
{
	gotoxy(hout, x, y);
	cout << "小球移动路径（用不同色块标出）：" << endl;
	cout << "     ";
	for (int i = 0; i < column; i++)
		cout << i + 1 << "  ";
	cout << endl << "---";
	for (int i = 0; i < column; i++)
		cout << "---";
	cout << endl;
	for (int i = 0; i < low; i++)
	{
		cout << (char)(65 + i) << " " << "|  ";
		for (int j = 0; j < column; j++)
		{
			if (astep[i][j] != 0)
				setcolor(hout, 14, 8);
			cout << a[i][j];
			setcolor(hout, 0, 7);
			cout << "  ";
		}
		cout << endl;
	}
}
void cout_orgin(int p, int a[][MAX_COLUMN], int *low, int *column)
{
	random_ball_origin(p, a, low, column);
	cout << "初始数组为：" << endl;
	print_array(*low, *column, a);
}
void print_nextthree(int *b)
{
	cout << "下三个颜色为 ";
	for (int i = 0; i < 3; i++)
		cout << *(b + i) + 1 << " ";
	cout << endl;
}
int change_shuru(int *x, int*y)
{
	*x = _getch();
	cout << (char)(*x);
	if ((*x >= 'A'&&*x <= 'Z'))
		*x -= 'A';
	else if ((*x >= 'a'&&*x <= 'z'))
		*x -= 'a';
	*y = _getch();
	cout << (char)(*y);
	if ((*y >= '0'&&*y <= '9'))
		*y = *y - '0' - 1;
	return 1;
}
void shuru_start_end(int *start_x, int *start_y, int *end_x, int *end_y, int a[][MAX_COLUMN], int low, int column)
{
	while (1)
	{
		cout << "请以字母+数字形式[例：c2]输入要移动球的矩阵坐标：";
		change_shuru(start_x, start_y);
		if (*start_x >= 0 && *start_x < low&&*start_y >= 0 && *start_y < column&&a[*start_x][*start_y] != 0)
		{
			cout << endl << "起始小球为" << (char)(*start_x + 65) << "行" << (char)(*start_y + '0' + 1) << "列                      " << endl;
			break;
		}
		else
			cout << endl << "输入错误" << endl;
	}
	while (1)
	{
		cout << "请以字母+数字形式[例：c2]输入要目标点的矩阵坐标：";
		change_shuru(end_x, end_y);
		if (*end_x >= 0 && *end_x < low&&*end_y >= 0 && *end_y < column && !(*end_x == *start_x&&*end_y == *start_y) && a[*end_x][*end_y] == 0)
		{
			cout << endl << "目标点为" << (char)(*end_x + 65) << "行" << (char)(*end_y + '0' + 1) << "列                      " << endl;
			break;
		}
		else
			cout << endl << "输入错误" << endl;
	}
}
void auto_game(int p, int a[][MAX_COLUMN], int low, int column)
{
	int b[MAX_ADD], rout[2][MAX_SPACE], step[MAX_LOW][MAX_COLUMN], start_x, start_y, end_x, end_y;
	for (int i = 0; i < MAX_LOW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			step[i][j] = 0;
	while (1)
	{
		for (int i = 0; i < MAX_ADD; i++)
			b[i] = rand() % MAX_BALL;
		if (check_60(p, a, low, column, 0.6))
			break;
		add_random_ball(MAX_ADD, low, column, a, b);
	}
	gotoxy(hout, 0, 4);
	print_array(low, column, a);
	print_nextthree(b);
	shuru_start_end(&start_x, &start_y, &end_x, &end_y, a, low, column);
	if (!BFS(low, column, a, start_x, start_y, end_x, end_y, step, rout))
	{
		cout << "无法移动至目标点";
		end(0, low + 12);
	}
	else
	{
		print_routinue_black(low, column, step, 0, (low + 8) + 5);
		CHange_array(rout, step, start_x, start_y, end_x, end_y);
		reform(step, rout);
		print_routinue_colour(low, column, step, 0, (low + 8) + low + 8, a);
	}
	end(0, (low + 8) * 3);
}
void man_game(int p, int a[][MAX_COLUMN], int low, int column)
{
	int b[MAX_ADD], num, start_x, start_y, end_x, end_y, count_num = 0, flag = -10;
	for (int i = 0; i < 3; i++)
		b[i] = rand() % MAX_BALL;
	while (1)
	{
		print_nextthree(b);
		while (1)
		{
			shuru_start_end(&start_x, &start_y, &end_x, &end_y, a, low, column);
			int rout[2][MAX_SPACE], step[MAX_LOW][MAX_COLUMN];
			for (int i = 0; i < MAX_LOW; i++)
				for (int j = 0; j < MAX_COLUMN; j++)
					step[i][j] = 0;
			if (!BFS(low, column, a, start_x, start_y, end_x, end_y, step, rout))
				cout << endl<<"无法移动至目标点!" << endl;
			else
			{
				CHange_array(rout, step, start_x, start_y, end_x, end_y);
				reform(step, rout);
				a[end_x][end_y] = a[start_x][start_y];
				a[start_x][start_y] = 0;
				num = judge_delete_ball_aftermove(low, column, a, end_x, end_y);
				if (num != 0)
					count_num += (num - 1)*(num - 2);
				cout << endl << "本次得分 " << num << "总得分" << count_num<< endl<< "移动后的数组" << endl;
				print_array(low, column, a);//输出移动后的数组
				if (!num)
				{
					flag = check_win_lose(a, low, column);
					break;
				}
				cout << "本次数组为：" << endl;
				print_array(low, column, a);//下一次数组
				print_nextthree(b);
			}
		}
		if (flag == 0 || flag == -1)
			break;
		add_random_ball(MAX_ADD, low, column, a, b);
		flag = check_win_lose(a, low, column);
		if (flag == 0 || flag == -1)
			break;
		for (int i = 0; i < MAX_ADD; i++)
			b[i] = rand() % MAX_BALL;
		cout << "本次数组为：" << endl;
		print_array(low, column, a);//输出下一次的数组
	}
	cout << "本次数组为：" << endl;
	print_array(low, column, a);//输出下一次的数组
	if (flag == 0)
		cout << "游戏成功！" << endl;
	else if (flag == -1)
		cout << "格子已满，游戏结束" << endl;
}
//打印数组
void print_array(int i_end, int j_end, int a[][MAX_COLUMN])
{
	cout << "     ";
	for (int i = 0; i < j_end; i++)
		cout << i + 1 << "  ";
	cout << endl << "---";
	for (int i = 0; i < j_end; i++)
		cout << "---";
	cout << endl;
	for (int i = 0; i < i_end; i++)
	{
		cout << (char)(65 + i) << " " << "|  ";
		for (int j = 0; j < j_end; j++)
		{
			if (a[i][j] != 0)
				setcolor(hout, a_color[a[i][j] - 1], 7);
			cout << a[i][j];
			setcolor(hout, 0, 7);
			cout << "  ";
		}
		cout << endl;
	}
}
