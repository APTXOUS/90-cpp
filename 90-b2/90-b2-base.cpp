#include"90-b2.h"
/*1650254 尤尧寅 计算机一班*/
void print_array(int i_end, int j_end, int a[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN], int origin[][MAX_COLUMN], int x, int y)
{
	cout << "\n     ";
	for (int i = 0; i < j_end; i++)
		cout << i + 1 << " ";
	cout << endl << "---";
	for (int i = 0; i < j_end; i++)
		cout << "--";
	cout << endl;
	for (int i = 0; i < i_end; i++)
	{
		cout << (char)(65 + i) << " " << "|  ";
		for (int j = 0; j < j_end; j++)
		{
			setcolor(hout, 0, 7);
			if (i == x&&j == y)
				setcolor(hout, 0, COLOR_HYELLOW);
			if (a[i][j] == 0)
				setcolor(hout, 0, COLOR_HRED);
			if (a[i][j] != 0 && origin[i][j] != 0)
				setcolor(hout, 0, COLOR_HBLUE);
			if (color[i][j] != 0)
				if (a[i][j] == 0)
					setcolor(hout, COLOR_WHITE, 0);
				else if (book[i][j] == 0)
					if (origin[i][j] != 0)
						setcolor(hout, COLOR_WHITE, COLOR_BLUE);
					else
						setcolor(hout, 0, 7);
				else
					if (i == x&&j == y)
						setcolor(hout, COLOR_WHITE, COLOR_YELLOW);
					else
						setcolor(hout, COLOR_WHITE, COLOR_HYELLOW);
			cout << a[i][j];
			setcolor(hout, 0, 7);
			cout << " ";
		}
		cout << endl;
	}
}
int shuru(int *x, int *y, int *num, int _x, int _y, int book[][MAX_COLUMN])
{
	while (1)
	{
		if (_x != -1 && _y != -1)
		{
			Sleep(1000);
			gotoxy(hout, _x, _y);
		}
		cout << "请按行/列/值的方式输入(例如:c56=第c行第5列为6)，输入bk表示回退一次：";
		if (_x != -1 && _y != -1)
		{

			cout << "       \n                                                                    ";
			cout << "\n                                                                    ";
			cout << "\n                                                                    ";
			gotoxy(hout, _x, _y);
			cout << "请按行/列/值的方式输入(例如:c56=第c行第5列为6)，输入bk表示回退一次：";
		}
		char temp[3];
		temp[0] = _getch();
		cout << temp[0];
		temp[1] = _getch();
		cout << temp[1];
		if ((temp[0] == 'b' || temp[0] == 'B') && (temp[1] == 'k' || temp[1] == 'K'))
			return -1;
		temp[2] = _getch();
		cout << temp[2];
		if (temp[0] >= 'a'&&temp[0] <= 'i')
			*x = temp[0] - 'a';
		else if (temp[0] >= 'A'&&temp[0] <= 'I')
			*x = temp[0] - 'A';
		else
		{
			cout << "\n输入错误，请重新输入！\n\n";
			continue;
		}
		if (temp[1] >= '1'&&temp[1] <= '9')
			*y = temp[1] - '1';
		else
		{
			cout << "\n输入错误，请重新输入！\n\n";
			continue;
		}
		if (temp[2] >= '1'&&temp[2] <= '9')
		{
			*num = temp[2] - '0';
		}
		else
		{
			cout << "\n输入错误，请重新输入！\n\n";
			continue;
		}

		if (book[*x][*y] != 0)
		{
			cout << "\n此处为默认项，不能更改\n\n";
			continue;
		}
		else
			break;
	}
	return 0;
}
