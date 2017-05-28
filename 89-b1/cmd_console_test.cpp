#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ָ��λ�ã���ָ����ɫ����ʾһ���ַ����ɴ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continued(HANDLE hout, int prompt)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, 0, 22);

	switch (prompt) {
	case 1:
		cout << "��ɫ��ʾ��ʾ���";
		break;
	case 2:
		cout << "������Ч���";
		break;
	case 3:
		cout << "������Ч���";
		break;
	case 4:
		cout << "����ַ���ʾ���";
		break;
	case 5:
		cout << "��ʾԭ���ڵĿ����߶����";
		break;
	case 6:
		cout << "�ı䴰�ڵĿ����߶����";
		break;
	}
	cout << "�����س�������...";

	while (_getch() != '\r')
		;

	system("cls"); //����ϵͳ���������Ļ
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ָ��λ�ã���ָ����ɫ����ʾһ���ַ����ɴ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��

	if (1) {
		int x, y;

		/* ��ʾ16*16����ɫ��ÿ���ַ�֮���һ���ո� */
		for (y = 0; y < 16; y++) {
			for (x = 0; x < 16; x++)
				showch(hout, x * 2, y, 'x', y, x, 2);	//��xyλ����ʾx����x�����ֵ��ǰ��ɫ��y�����ֵ������ɫ����ʾ����x��Ϊ��ʹ����Э�������Ի���һ��x��۲�Ч����
			cout << endl; //16��ǰ��ɫ�任��ɺ󣬻�һ��
			Sleep(100);  //��ʱ0.1�루�Ժ���Ϊ��λ��1000=1�룩
		}
		to_be_continued(hout, 1);
	}

	if (1) {
		const int MAX_X = 50;
		const int Y = 2;
		const int bg_color = COLOR_HYELLOW;	//����Ϊ����ɫ
		const int fg_color = COLOR_HBLUE;	//ǰ��Ϊ����ɫ
		const char ch = '*';        //�ַ�Ϊ*(ע�⣺����ǿո���ǰ��ɫ�޷���ʾ)
		const int LENGTH = 10;
		int x;

		/* ��һ���ַ����������ƶ� */
		for (x = 0; x < MAX_X; x++) {
			/* ������(x,2)λ�ô�������ӡ10���ַ� */
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);

			/* ��ʱ0.1�� */
			Sleep(100);

			if (x < MAX_X - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				showch(hout, x, Y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, 2);
	}

	if (1) {
		const int MAX_Y = 12;
		const int X = 2;
		const int bg_color = COLOR_HYELLOW;	//����Ϊ����ɫ
		const int fg_color = COLOR_HBLUE;	//ǰ��Ϊ����ɫ
		const char ch = '*';        //�ַ�Ϊ*(ע�⣺����ǿո���ǰ��ɫ�޷���ʾ)
		const int LENGTH = 10;
		int y;

		/* ��һ���ַ����������ƶ� */
		for (y = 2; y < MAX_Y; y++) {
			/* ������(x,2)λ�ô�������ӡ10���ַ� */
			showch(hout, X, y, ch, bg_color, fg_color, LENGTH);

			/* ��ʱ0.3�� */
			Sleep(300);

			if (y < MAX_Y - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				showch(hout, X, y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, 3);
	}

	if (1) {
		/* ����Ļ��[0,0]-[60,20]�����������ʾ100���ַ���ֵ�������ɫ���
		˵����δ�ж�λ���ظ������������ַ�������100
		δ�ж�ǰ��ɫ/����ɫ�ظ�������ĳЩλ��ֻ������ɫ���������ַ� */
		const int MAX_X = 60, MAX_Y = 20;
		int x, y, fg_color, bg_color, num;
		char ch;

		srand(unsigned int(time(0))); //��������

		for (num = 0; num < 100; num++) {
			x = rand() % (MAX_X + 1);
			y = rand() % (MAX_Y + 1);
			fg_color = rand() % 16;
			bg_color = rand() % 16;
			ch = 33 + rand() % 94;   //ASCII�����33-126Ϊ�ɼ�ͼ���ַ�

									 /* ��ʾһ��1 */
			showch(hout, x, y, ch, bg_color, fg_color, 1);

			/* ��ʱ0.05�� */
			Sleep(50);
		}

		to_be_continued(hout, 4);
	}

	if (1) {
		/* �ָ�Ϊ��ʼ��ɫ */
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);

		/* ���� */
		system("cls");

		cout << "ԭ���ڵĿ����߶�" << endl;
		cout << "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7";
		to_be_continued(hout, 5);

		/* ���� */
		system("cls");

		/* ��������ڸ�Ϊ 30�� 100�� */
		setconsoleborder(hout, 100, 30);
		cout << "�´��ڵĿ����߶�" << endl;
		cout << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7         8         9";

		to_be_continued(hout, 6);
	}

	return 0;
}
