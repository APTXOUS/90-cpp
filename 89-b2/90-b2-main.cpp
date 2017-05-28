/*1650254 尤尧寅 计1*/
#include"90-b2.h"

//菜单提示
void tishi()
{
	setfontsize(hout, L"点阵字体", 16);
	setconsoleborder(hout, 80, 25);
	gotoxy(hout, 0, 0);
	cout << "----------------------------------" << endl;
	cout << "1.内部数组，随机生成初始5个球" << endl;
	cout << "2.内部数组，随机生成60%的球，寻找移动路径" << endl;
	cout << "3.内部数组，完整版" << endl;
	cout << "4.画出n*n的框架（无分隔线），随机显示5个球" << endl;
	cout << "5.画出n*n的框架（有分隔线），随机显示5个球" << endl;
	cout << "6.n*n的框架，60%的球，完成一次移动" << endl;
	cout << "7.cmd图形界面完整版" << endl;
	cout << "8.cmd图形界面完整版-支持同时读键（额外加分）" << endl;
	//cout << "9.双击事件屏蔽单击事件" << endl;
	cout << "0.退出" << endl;
	cout << "----------------------------------" << endl;
	cout << "请输入(0-8)                                 " << endl;
	gotoxy(hout, 11, 11);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);


}
//输入菜单项
bool cin_switch(int *p)
{
	*p = _getch() - '0';
	cout << *p;
	if (*p >= 0 && *p <= 8)
		return 1;
	else
		return 0;
}
bool change_mode(int p, int(*a)[MAX_COLUMN], int *low, int *column)
{
	switch (p)
	{
	case 0:
		return 1;
	case 1:
		cout_orgin(p, a, low, column);
		end(0, *low + 10);
		break;
	case 2:
		cout_orgin(p, a, low, column);
		auto_game(p, a, *low, *column);
		break;
	case 3:
		cout_orgin(p, a, low, column);
		man_game(p, a, *low, *column);;
		end(-1, -1);
		break;
	case 4:
		cout_orgin(p, a, low, column);
		cout << "按回车键显示图形界面...";
		while (_getch() != '\r')
			;
		color_origin(p, a, low, column);
		end(0, *low + 2);
		break;
	case 5:
		cout_orgin(p, a, low, column);
		cout << "按回车键显示图形界面...";
		while (_getch() != '\r')
			;
		system("cls");
		setfontsize(hout, L"点阵字体", 30);
		setconsoleborder(hout, (int)(2 * *column + 3) * 2 + 1, (int)(2 * *low + 3) + 2);
		setcursor(hout, CURSOR_INVISIBLE);
		color_origin_with(p, a, low, column);
		end(0, 2 * *low + 3);
		break;
	case 6:
		random_ball_origin(p, a, low, column);
		auto_color(p, a, *low, *column);
		end(0, 2 * *low + 3);
		break;
	case 7:
		random_ball_origin(p, a, low, column);
		color_game(p, a, *low, *column);
		end(0, 2 * *low + 3);
		break;
	case 8:
		random_ball_origin(p, a, low, column);
		color_game(p, a, *low, *column);
		end(0, 2 * *low + 3);
		break;
	case 9:
		random_ball_origin(p, a, low, column);
		color_game(p, a, *low, *column);
		end(0, 2 * *low + 3);
		break;
	}
	return 0;
}
int main()
{
	srand((unsigned int)time(0));
	while (1)
	{
		system("cls");
		int xuan_xiang;
		while (1)
		{
			tishi();
			if (cin_switch(&xuan_xiang) == 1)
				break;
		}
		int a[MAX_LOW][MAX_COLUMN] = { 0 };
		int low;
		int column;
		if (change_mode(xuan_xiang, a, &low, &column) == 1)
			break;
	}
	return 0;
}