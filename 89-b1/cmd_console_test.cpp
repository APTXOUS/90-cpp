#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：在指定位置，用指定颜色，显示一个字符若干次
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continued(HANDLE hout, int prompt)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, 0, 22);

	switch (prompt) {
	case 1:
		cout << "配色显示演示完成";
		break;
	case 2:
		cout << "右移特效完成";
		break;
	case 3:
		cout << "下移特效完成";
		break;
	case 4:
		cout << "随机字符演示完成";
		break;
	case 5:
		cout << "显示原窗口的宽度与高度完成";
		break;
	case 6:
		cout << "改变窗口的宽度与高度完成";
		break;
	}
	cout << "，按回车键继续...";

	while (_getch() != '\r')
		;

	system("cls"); //调用系统命令清除屏幕
}

/***************************************************************************
  函数名称：
  功    能：在指定位置，用指定颜色，显示一个字符若干次
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

	if (1) {
		int x, y;

		/* 显示16*16的配色框，每个字符之间加一个空格 */
		for (y = 0; y < 16; y++) {
			for (x = 0; x < 16; x++)
				showch(hout, x * 2, y, 'x', y, x, 2);	//在xy位置显示x，用x坐标的值做前景色，y坐标的值做背景色（显示两个x是为了使比例协调，可以换成一个x后观察效果）
			cout << endl; //16个前景色变换完成后，换一行
			Sleep(100);  //延时0.1秒（以毫秒为单位，1000=1秒）
		}
		to_be_continued(hout, 1);
	}

	if (1) {
		const int MAX_X = 50;
		const int Y = 2;
		const int bg_color = COLOR_HYELLOW;	//背景为亮黄色
		const int fg_color = COLOR_HBLUE;	//前景为亮蓝色
		const char ch = '*';        //字符为*(注意：如果是空格，则前景色无法显示)
		const int LENGTH = 10;
		int x;

		/* 将一串字符从左向右移动 */
		for (x = 0; x < MAX_X; x++) {
			/* 在坐标(x,2)位置处连续打印10个字符 */
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);

			/* 延时0.1秒 */
			Sleep(100);

			if (x < MAX_X - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				showch(hout, x, Y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, 2);
	}

	if (1) {
		const int MAX_Y = 12;
		const int X = 2;
		const int bg_color = COLOR_HYELLOW;	//背景为亮黄色
		const int fg_color = COLOR_HBLUE;	//前景为亮蓝色
		const char ch = '*';        //字符为*(注意：如果是空格，则前景色无法显示)
		const int LENGTH = 10;
		int y;

		/* 将一串字符从上向下移动 */
		for (y = 2; y < MAX_Y; y++) {
			/* 在坐标(x,2)位置处连续打印10个字符 */
			showch(hout, X, y, ch, bg_color, fg_color, LENGTH);

			/* 延时0.3秒 */
			Sleep(300);

			if (y < MAX_Y - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				showch(hout, X, y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, 3);
	}

	if (1) {
		/* 在屏幕的[0,0]-[60,20]区域内随机显示100个字符，值随机，颜色随机
		说明：未判断位置重复，可能最终字符数少于100
		未判断前景色/背景色重复，可能某些位置只看到颜色，看不到字符 */
		const int MAX_X = 60, MAX_Y = 20;
		int x, y, fg_color, bg_color, num;
		char ch;

		srand(unsigned int(time(0))); //生成种子

		for (num = 0; num < 100; num++) {
			x = rand() % (MAX_X + 1);
			y = rand() % (MAX_Y + 1);
			fg_color = rand() % 16;
			bg_color = rand() % 16;
			ch = 33 + rand() % 94;   //ASCII码表中33-126为可见图形字符

									 /* 显示一个1 */
			showch(hout, x, y, ch, bg_color, fg_color, 1);

			/* 延时0.05秒 */
			Sleep(50);
		}

		to_be_continued(hout, 4);
	}

	if (1) {
		/* 恢复为初始颜色 */
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);

		/* 清屏 */
		system("cls");

		cout << "原窗口的宽度与高度" << endl;
		cout << "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7";
		to_be_continued(hout, 5);

		/* 清屏 */
		system("cls");

		/* 将输出窗口改为 30行 100列 */
		setconsoleborder(hout, 100, 30);
		cout << "新窗口的宽度与高度" << endl;
		cout << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7         8         9";

		to_be_continued(hout, 6);
	}

	return 0;
}
