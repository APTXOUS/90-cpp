#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ������ɫ
  ���������const HANDLE hout  ��cmd���ھ��
            const int bg_color ������ɫ��0-15��
            const int fg_color ��ǰ��ɫ��0-15��
  �� �� ֵ��
  ˵    ������ɫ��ȡֵ�ɱ���ɫ+ǰ��ɫ��ɣ���16��
            fg_color��0-7    ��   ��   ��   ��   ��   ��   ��   ��
                      8-15 ���� ���� ���� ���� ���� ���� ���� ����
            bg_color��0-7    ��   ��   ��   ��   ��   ��   ��   ��
                      8-15 ���� ���� ���� ���� ���� ���� ���� ����
            ���յ���ɫΪ ����ɫ*16+ǰ��ɫ
***************************************************************************/
void setcolor(const HANDLE hout, const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡ��ǰ���õ�ǰ��ɫ�ͱ���ɫ
  ���������const HANDLE hout  ��cmd���ھ��
            int &bg_color      �����صı���ɫ��0-15��
            int &fg_color      �����ص�ǰ��ɫ��0-15��
  �� �� ֵ��
  ˵    �����������һ��setcolor��ǰ��ɫ�ͱ���ɫ
***************************************************************************/
void getcolor(const HANDLE hout, int &bg_color, int &fg_color)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	bg_color = binfo.wAttributes / 16;
	fg_color = binfo.wAttributes % 16;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ƶ���ָ��λ��
  ���������const HANDLE hout ��cmd���ھ��
            const int X       ��X�����꣨�У�
            const int Y       ��Y�����꣨�У�
  �� �� ֵ��
  ˵    ������Ļ���Ͻ�����Ϊ(0,0)����cmd���ڵĴ�Сδ������������£�ȱʡΪ��
            ����x�ᣬ��Ӧ��(0-79)
            ����y�ᣬ��Ӧ��(0-24)
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡ��ǰ�������λ�õ�����ֵ
  ���������const HANDLE hout ��cmd���ھ��
            int &x            ��ȡ�õ�X�����꣨�У�
			int &y            ��ȡ�õ�Y�����꣨�У�
  �� �� ֵ��
  ˵    �����β��е�&��ʾ���ã������»ὲ���������βε�ֵ���Է��ظ�ʵ��
***************************************************************************/
void getxy(const HANDLE hout, int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	x = binfo.dwCursorPosition.X;
	y = binfo.dwCursorPosition.Y;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ù��״̬����ʾ/����ʾ/ȫ��/���/���ߵȣ�
  ���������const HANDLE hout ��cmd���ھ��
			const int X       ��X�����꣨�У�
			const int Y       ��Y�����꣨�У�
			const char ch     ��Ҫ������ַ�ֵ
  �� �� ֵ��
  ˵    ����X��Y�ķ�Χ�μ�gotoxy������˵��
***************************************************************************/
void setcursor(const HANDLE hout, const int options)
{
	CONSOLE_CURSOR_INFO cursor_info;

	switch (options) {
		case CURSOR_VISIBLE_FULL:
			cursor_info.bVisible = 1;
			cursor_info.dwSize = 100;
			break;
		case CURSOR_VISIBLE_HALF:
			cursor_info.bVisible = 1;
			cursor_info.dwSize = 50;
			break;
		case CURSOR_INVISIBLE:
			cursor_info.bVisible = 0;
			cursor_info.dwSize = 1;
			break;
		case CURSOR_VISIBLE_NORMAL:
		default: //ȱʡ��ʾ��꣬����
			cursor_info.bVisible = 1;
			cursor_info.dwSize = 25;
			break;
		}
	SetConsoleCursorInfo(hout, &cursor_info);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ָ��λ�ã���ָ����ɫ����ʾһ���ַ����ɴ�
  ���������const HANDLE hout ��cmd���ھ��
			const int X       ��X�����꣨�У�
			const int Y       ��Y�����꣨�У�
			const char ch     ��Ҫ������ַ�ֵ
  �� �� ֵ��
  ˵    ����X��Y�ķ�Χ�μ�gotoxy������˵��
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch, const int bg_color, const int fg_color, const int n)
{
	int i;
	gotoxy(hout, X, Y);
	setcolor(hout, bg_color, fg_color);

	/* ѭ��n�Σ���ӡ�ַ�ch */
	for (i=0; i<n; i++)
		putchar(ch);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ָ��λ�ã���ָ����ɫ����ʾһ���ַ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void showstr(const HANDLE hout, const int X, const int Y, const char *str, const int bg_color, const int fg_color)
{
	const char *p;
	gotoxy(hout, X, Y);
	setcolor(hout, bg_color, fg_color);
	for (p = str; *p; p++)
		putchar(*p);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ı�cmd���ڵĴ�С
  ���������const HANDLE hout ��cmd���ھ��
            const int cols    : �µ�����
			const int lines   ���µ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void setconsoleborder(const HANDLE hout, const int cols, const int lines, const int buffer_lines)
{
	char cmd[80];

	/* �ָ�Ϊ����ɫ0��ǰ��ɫ�ף�cmd���ڵ�ȱʡֵ��*/
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	system("cls");	//����

	sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
	system(cmd); //�����µĴ�С

	/* ������Ļ�������Ĵ�С��ȱʡ������Ļ�߶�һ�£��������ã�*/
	if (buffer_lines >= lines) {
		COORD cr;
		cr.X = cols;
		cr.Y = buffer_lines;
		SetConsoleScreenBufferSize(hout, cr); //����cmd���ڵ���Ļ�������Ĵ�С
		}

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡ��ǰcmd���ڵĴ�С����
  ���������const HANDLE hout ��cmd���ھ��
			int &cols         ����ǰ���ڵ�����-����ֵ
			int &lines        ����ǰ���ڵ�����-����ֵ
			int &buffer_cols  ����ǰ������������-����ֵ
			int &buffer_lines ����ǰ������������-����ֵ
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void getconsoleborder(const HANDLE hout, int &cols, int &lines, int &buffer_cols, int &buffer_lines)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	cols  = binfo.dwMaximumWindowSize.X;	//�ɼ����ڵ�����
	lines = binfo.dwMaximumWindowSize.Y;   //�ɼ����ڵ�����
	buffer_cols  = binfo.dwSize.X;         //������������
	buffer_lines = binfo.dwSize.Y;			//������������
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ı�������ڵ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void setfontsize(const HANDLE hout, const wchar_t *fontname, const int fontsize)
{
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize       = sizeof(info);
	info.dwFontSize.Y = fontsize; // leave X as zero
	info.FontWeight   = FW_NORMAL;
	wcscpy(info.FaceName, fontname);	//����
	SetCurrentConsoleFontEx(hout, NULL, &info);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ʹ�����
  ���������const HANDLE hin ��cmd����������
  �� �� ֵ��
  ˵    ����ĳЩcmd���ڿ������ִ�к󣬿��ܻ�ȡ�����֧�֣�����ñ��������ٴμ���
***************************************************************************/
void enable_mouse(const HANDLE hin)
{
	DWORD Mode;

	GetConsoleMode(hin, &Mode);	/* ȡ�ÿ���̨ԭ����ģʽ */
	SetConsoleMode(hin, Mode | ENABLE_MOUSE_INPUT);	//�������֧�֣�����ԭ����֧����꣬�ټ�Ҳû��
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����갴��
  ���������const HANDLE hout ��cmd���ھ��
  �� �� ֵ��
  ˵    ��������˵��������궨���ļ�
  01.typedef struct _MOUSE_EVENT_RECORD      //����¼��ṹ��
  02.{  
  03.    COORD dwMousePosition;      //��ǰ����ڿ���̨���ڻ�������λ��  
  04.    DWORD dwButtonState;        //��갴����״̬  
  05.    DWORD dwControlKeyState;    //���Ƽ�״̬  
  06.    DWORD dwEventFlags;         //����¼�����  
  07.} MOUSE_EVENT_RECORD;  
  08.
  09.������갴��״̬dwButtonState���ܵ�ֵ�� 
  10.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  11.FROM_LEFT_1ST_BUTTON_PRESSED        ����ߵ�����������      һ����˵���������� 
  12.FROM_LEFT_2ND_BUTTON_PRESSED        ����ڶ�������������    һ����˵������м������ǹ��ּ� 
  13.FROM_LEFT_3RD_BUTTON_PRESSED        �������������������
  14.FROM_LEFT_4TH_BUTTON_PRESSED        ������ĸ����������� 
  15.RIGHTMOST_BUTTON_PRESSED            ���ұߵ�����������      һ����˵������Ҽ� 
  16.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  17.���Ƽ�״̬dwControlKeyState������¼���һ�� 
  18.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  19.ENHANCED_KEY        ��չ��������  
  20.LEFT_ALT_PRESSED    ��Alt��������  
  21.LEFT_CTRL_PRESSED   ��Ctrl��������  
  22.RIGHT_ALT_PRESSED   ��Alt��������  
  23.RIGHT_CTRL_PRESSED  ��Ctrl��������  
  24.NUMLOCK_ON          ������������  
  25.SCROLLLOCK_ON       ������������  
  26.CAPSLOCK_ON         ��д��������  
  27.SHIFT_PRESSED       Shift�������� 
  28.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  29.����¼�����dwEventFlags�����¼��� 
  30.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  31.DOUBLE_CLICK            ˫������һ��ֻ��Ϊ��ͨ�����¼����ڶ�������Ϊ˫���¼� 
  32.MOUSE_HWHEELED          ˮƽ�������ƶ� 
  33.MOUSE_MOVED             ����ƶ�
  34.MOUSE_WHEELED           ��ֱ�������ƶ�
  35.0                       ������м������»����ͷ�
***************************************************************************/
int read_mouse(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos;

	while (1) {
		/* ��hin�ж�����״̬��������ꡢ���̵ȣ� */
		ReadConsoleInput(hin, &mouseRec, 1, &res);
		/* �������з�����¼����������� */
		if (mouseRec.EventType != MOUSE_EVENT)
			continue;

		/* �ӷ����ж����ָ�뵱ǰ������ */
		crPos = mouseRec.Event.MouseEvent.dwMousePosition;
		X = crPos.X;
		Y = crPos.Y;

		if (enable_read_mouse_moved && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			return MOUSE_ONLY_MOVED;

		if (mouseRec.Event.MouseEvent.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)) { //ͬʱ�������Ҽ�
			return MOUSE_LEFTRIGHT_BUTTON_CLICK;
			}
		else if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //�������
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_LEFT_BUTTON_CLICK;
			}
		else if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { //�����Ҽ�
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_RIGHT_BUTTON_CLICK;
			}
		else //�����������������������Ҫ���֣����ж� FROM_LEFT_2ND_BUTTON_PRESSED��
			;
		} //end of while(1)

	return MOUSE_NO_ACTION; //�˾�Ӧ��ִ�в�����Ϊ����ĳЩ������������ȫ��֧���󣬼�
}

