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
  函数名称：
  功    能：显示提示信息
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continued(const HANDLE hout, const char *prompt, const int X=0, const int Y=22)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, X, Y);

	if (prompt) 
		cout << prompt << "，按回车键继续...";
	else
		cout << "按回车键继续...";

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
	const HANDLE hin  = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
		
	if (1) {
		int x, y;

		/* 显示16*16的配色框，每个字符之间加一个空格 */
		for (y = 0; y<16; y++) {
			for (x = 0; x<16; x++)
				showch(hout, x * 2, y, 'x', y, x, 2);	//在xy位置显示x，用x坐标的值做前景色，y坐标的值做背景色（显示两个x是为了使比例协调，可以换成一个x后观察效果）
			cout << endl; //16个前景色变换完成后，换一行
			Sleep(100);  //延时0.1秒（以毫秒为单位，1000=1秒）
			}

		to_be_continued(hout, "配色显示演示完成");
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
		for (x = 0; x<MAX_X; x++) {
			/* 在坐标(x,2)位置处连续打印10个字符 */
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);

			/* 延时0.1秒 */
			Sleep(100);

			if (x<MAX_X - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				showch(hout, x, Y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, "右移特效完成");
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
		for (y = 2; y<MAX_Y; y++) {
			/* 在坐标(x,2)位置处连续打印10个字符 */
			showch(hout, X, y, ch, bg_color, fg_color, LENGTH);

			/* 延时0.3秒 */
			Sleep(300);

			if (y<MAX_Y - 1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				showch(hout, X, y, ' ', COLOR_BLACK, COLOR_WHITE, LENGTH);
			}
		}

		to_be_continued(hout, "下移特效完成");
	}

	if (1) {
		/* 在屏幕的[0,0]-[60,20]区域内随机显示100个字符，值随机，颜色随机
		说明：未判断位置重复，可能最终字符数少于100
		未判断前景色/背景色重复，可能某些位置只看到颜色，看不到字符 */
		const int MAX_X = 60, MAX_Y = 20;
		int x, y, fg_color, bg_color, num;
		char ch;

		srand(unsigned int(time(0))); //生成种子

		for (num = 0; num<100; num++) {
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

		to_be_continued(hout, "随机字符演示完成");
	}

	if (1) {
		int cols, lines, buffer_cols, buffer_lines;

		/* 恢复为初始颜色 */
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);

		/* 清屏 */
		system("cls");

		cout << "原窗口的宽度与高度" << endl;
		cout << "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7";

		cout << endl;

		getconsoleborder(hout, cols, lines, buffer_cols, buffer_lines);
		cout << "当前窗口的宽度：" << cols << " 高度：" << lines << " 缓冲区宽度：" << buffer_cols << " 缓冲区高度：" << buffer_lines << endl;

		to_be_continued(hout, "显示原窗口的宽度与高度完成");

		/* 清屏 */
		system("cls");

		/* 将输出窗口改为 30行 100列，缓冲区200行 */
		setconsoleborder(hout, 100, 30, 200);
		cout << "新窗口的宽度与高度" << endl;
		cout << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		cout << "0         1         2         3         4         5         6         7         8         9";
		cout << endl;

		getconsoleborder(hout, cols, lines, buffer_cols, buffer_lines);
		cout << "当前窗口的宽度：" << cols << " 高度：" << lines << " 缓冲区宽度：" << buffer_cols << " 缓冲区高度：" << buffer_lines << endl;

		to_be_continued(hout, "改变窗口的宽度与高度完成");
	}

	if (1) {
		setcursor(hout, CURSOR_VISIBLE_FULL);
		cout << "光标显示为全高色块，任意键继续";
		getchar(); //暂停为了看清楚

		cout << endl << endl;
		setcursor(hout, CURSOR_VISIBLE_HALF);
		cout << "光标显示为半高色块，任意键继续";
		getchar(); //暂停为了看清楚

		cout << endl << endl;
		setcursor(hout, CURSOR_INVISIBLE);
		cout << "关闭光标显示，任意键继续";
		getchar(); //暂停为了看清楚

		cout << endl << endl;
		setcursor(hout, CURSOR_VISIBLE_NORMAL);
		cout << "光标显示为正常，任意键继续";
		getchar(); //暂停为了看清楚

		to_be_continued(hout, "光标形状演示完成");
		}

	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;

		enable_mouse(hin);

		/* 打印初始光标位置[0,0] */
		setcursor(hout, CURSOR_INVISIBLE);	//关闭光标
		cout << "可测试移动,左键单/双击,右键单/双击,左右键同时单击六种，其中右键双击结束鼠标测试" << endl;
		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置

		while (loop) {
			/* 读鼠标，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			action = read_mouse(hin, X, Y);

			/* 转到第1行进行打印 */
			gotoxy(hout, 0, 1);
			cout << "[当前光标位置] X:" << setw(2) << X << " Y:" << setw(2) << Y << " 操作:";

			switch (action) {
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					cout << "按下左键      " << endl;
					showch(hout, X, Y, '1');			//在鼠标指针位置显示1
					break;
				case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:	//双击左键
					cout << "双击左键      " << endl;
					showch(hout, X, Y, '2');			//在鼠标指针位置显示2
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键
					cout << "按下右键      " << endl;
					showch(hout, X, Y, '3');			//在鼠标指针位置显示3
					break;
				case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//双击右键
					cout << "双击右键      " << endl;
					showch(hout, X, Y, '4');			//在鼠标指针位置显示4
					loop = 0;
					break;
				case MOUSE_LEFTRIGHT_BUTTON_CLICK:		//同时按下左右键
					cout << "同时按下左右键" << endl;
					showch(hout, X, Y, '5');			//在鼠标指针位置显示5
					break;
				case MOUSE_ONLY_MOVED:
					cout << "移动          " << endl;
					//showch(hout, X, Y, '*');不打印任何内容
					break;
				case MOUSE_NO_ACTION:
				default:
					cout << "其它操作" << endl;
					showch(hout, X, Y, '0');			//在鼠标指针位置显示0
					break;
				} //end of switch
			} //end of while(1)

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//打开光标
		to_be_continued(hout, "鼠标操作演示1（读取鼠标移动事件）完成");
		}

	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;

		enable_mouse(hin);

		/* 打印初始光标位置[0,0] */
		setcursor(hout, CURSOR_INVISIBLE);	//关闭光标
		cout << "可测试左键单/双击,右键单/双击,左右键同时单击五种，其中右键双击结束鼠标测试" << endl;
		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置

		while (loop) {
			/* 读鼠标，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			action = read_mouse(hin, X, Y, 0);

			/* 转到第1行进行打印 */
			gotoxy(hout, 0, 1);
			cout << "[当前光标位置] X:" << setw(2) << X << " Y:" << setw(2) << Y << " 操作:";

			switch (action) {
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					cout << "按下左键      " << endl;
					showch(hout, X, Y, '1');			//在鼠标指针位置显示1
					break;
				case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:	//双击左键
					cout << "双击左键      " << endl;
					showch(hout, X, Y, '2');			//在鼠标指针位置显示2
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键
					cout << "按下右键      " << endl;
					showch(hout, X, Y, '3');			//在鼠标指针位置显示3
					break;
				case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//双击右键
					cout << "双击右键      " << endl;
					showch(hout, X, Y, '4');			//在鼠标指针位置显示4
					loop = 0;
					break;
				case MOUSE_LEFTRIGHT_BUTTON_CLICK:		//同时按下左右键
					cout << "同时按下左右键" << endl;
					showch(hout, X, Y, '5');			//在鼠标指针位置显示5
					break;
				case MOUSE_ONLY_MOVED:
					cout << "移动          " << endl;
					//showch(hout, X, Y, '*');不打印任何内容
					break;
				case MOUSE_NO_ACTION:
				default:
					cout << "其它操作" << endl;
					showch(hout, X, Y, '0');			//在鼠标指针位置显示0
					break;
			} //end of switch
		} //end of while(1)

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//打开光标
		to_be_continued(hout, "鼠标操作演示2（不读鼠标移动事件）完成");
	}

	if (1) {
		/* 设置窗口大小为15行*40列 */
		setconsoleborder(hout, 40, 15);
		setfontsize(hout, L"新宋体", 36);
		cout << "设置字体为新宋体36" << endl;

		to_be_continued(hout, "当前系统字体设置1完成", 0, 10);//缺省在22行打印，本窗口只有15行，所以在第10行打印

		/* 设置窗口大小为25行*80列 */
		setconsoleborder(hout, 40, 15);
		setfontsize(hout, L"新宋体", 20);
		cout << "设置字体为新宋体20" << endl;

		to_be_continued(hout, "当前系统字体设置2完成", 0, 10);//缺省在22行打印，本窗口只有15行，所以在第10行打印

		/* 设置窗口大小为25行*80列，缓冲区大小为300行 */
		setconsoleborder(hout, 80, 25, 300);
		setfontsize(hout, L"点阵字体", 16);
		cout << "设置字体为点阵字体16" << endl;

		to_be_continued(hout, "当前系统字体设置2完成", 0, 10);//缺省在22行打印，本窗口只有15行，所以在第10行打印
		}

	CloseHandle(hout);	// 关闭标准输入设备句柄
	CloseHandle(hin);	// 关闭标准输入设备句柄

	return 0;
}
