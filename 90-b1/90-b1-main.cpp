/*1650254 ��Ң�� �����1��*/
#include"90-b1.h"
void tishi()
{
	setcolor(hout, BASE_COLOR, BASE_WORD);
	setfontsize(hout, L"������", 16);
	setconsoleborder(hout, 80, 25);
	gotoxy(hout, 0, 0);
	cout << "----------------------------------------------------" << endl;
	cout << " 1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������" << endl;
	cout << " 2.�ڲ����飬������ʼ����������0�����䲢��0���" << endl;
	cout << " 3.�ڲ����飬������ʼ������������������ʾ" << endl;
	cout << " 4.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬" << endl;
	cout << " 5.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬" << endl;
	cout << " 6.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬����ʼ��������" << endl;
	cout << " 7.n*n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ" << endl;
	cout << " 8.cmdͼ�ν���������" << endl;
	cout << " 9.���ļ��ж�ȡ��������֤����������ʾ���㷨����ȷ��" << endl;
	cout << " 0.�˳�" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "������(0-9)                                 " << endl;
	gotoxy(hout, 11, 12);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
}
//����˵���
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
