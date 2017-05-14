/*1650254 尤尧寅 计算机1班*/
#include"90-b1.h"
void tishi()
{
	setcolor(hout, BASE_COLOR, BASE_WORD);
	setfontsize(hout, L"新宋体", 16);
	setconsoleborder(hout, 80, 25);
	gotoxy(hout, 0, 0);
	cout << "----------------------------------------------------" << endl;
	cout << " 1.内部数组，生成初始状态，寻找是否有初始可消除项" << endl;
	cout << " 2.内部数组，消除初始可消除项后非0项下落并用0填充" << endl;
	cout << " 3.内部数组，消除初始可消除项后查找消除提示" << endl;
	cout << " 4.n*n的框架(无分隔线)，显示初始状态" << endl;
	cout << " 5.n*n的框架(有分隔线)，显示初始状态" << endl;
	cout << " 6.n*n的框架(有分隔线)，显示初始状态及初始可消除项" << endl;
	cout << " 7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示" << endl;
	cout << " 8.cmd图形界面完整版" << endl;
	cout << " 9.从文件中读取数据以验证查找消除提示的算法的正确性" << endl;
	cout << " 0.退出" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "请输入(0-9)                                 " << endl;
	gotoxy(hout, 11, 12);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
}
//输入菜单项
bool cin_switch(int *p)
{
	*p = _getch() - '0';
	cout << *p;
	if (*p >= 0 && *p <= 9)
		return 1;
	else
		return 0;
}
bool change_mode(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	switch (p)
	{
	case 0:
		return 1;
	case 1:
		mode1(p, a, row, column);
		break;
	case 2:
		mode2(p, a, row, column);
		end(-1, -1);
		break;
	case 3:
		mode3(p, a, row, column);
		break;
	case 4:
		mode4(p, a, row, column);
		break;
	case 5:
		mode5(p, a, row, column);
		break;
	case 6:
		mode6(p, a, row, column);
		break;
	case 7:
		mode7(p, a, row, column);
		break;
	case 8:
		mode8(p, a, row, column);
		break;
	case 9:
		mode9(p, a, row, column);
		break;
	}
	return 0;
}
int main()
{
	setlocale(LC_ALL, "Chinese-simplified");
	srand((unsigned int)time(0));
	while (1)
	{
		system("cls");
		int xuan_xiang, row, column;
		while (1)
		{
			tishi();
			if (cin_switch(&xuan_xiang) == 1)
				break;
		}
		int a[MAX_ROW][MAX_COLUMN] = { 0 };
		if (change_mode(xuan_xiang, a, &row, &column) == 1)
			break;
	}
	return 0;
}
