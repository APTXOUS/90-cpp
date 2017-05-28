/*1650254 ��Ң�� ��1*/
//�ڲ�����
#include"90-b2.h"
void print_routinue_black(int low, int column, int astep[][MAX_COLUMN], int x, int y)
{
	gotoxy(hout, x, y);
	setcolor(hout, 0, 7);
	cout << "���ҽ������(��ʾ���в��ҹ��ĵ�)��" << endl;
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
	cout << "С���ƶ�·�����ò�ͬɫ��������" << endl;
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
	cout << "��ʼ����Ϊ��" << endl;
	print_array(*low, *column, a);
}
void print_nextthree(int *b)
{
	cout << "��������ɫΪ ";
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
		cout << "������ĸ+������ʽ[����c2]����Ҫ�ƶ���ľ������꣺";
		change_shuru(start_x, start_y);
		if (*start_x >= 0 && *start_x < low&&*start_y >= 0 && *start_y < column&&a[*start_x][*start_y] != 0)
		{
			cout << endl << "��ʼС��Ϊ" << (char)(*start_x + 65) << "��" << (char)(*start_y + '0' + 1) << "��                      " << endl;
			break;
		}
		else
			cout << endl << "�������" << endl;
	}
	while (1)
	{
		cout << "������ĸ+������ʽ[����c2]����ҪĿ���ľ������꣺";
		change_shuru(end_x, end_y);
		if (*end_x >= 0 && *end_x < low&&*end_y >= 0 && *end_y < column && !(*end_x == *start_x&&*end_y == *start_y) && a[*end_x][*end_y] == 0)
		{
			cout << endl << "Ŀ���Ϊ" << (char)(*end_x + 65) << "��" << (char)(*end_y + '0' + 1) << "��                      " << endl;
			break;
		}
		else
			cout << endl << "�������" << endl;
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
		cout << "�޷��ƶ���Ŀ���";
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
				cout << endl<<"�޷��ƶ���Ŀ���!" << endl;
			else
			{
				CHange_array(rout, step, start_x, start_y, end_x, end_y);
				reform(step, rout);
				a[end_x][end_y] = a[start_x][start_y];
				a[start_x][start_y] = 0;
				num = judge_delete_ball_aftermove(low, column, a, end_x, end_y);
				if (num != 0)
					count_num += (num - 1)*(num - 2);
				cout << endl << "���ε÷� " << num << "�ܵ÷�" << count_num<< endl<< "�ƶ��������" << endl;
				print_array(low, column, a);//����ƶ��������
				if (!num)
				{
					flag = check_win_lose(a, low, column);
					break;
				}
				cout << "��������Ϊ��" << endl;
				print_array(low, column, a);//��һ������
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
		cout << "��������Ϊ��" << endl;
		print_array(low, column, a);//�����һ�ε�����
	}
	cout << "��������Ϊ��" << endl;
	print_array(low, column, a);//�����һ�ε�����
	if (flag == 0)
		cout << "��Ϸ�ɹ���" << endl;
	else if (flag == -1)
		cout << "������������Ϸ����" << endl;
}
//��ӡ����
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
