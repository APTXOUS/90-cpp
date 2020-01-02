#include"90-b2.h"
/*1650254 尤尧寅 计算机一班*/
void tishi()
{
	setcolor(hout, BASE_COLOR, BASE_WORD);
	setfontsize(hout, L"点阵字体", 16);
	setconsoleborder(hout, 80, 25);
	gotoxy(hout, 0, 0);
	cout << "----------------------------------------------------" << endl;
	cout << " 1.数独游戏-内部数组（手动输入文件名）" << endl;
	cout << " 2.数独游戏-图形界面（无加分项）" << endl;
	cout << " 3.数独游戏-自动求解" << endl;
	cout << " 4.数独游戏-图形界面（加分项1）" << endl;
	cout << " 5.数独游戏-图形界面（加分项2）(暂无）" << endl;
	cout << " 0.退出" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "请输入(0-5)                                 " << endl;
	gotoxy(hout, 0, 9);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
}
bool cin_switch(int *p)
{
	*p = _getch() - '0';
	cout << *p;
	if (*p >= 0 && *p <= 5)
		return 1;
	else
		return 0;
}
int mode2(const int p)
{
	if (p != 1)
	{
		system("cls");
		setfontsize(hout, L"点阵字体", 20);
		setconsoleborder(hout, (int)(2 * MAX_COLUMN + 3) * 4 + 1, (int)(4 * MAX_ROW + 3) + 2);
		setcursor(hout, CURSOR_INVISIBLE);
	}
	int arr[MAX_ROW][MAX_COLUMN];
	int book[MAX_ROW][MAX_COLUMN];
	int color[MAX_ROW][MAX_COLUMN];
	int origin[MAX_ROW][MAX_COLUMN];
	reset(book);
	reset(color);
	reset(origin);
	FILE_NAME *head=NULL, *target=NULL;
	if (p != 1)
	{
		if (input_document("sudoku", &head) == -1)
		{
			cout << "没有文件！" << endl;
			end(-1, -1);
			return 0;
		}
		else
		{
			output_document(head, &target);
			open_document(target->name, arr);
		}
	}
	else
		infile_document(arr);
	copy_arr(arr, origin);
	if (p != 1)
		gotoxy(hout, 0, 0);
	if (print_judege_array(p, MAX_ROW, MAX_COLUMN, arr, book, color, origin, -1, -1) != 0)
	{
		end(-1, -1);
		return 0;
	}
	STEP *head_ = NULL, *l = NULL, *q = NULL;
	int count = 0;
	int x = 0, y = 0, num;
	while (1)
	{
		if (p != 1)
		{
			Sleep(1000);
			gotoxy(hout, 0, 3 * MAX_COLUMN + 1);
			cout << "                              " << endl;
		}
		int _x = 0, _y = 3 * MAX_COLUMN + 2;
		if (p == 1)
		{
			_x = -1;
			_y = -1;
		}
		int flag_shuru = 0;
		if (p == 2)
			flag_shuru = shuru(&x, &y, &num, _x, _y, origin);
		else if (p == 4)
			flag_shuru = shuru_color(&x, &y, &num, 0, 3 * MAX_COLUMN + 2, origin, arr, book, color);
		if (flag_shuru == -1)
		{
			cout << endl;
			if (l != NULL)
				arr[l->x][l->y] = l->old;
			delete_list(&count, x, y, num, &head_, &l, &q);
		}
		else
		{
			cout << endl;
			add_list(&count, x, y, num, &head_, &l, &q);
			l->old = arr[x][y];
			arr[x][y] = num;
		}
		if (p != 1)
			gotoxy(hout, 0, 0);
		int flag = print_judege_array(p, MAX_ROW, MAX_COLUMN, arr, book, color, origin, x, y);
		if (judge_zero(arr) == 0 && flag == 0)
		{
			cout << "游戏成功!" << endl;
			break;
		}
	}
	if (p != 1)
		linklist_destroy_step(head_);
	linklist_destroy_name(head);
	end(0, 3 * MAX_COLUMN + 3);
	return OK;
}
int mode3(const int p)
{
	system("cls");
	setfontsize(hout, L"点阵字体", 20);
	setconsoleborder(hout, (int)(2 * MAX_COLUMN + 3) * 4 + 1, (int)(4 * MAX_ROW + 3) + 2);
	setcursor(hout, CURSOR_INVISIBLE);
	int arr[MAX_ROW][MAX_COLUMN];
	int book[MAX_ROW][MAX_COLUMN];
	int color[MAX_ROW][MAX_COLUMN];
	int origin[MAX_ROW][MAX_COLUMN];
	reset(book);
	reset(color);
	reset(origin);
	FILE_NAME *head, *target;
	if (input_document("sudoku", &head) == -1)
	{
		cout << "没有文件！" << endl;
		end(-1, -1);
		return 0;
	}
	else
	{
		output_document(head, &target);
		open_document(target->name, arr);
	}
	copy_arr(arr, origin);
	gotoxy(hout, 0, 0);
	if (print_judege_array(p, MAX_ROW, MAX_COLUMN, arr, book, color, origin, -1, -1) != 0)
	{
		end(-1, -1);
		return 0;
	}
	reset(book);
	dfs(arr, 0, origin, book, 1);
	if (judge_error_1(arr))
	{
		gotoxy(hout, 0, 3 * MAX_COLUMN + 3);
		cout << "无解";
	}
	linklist_destroy_name(head);
	end(0, 3 * MAX_COLUMN + 5);
	return OK;
}
bool change_mode(const int p)
{
	switch (p)
	{
	case 0:
		return 1;
	case 1:
		mode2(p);
		break;
	case 2:
		mode2(p);
		break;
	case 3:
		mode3(p);
		break;
	case 4:
		mode2(p);
		break;
	case 5:
		//mode5(p);
		break;
	}
	return 0;
}
int main()
{
	setlocale(LC_ALL, "Chinese-simplified");
	while (1)
	{
		int p;
		tishi();
		cin_switch(&p);
		if (change_mode(p) == 1)
			break;
	}
	return 0;
}