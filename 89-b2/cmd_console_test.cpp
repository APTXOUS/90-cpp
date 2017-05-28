#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ��ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continued(const HANDLE hout, const char *prompt, const int X=0, const int Y=22)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, X, Y);

	if (prompt) 
		cout << prompt << "�����س�������...";
	else
		cout << "���س�������...";

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
	const HANDLE hin  = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��
		
	if (1) {
		int x, y;

		/* ��ʾ16*16����ɫ��ÿ���ַ�֮���һ���ո� */
		for (y = 0; y<16; y++) {
			for (x = 0; x<16; x++)
				showch(hout, x * 2, y, 'x', y, x, 2);	//��xyλ����ʾx����x�����ֵ��ǰ��ɫ��y�����ֵ������ɫ����ʾ����x��Ϊ��ʹ����Э�������Ի���һ��x��۲�Ч����
			cout << endl; //16��ǰ��ɫ�任��ɺ󣬻�һ��
			Sleep(100);  //��ʱ0.1�루�Ժ���Ϊ��λ��1000=1�룩
			}

		to_be_continued(hout, "��ɫ��ʾ��ʾ���");
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
		for (x = 0; x<MAX_X; x++) {
			/* ������(x,2)λ�ô�������ӡ10���ַ� */
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);

			/* ��ʱ0.1�� */
			Sleep(100);

			if (x<MAX_X - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				showch(hout, x, Y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, "������Ч���");
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
		for (y = 2; y<MAX_Y; y++) {
			/* ������(x,2)λ�ô�������ӡ10���ַ� */
			showch(hout, X, y, ch, bg_color, fg_color, LENGTH);

			/* ��ʱ0.3�� */
			Sleep(300);

			if (y<MAX_Y - 1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				showch(hout, X, y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, "������Ч���");
	}

	if (1) {
		/* ����Ļ��[0,0]-[60,20]�����������ʾ100���ַ���ֵ�������ɫ���
		˵����δ�ж�λ���ظ������������ַ�������100
		δ�ж�ǰ��ɫ/����ɫ�ظ�������ĳЩλ��ֻ������ɫ���������ַ� */
		const int MAX_X = 60, MAX_Y = 20;
		int x, y, fg_color, bg_color, num;
		char ch;

		srand(unsigned int(time(0))); //��������

		for (num = 0; num<100; num++) {
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

		to_be_continued(hout, "����ַ���ʾ���");
	}

	if (1) {
		int cols, lines, buffer_cols, buffer_lines;

		/* �ָ�Ϊ��ʼ��ɫ */
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);

		/* ���� */
		system("cls");

		cout << "ԭ���ڵĿ����߶�" << endl;
		cout << "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7";

		cout << endl;

		getconsoleborder(hout, cols, lines, buffer_cols, buffer_lines);
		cout << "��ǰ���ڵĿ�ȣ�" << cols << " �߶ȣ�" << lines << " ��������ȣ�" << buffer_cols << " �������߶ȣ�" << buffer_lines << endl;

		to_be_continued(hout, "��ʾԭ���ڵĿ����߶����");

		/* ���� */
		system("cls");

		/* ��������ڸ�Ϊ 30�� 100�У�������200�� */
		setconsoleborder(hout, 100, 30, 200);
		cout << "�´��ڵĿ����߶�" << endl;
		cout << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7         8         9";
		cout << endl;

		getconsoleborder(hout, cols, lines, buffer_cols, buffer_lines);
		cout << "��ǰ���ڵĿ�ȣ�" << cols << " �߶ȣ�" << lines << " ��������ȣ�" << buffer_cols << " �������߶ȣ�" << buffer_lines << endl;

		to_be_continued(hout, "�ı䴰�ڵĿ����߶����");
	}

	if (1) {
		setcursor(hout, CURSOR_VISIBLE_FULL);
		cout << "�����ʾΪȫ��ɫ�飬���������";
		getchar(); //��ͣΪ�˿����

		cout << endl << endl;
		setcursor(hout, CURSOR_VISIBLE_HALF);
		cout << "�����ʾΪ���ɫ�飬���������";
		getchar(); //��ͣΪ�˿����

		cout << endl << endl;
		setcursor(hout, CURSOR_INVISIBLE);
		cout << "�رչ����ʾ�����������";
		getchar(); //��ͣΪ�˿����

		cout << endl << endl;
		setcursor(hout, CURSOR_VISIBLE_NORMAL);
		cout << "�����ʾΪ���������������";
		getchar(); //��ͣΪ�˿����

		to_be_continued(hout, "�����״��ʾ���");
		}

	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;

		enable_mouse(hin);

		/* ��ӡ��ʼ���λ��[0,0] */
		setcursor(hout, CURSOR_INVISIBLE);	//�رչ��
		cout << "�ɲ����ƶ�,�����/˫��,�Ҽ���/˫��,���Ҽ�ͬʱ�������֣������Ҽ�˫������������" << endl;
		cout << "[��ǰ���λ��] X:0  Y:0"; //��ӡ��ʼ���λ��

		while (loop) {
			/* ����꣬����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			action = read_mouse(hin, X, Y);

			/* ת����1�н��д�ӡ */
			gotoxy(hout, 0, 1);
			cout << "[��ǰ���λ��] X:" << setw(2) << X << " Y:" << setw(2) << Y << " ����:";

			switch (action) {
				case MOUSE_LEFT_BUTTON_CLICK:			//�������
					cout << "�������      " << endl;
					showch(hout, X, Y, '1');			//�����ָ��λ����ʾ1
					break;
				case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:	//˫�����
					cout << "˫�����      " << endl;
					showch(hout, X, Y, '2');			//�����ָ��λ����ʾ2
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:			//�����Ҽ�
					cout << "�����Ҽ�      " << endl;
					showch(hout, X, Y, '3');			//�����ָ��λ����ʾ3
					break;
				case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//˫���Ҽ�
					cout << "˫���Ҽ�      " << endl;
					showch(hout, X, Y, '4');			//�����ָ��λ����ʾ4
					loop = 0;
					break;
				case MOUSE_LEFTRIGHT_BUTTON_CLICK:		//ͬʱ�������Ҽ�
					cout << "ͬʱ�������Ҽ�" << endl;
					showch(hout, X, Y, '5');			//�����ָ��λ����ʾ5
					break;
				case MOUSE_ONLY_MOVED:
					cout << "�ƶ�          " << endl;
					//showch(hout, X, Y, '*');����ӡ�κ�����
					break;
				case MOUSE_NO_ACTION:
				default:
					cout << "��������" << endl;
					showch(hout, X, Y, '0');			//�����ָ��λ����ʾ0
					break;
				} //end of switch
			} //end of while(1)

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//�򿪹��
		to_be_continued(hout, "��������ʾ1����ȡ����ƶ��¼������");
		}

	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;

		enable_mouse(hin);

		/* ��ӡ��ʼ���λ��[0,0] */
		setcursor(hout, CURSOR_INVISIBLE);	//�رչ��
		cout << "�ɲ��������/˫��,�Ҽ���/˫��,���Ҽ�ͬʱ�������֣������Ҽ�˫������������" << endl;
		cout << "[��ǰ���λ��] X:0  Y:0"; //��ӡ��ʼ���λ��

		while (loop) {
			/* ����꣬����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
			action = read_mouse(hin, X, Y, 0);

			/* ת����1�н��д�ӡ */
			gotoxy(hout, 0, 1);
			cout << "[��ǰ���λ��] X:" << setw(2) << X << " Y:" << setw(2) << Y << " ����:";

			switch (action) {
				case MOUSE_LEFT_BUTTON_CLICK:			//�������
					cout << "�������      " << endl;
					showch(hout, X, Y, '1');			//�����ָ��λ����ʾ1
					break;
				case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:	//˫�����
					cout << "˫�����      " << endl;
					showch(hout, X, Y, '2');			//�����ָ��λ����ʾ2
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:			//�����Ҽ�
					cout << "�����Ҽ�      " << endl;
					showch(hout, X, Y, '3');			//�����ָ��λ����ʾ3
					break;
				case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//˫���Ҽ�
					cout << "˫���Ҽ�      " << endl;
					showch(hout, X, Y, '4');			//�����ָ��λ����ʾ4
					loop = 0;
					break;
				case MOUSE_LEFTRIGHT_BUTTON_CLICK:		//ͬʱ�������Ҽ�
					cout << "ͬʱ�������Ҽ�" << endl;
					showch(hout, X, Y, '5');			//�����ָ��λ����ʾ5
					break;
				case MOUSE_ONLY_MOVED:
					cout << "�ƶ�          " << endl;
					//showch(hout, X, Y, '*');����ӡ�κ�����
					break;
				case MOUSE_NO_ACTION:
				default:
					cout << "��������" << endl;
					showch(hout, X, Y, '0');			//�����ָ��λ����ʾ0
					break;
			} //end of switch
		} //end of while(1)

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//�򿪹��
		to_be_continued(hout, "��������ʾ2����������ƶ��¼������");
	}

	if (1) {
		/* ���ô��ڴ�СΪ15��*40�� */
		setconsoleborder(hout, 40, 15);
		setfontsize(hout, L"������", 36);
		cout << "��������Ϊ������36" << endl;

		to_be_continued(hout, "��ǰϵͳ��������1���", 0, 10);//ȱʡ��22�д�ӡ��������ֻ��15�У������ڵ�10�д�ӡ

		/* ���ô��ڴ�СΪ25��*80�� */
		setconsoleborder(hout, 40, 15);
		setfontsize(hout, L"������", 20);
		cout << "��������Ϊ������20" << endl;

		to_be_continued(hout, "��ǰϵͳ��������2���", 0, 10);//ȱʡ��22�д�ӡ��������ֻ��15�У������ڵ�10�д�ӡ

		/* ���ô��ڴ�СΪ25��*80�У���������СΪ300�� */
		setconsoleborder(hout, 80, 25, 300);
		setfontsize(hout, L"��������", 16);
		cout << "��������Ϊ��������16" << endl;

		to_be_continued(hout, "��ǰϵͳ��������2���", 0, 10);//ȱʡ��22�д�ӡ��������ֻ��15�У������ڵ�10�д�ӡ
		}

	CloseHandle(hout);	// �رձ�׼�����豸���
	CloseHandle(hin);	// �رձ�׼�����豸���

	return 0;
}
