/*1650254 ��Ң�� ��1*/
#include"90-b2.h"

//�˵���ʾ
void tishi()
{
	setfontsize(hout, L"��������", 16);
	setconsoleborder(hout, 80, 25);
	gotoxy(hout, 0, 0);
	cout << "----------------------------------" << endl;
	cout << "1.�ڲ����飬������ɳ�ʼ5����" << endl;
	cout << "2.�ڲ����飬�������60%����Ѱ���ƶ�·��" << endl;
	cout << "3.�ڲ����飬������" << endl;
	cout << "4.����n*n�Ŀ�ܣ��޷ָ��ߣ��������ʾ5����" << endl;
	cout << "5.����n*n�Ŀ�ܣ��зָ��ߣ��������ʾ5����" << endl;
	cout << "6.n*n�Ŀ�ܣ�60%�������һ���ƶ�" << endl;
	cout << "7.cmdͼ�ν���������" << endl;
	cout << "8.cmdͼ�ν���������-֧��ͬʱ����������ӷ֣�" << endl;
	//cout << "9.˫���¼����ε����¼�" << endl;
	cout << "0.�˳�" << endl;
	cout << "----------------------------------" << endl;
	cout << "������(0-8)                                 " << endl;
	gotoxy(hout, 11, 11);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);


}
//����˵���
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
		cout << "���س�����ʾͼ�ν���...";
		while (_getch() != '\r')
			;
		color_origin(p, a, low, column);
		end(0, *low + 2);
		break;
	case 5:
		cout_orgin(p, a, low, column);
		cout << "���س�����ʾͼ�ν���...";
		while (_getch() != '\r')
			;
		system("cls");
		setfontsize(hout, L"��������", 30);
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