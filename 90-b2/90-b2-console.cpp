#include"90-b2.h"
/*1650254 ”»“¢“˙ º∆À„ª˙“ª∞‡*/
int move_1()
{
	int w = 'a';
	int t;
	while (w != '\r')
	{
		w = _getch();
		if (w == 224)
			t = _getch();
		if (w == 224 && t == 72)
			return 1;
		else if (w == 224 && t == 80)
			return -1;
		else
			;
	}
	return 0;
}
void output_document(FILE_NAME *file_name, FILE_NAME **target)
{
	int num = 0;
	FILE_NAME *q = file_name;
	while (1)
	{
		setcolor(hout, BASE_COLOR, BASE_WORD);
		gotoxy(hout, 7 * MAX_COLUMN, 0);
		int row_num = ROW_NUM;
		int column_num = COLUMN_NUM;
		for (int i = 0; i < row_num + 2; i++)
		{
			if (i == 0)
				cout << "®X";
			else if (i == row_num + 1)
				cout << "®[";
			else
				cout << "-";
		}
		FILE_NAME *temp_p = q;
		for (int i = 0; i < column_num; i++)
		{
			gotoxy(hout, 7 * MAX_COLUMN, i + 1);
			cout << "®U";
			if (q != NULL)
			{
				int temp = strlen(q->name);
				for (int j = 0; j < row_num; j++)
				{
					if (i == num)
					{
						setcolor(hout, BASE_WORD, BASE_COLOR);
					}
					if (j <temp)
						cout <<q->name[j];
					else
						cout << " ";
				}
				setcolor(hout, BASE_COLOR, BASE_WORD);
				q = q->next;
			}
			else
			{
				for (int j = 0; j < row_num; j++)
					cout << " ";
			}
			cout << "®U\n";
		}
		gotoxy(hout, 7 * MAX_COLUMN, column_num + 1);
		for (int i = 0; i < row_num + 2; i++)
		{
			if (i == 0)
				cout << "®^";
			else if (i == row_num + 1)
				cout << "®a";
			else
				cout << "-";
		}
		FILE_NAME *temp_q = q;
		q = temp_p;
		int step = move_1();
		if (step == 1)
		{
			if (num != 0)
				num--;
			if (num == 0 && q->last != NULL)
				q = q->last;
		}
		else if (step == -1)
		{
			if (num != column_num - 1)
				num++;
			if (num == column_num - 1 && q->next != NULL&&temp_q != NULL)
				q = q->next;
		}
		else if (step == 0)
		{
			for (int i = 0; i < num; i++)
				q = q->next;
			*target = q;
			break;
		}
		else
			;
	}
	setcolor(hout, BASE_COLOR, COLOR_HWHITE);

}
void print_element(int x, int y, int num)
{
	gotoxy(hout, x, y);
	cout << "®X--®[";
	gotoxy(hout, x, y + 1);
	cout << "®U " << num << "®U";
	gotoxy(hout, x, y + 2);
	cout << "®^--®a";
}
void print_color(int a[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN], int origin[][MAX_COLUMN], int x, int y, int bo)
{
	for (int i = 0; i < MAX_COLUMN; i++)
		cout << "     " << i + 1;
	cout << endl;
	for (int i = 0; i < MAX_ROW; i++)
	{
		cout << '\n' << (char)(65 + i);
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			int color1 = 0;
			int color2 = COLOR_HWHITE;
			
			if (a[i][j] == 0)
				color2 = COLOR_HRED;
			if (a[i][j] != 0 && origin[i][j] != 0)
				color2=COLOR_HBLUE;
			if (bo == -1)
			{
				if (color[i][j] != 0)
					color1 = COLOR_WHITE;
			}
			if (book[i][j] != 0)
				color2 = COLOR_YELLOW;
			if (i == x&&j == y)
				color2 = COLOR_HYELLOW;
			setcolor(hout, color1, color2);
			print_element(j * 6 + 2, i * 3 + 1, a[i][j]);
			setcolor(hout, 0, 7);
		}
		cout << endl;
	}
}
int shuru_color(int *x, int *y, int *num, int _x, int _y, int origin[][MAX_COLUMN], int a[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN])
{
	while (1)
	{
		int w;
		w = 'a';
		int t;
		while (w != '\r')
		{
			w = _getch();
			if (w == 224)
				t = _getch();
			if (w == 8)
				return - 1;
			if (w == 224 && t == 72)
			{
				if (*x != 0)
					(*x)--;
			}
			else if (w == 224 && t == 80)
			{
				if (*x != 8)
					(*x)++;
			}
			else if (w == 224 && t == 75)
			{
				if (*y != 0)
					(*y)--;
			}
			else if (w == 224 && t == 77)
			{
				if (*y != 8)
					(*y)++;
			}
			else
				;
			gotoxy(hout, 0, 0);
			print_color(a, book, color, origin, *x, *y, 0);

		}
		if (origin[*x][*y] != 0)
		{
			continue;
		}
		else
		{
			while (1)
			{
				char temp = _getch();
				if (temp >= '1'&&temp <= '9')
				{
					*num = temp - '0';
					break;
				}
				else
					continue;
			}
			break;
		}
	}
	return 0;
}
//int shuru_mouse(int *x, int *y, int *num, int _x, int _y, int book[][MAX_COLUMN])
//{

//}