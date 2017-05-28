#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include<iomanip>
using namespace std;
double num = 0;//记录步数
int a1[11] = { 0 };
int b1[11] = { 0 };
int c1[11] = { 0 };
const int dis = 31;
const int height = 13;
const int length = 23;
int a_num=0;//a柱盘子数
int b_num=0;//b柱盘子数
int c_num=0;//c柱盘子数
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
//速度延时函数
void time1(int speed)
{
	if (speed == 0)
		while (_getch() != '\r');
	else if (speed == 1)
		Sleep(50);
	else if (speed == 2)
		Sleep(40);
	else if (speed == 3)
		Sleep(30);
	else if (speed == 4)
		Sleep(20);
	else if (speed == 5)
		Sleep(1);
}
//打印内部数组函数
void print(int n, char a, char b, char c)
{
	cout << setiosflags(ios::right) << setw(5) << num;
	cout << ": ";
	cout << setw(2) << n;
	cout << "#" << " " << a << "---->" << c;
	cout << " A:";
	for (int i = 9; i >= 0; i--)
		if (a1[i] != 0)
			cout << setw(2) << a1[i];
	for (int i = 9; i >= 0; i--)
		if (a1[i] == 0)
			cout << "  ";
	cout << " B:";
	for (int i = 9; i >= 0; i--)
		if (b1[i] != 0)
			cout << setw(2) << b1[i];
	for (int i = 9; i >= 0; i--)
		if (b1[i] == 0)
			cout << "  ";
	cout << " C:";
	for (int i = 9; i >= 0; i--)
		if (c1[i] != 0)
			cout << setw(2) << c1[i];
	for (int i = 9; i >= 0; i--)
		if (c1[i] == 0)
			cout << "  ";
	cout << endl;
}
//打印纵向数组函数
void printk(int n, char a, char b, char c, double num1, int speed,int x_set,int y_set,int rey,int xuan_xiang)//输出部分
{
	if (num == 0)
	{
		if(xuan_xiang!=9)
			cout << "从" << a << "移动到" << c << "，共 " << n << " 层，延时设置为" << speed << endl;
		gotoxy(hout, 0, y_set + 1);
		cout << "         =========================\n           A         B         C  ";
	}
	gotoxy(hout, 0, 18+rey);
	if (num == 0)
		print(0, a, b, c);
	else
		print(n, a, b, c);
	int num2 = 0;
	for (int i = 9; i >= 0; i--)
		if (a1[i] != 0)
		{
			gotoxy(hout, x_set, y_set - num2);
			cout << a1[i];
			num2++;
		}
	for (int i = 9; i >= 0; i--)
		if (a1[i] == 0)
		{
			gotoxy(hout, x_set, y_set - num2);
			cout << "  ";
			num2++;
		}
	num2 = 0;
	for (int i = 9; i >= 0; i--)
		if (b1[i] != 0)
		{
			gotoxy(hout, x_set+10, y_set - num2);
			cout << b1[i];
			num2++;
		}
	for (int i = 9; i >= 0; i--)
		if (b1[i] == 0)
		{
			gotoxy(hout, x_set+10, y_set - num2);
			cout << "  ";
			num2++;
		}
	num2 = 0;
	for (int i = 9; i >= 0; i--)
		if (c1[i] != 0)
		{
			gotoxy(hout, x_set+22, y_set - num2);
			cout << c1[i];
			num2++;
		}
	for (int i = 9; i >= 0; i--)
		if (c1[i] == 0)
		{
			gotoxy(hout, x_set+22, y_set - num2);
			cout << "  ";
			num2++;
		}
	if(num!=0)
		time1(speed);
}
//出栈函数
void push(int x[], int y[])//出栈入栈
{
	for (int j = 9; j >= 0; j--)
	{
		y[j] = y[j - 1];
	}
	y[0] = x[0];
	for (int j = 0; j < 10; j++)
		x[j] = x[j + 1];
}
//交换函数
void change(char flag1, char flag2)//交换
{
	if (flag1 == 'A'&&flag2 == 'B')
	{
		push(a1, b1);
		a_num--;
		b_num++;
	}
	else if (flag1 == 'A'&&flag2 == 'C')
	{
		push(a1, c1);
		a_num--;
		c_num++;
	}
	else if (flag1 == 'B'&&flag2 == 'C')
	{
		push(b1, c1);
		b_num--;
		c_num++;
	}
	else if (flag1 == 'B'&&flag2 == 'A')
	{
		push(b1, a1);
		b_num--;
		a_num++;
	}
	else if (flag1 == 'C'&&flag2 == 'A')
	{
		push(c1, a1);
		c_num--;
		a_num++;
	}
	else if (flag1 == 'C'&&flag2 == 'B')
	{
		push(c1, b1);
		c_num--;
		b_num++;
	}
}
//选项1
void jiben(int n, char a, char b, char c)
{
	cout << n << "#" << " " << a << "---->" << c << endl;
}
//选项2
void jibenbushu(int n, char a, char b, char c)
{
	cout << setiosflags(ios::right) << setw(5) << num;
	cout << ": ";
	cout << n << "#" << " " << a << "---->" << c << endl;
}
//选项3
void neibushuzuxianhi(int n, char a, char b, char c)
{
	change(a, c);
	print(n, a, b, c);
}
//选项4
void neibushuzuxianhizongxiang(int n, char a, char b, char c, int xuan, int speed)
{
	change(a, c);
	printk(n, a, b, c, num, speed, 11, 13, 0,xuan);	
}
//画圆柱
void huayuanzhu()
{
	gotoxy(hout, 1, height + 3);
	setcolor(hout, 14, 0);
	cout << "                       ";
	setcolor(hout, 0, 0);
	cout << "         ";
	setcolor(hout, 14, 0);
	cout << "                       ";
	setcolor(hout, 0, 0);
	cout << "         ";
	setcolor(hout, 14, 0);
	cout << "                       ";
	time1(1);
	for (int i = 0; i < height; i++)
	{
		gotoxy(hout, 12, height + 3 - i);
		cout << " ";
		gotoxy(hout, 12 + dis + 1, height + 3 - i);
		cout << " ";
		gotoxy(hout, 12 + dis + dis + 2, height + 3 - i);
		cout << " ";
		time1(1);
	}
	setcolor(hout, 0, 7);
	gotoxy(hout, 0, 20);


}
//画盘子
void panzi(int x, int y, int n)
{
	gotoxy(hout, x - n, y);
	setcolor(hout, n + 2, 0);
	for (int i = 0; i < 2*n+1; i++)
		cout << " ";
	setcolor(hout, 0, 7);
}
//初始化盘子
void huapanzi(int n, char a, char b, char c)
{
	int temp = a - 65;
	for (int i = 0; i < n; i++)
	{
		time1(1);
		panzi((length+1)/2+(dis+1)*temp, height + 2 - i,n-i);
	}
	Sleep(1000);
}
//画黑框
void black(int x, int y, int n)
{
	gotoxy(hout, x - n, y);
	setcolor(hout, 0, 0);
	for (int i = 0; i < 2 * n + 1; i++)
		cout << " ";
	setcolor(hout, 0, 7);
}
//补柱函数
void buzhuzi(int x, int y)
{
	gotoxy(hout, x, y);
	setcolor(hout, 14, 0);
	cout << " ";
}
//移动盘子的函数
void yidongpanzi(int n,char a,char c,int temp1,int temp2,int speed)
{
	int a_temp = (int)(a - 65);
	int c_temp = (int)(c - 65);
	if (a - c < 0)
	{
		for (int i = 1; i <= height + 2 - temp1; i++)
		{
			black((length + 1) / 2 + (dis + 1)*a_temp, 3 + height + 1 - temp1 - i, n);
			if (i + temp1 <= height)
				buzhuzi((length + 1) / 2 + (dis + 1)*a_temp, 3 + height + 1 - temp1 - i);
			panzi((length + 1) / 2 + (dis + 1)*a_temp, 3 + height + 1 - temp1 - i - 1, n);
			if (speed != 0)
				time1(speed);
			else
				time1(1);
		}
		for (int i = 0; i <= (c-a)*dis+(c_temp-a_temp)-1; i++)
		{
			black((length + 1) / 2 + (dis + 1)*a_temp + i, 1, n);
			panzi((length + 1) / 2 + (dis + 1)*a_temp + i+1 , 1, n);
			if (speed != 0)
				time1(speed);
			else
				time1(1);
		}
		for (int i = 1; i <= height - temp2 + 1; i++)
		{
			black((length + 1) / 2 + (dis + 1)*a_temp + (c-a)*(dis + 1), i, n);
			if (i < height+3 && i > 3)
				buzhuzi((length + 1) / 2 + (dis + 1)*a_temp + (c-a)*(dis + 1), i);
			panzi((length + 1) / 2 + (dis + 1)*a_temp + (c-a)*(dis + 1), i+1, n);
			if (speed != 0)
				time1(speed);
			else
				time1(1);
		}
	}
	else
	{
		for (int i = 1; i <= height + 2 - temp1; i++)
		{
			black((length + 1) / 2 + (dis + 1)*a_temp, 3 + height + 1 - temp1 - i, n);
			if (i + temp1 <= height)
				buzhuzi((length + 1) / 2 + (dis + 1)*a_temp, 3 + height + 1 - temp1 - i);
			panzi((length + 1) / 2 + (dis + 1)*a_temp, 3 + height + 1 - temp1 - i - 1, n);
			if (speed != 0)
				time1(speed);
			else
				time1(1);
		}
		for (int i = 0; i <=(a - c)*dis - (c_temp - a_temp) - 1; i++)
		{
			black((length + 1) / 2 + (dis + 1)*a_temp - i, 1, n);
			panzi((length + 1) / 2 + (dis + 1)*a_temp - i - 1, 1, n);
			if (speed != 0)
				time1(speed);
			else
				time1(1);
		}
		for (int i = 1; i <= height - temp2 + 1; i++)
		{
			black((length + 1) / 2 + (dis + 1)*a_temp - (a - c)*(dis+1), 2 + i - 2, n);
			if (i < height + 3 && i > 3)
				buzhuzi((length + 1) / 2 + (dis + 1)*a_temp - (a - c)*(dis+1), 2 + i - 2);
			panzi((length + 1) / 2 + (dis + 1)*a_temp - (a - c)*(dis + 1), 2 + i - 1, n);
			if (speed != 0)
				time1(speed);
			else
				time1(1);
		}
	}
}
//移动盘子
void yidong(int n,char a,char c,int speed)
{
	int a_temp = (int)(a - 65);
	int c_temp = (int)(c - 65);
	int temp1=-1;
	int temp2=-1;
	switch (a_temp)
	{
	case 0:
		temp1 = a_num;
		break;
	case 1:
		temp1 = b_num;
		break;
	case 2:
		temp1 = c_num;
		break;
	}
	switch (c_temp)
	{
	case 0:
		temp2 = a_num;
		break;
	case 1:
		temp2 = b_num;
		break;
	case 2:
		temp2 = c_num;
		break;
	}
	yidongpanzi(n, a, c, temp1, temp2,speed);
}
//第一次移动
void diyiciyidong(int n, char a, char b, char c)
{
	if (num == 1)
		yidong(n, a, c, 1);
}
//自动移动
void automaticmove(int n, char a, char b, char c, int xuan, int speed)
{
	if (num == 1)
		time1(speed);
	yidong(n, a, c,speed);
	change(a, c);
	printk(n, a, b, c, num, speed, 11, 28, 15,xuan);
}
//判断移动出错类型
int error(char a, char b)
{
	int a_temp = a - 65;
	int b_temp = b - 65;
	int temp1=-1;
	int temp2=-1;
	int flag1=0;//柱源为空为 2
	int flag2=0;//大盘压小盘为3
	switch (a_temp)
	{
	case 0:	
		temp1 = a1[0];
		if (a_num == 0)
			flag1 = 2;
		break;
	case 1:
		temp1 = b1[0];
		if (b_num == 0)
			flag1 = 2;
		break;
	case 2:
		temp1 = c1[0];
		if (c_num == 0)
			flag1 = 2;
		break;
	}
	switch (b_temp)
	{
	case 0:
		temp2 = a1[0];
		if (a_num == 0)
			flag2 = 2;
		break;
	case 1:
		temp2 = b1[0];
		if (b_num == 0)
			flag2 = 2;
		break;
	case 2:
		temp2 = c1[0];
		if (c_num == 0)
			flag2 = 2;
		break;
	}
	if (flag1 == 2)
		return 1;//柱源为空
	else if (temp1 > temp2 &&flag2 != 2)
		return 2;//大盘压小盘
	else
		return 0;//无错误
}
//转换输入字符并判断是否正确
int dial(char *a, char *b)
{
	if (*a >=97&&*a<=103)
	{
		*a = *a - 32;
	}
	if (*b >= 97 && *b <= 103)
	{
		*b = *b - 32;
	}
	if (*b == *a)
		return 4;
	else if ((*a == 'A' || *a == 'B' || *a == 'C') && (*b == 'A' || *b == 'B' || *b == 'C'))
		return error(*a, *b);
	else
		return 4;
}
//判断游戏是否结束
int function(char c)
{
	c = c - 65;
	switch (c)
	{
	case 0:
		if (b_num == 0 && c_num == 0)
			return 0;
		break;
	case 1:
		if (a_num == 0 && c_num == 0)
			return 0;
		break;
	case 2:
		if (a_num == 0 && b_num == 0)
			return 0;
		break;
	}
	return 1;
}
//游戏模式
void youxiban(int n, char a, char b, char c, int xuan, int speed)
{
	while (function(c))
	{
		char a_1, b_1;
		gotoxy(hout, 0, 18 + 17);
		cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C)：";
		while (1)
		{
			int sign=0;
			gotoxy(hout, 51, 18 + 17);
			a_1 = _getch();
			cout << a_1;
			b_1 = _getch();
			cout << b_1;
			if (!dial(&a_1, &b_1))
				break;
			else if (dial(&a_1, &b_1) != 4)
			{
				switch (error(a_1, b_1))
				{
				case 0:
					sign = 1;
					break;
				case 1:
					gotoxy(hout, 0, 18 + 18);
					cout << "柱源为空！请重新输入！";
					time1(0);
					break;
				case 2:
					gotoxy(hout, 0, 18 + 18);
					cout << "大盘压小盘！请重新输入！";
					time1(0);
					break;
				}
				if (sign == 1)
					break;
			}
			setcolor(hout, 0, 7);
			gotoxy(hout, 51, 18 + 17);
			cout << "                 " << '\n' << "                                 ";
			gotoxy(hout, 51, 18 + 17);
		}
		int temp=-1;
		switch (a_1-65)
		{
		case 0:
			temp = a1[0];
			break;
		case 1:
			temp = b1[0];
			break;
		case 2:
			temp = c1[0];
			break;
		}
		num++;
		yidong(temp, a_1, b_1, speed);
		change(a_1, b_1);
		printk(temp, a, b, c, num, speed, 11, 28, 15, xuan);
		gotoxy(hout, 0, 18 + 15);
		print(temp, a, b, c);
		gotoxy(hout, 51, 18 + 17);
		cout << "                 " << '\n' << "                                 ";
		gotoxy(hout, 51, 18 + 17);
	}
	gotoxy(hout, 0, 18 + 19);
	cout << "游戏结束";
}
//输出分类
void print_set(int n, char a, char b, char c, int xuan, int speed)
{
	switch (xuan) {
	case 1:
		jiben(n, a, b, c);
		break;
	case 2:
		jibenbushu(n, a, b, c);
		break;
	case 3:
		neibushuzuxianhi(n, a, b, c);
		break;
	case 4:
		neibushuzuxianhizongxiang(n, a, b, c, xuan, speed);
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		diyiciyidong(n, a, b, c);
		break;
	case 8:
		automaticmove(n, a, b, c, xuan, speed);
		break;
	case 9:
		break;
	}
}
//递归函数
void hn(int n, char a, char b, char c, int xuan, int speed)
{
	void change(char flag1, char flag2);
	if (n == 1)
	{
		num++;
		print_set(n, a, b, c, xuan, speed);
	}
	else
	{
		n--;
		hn(n, a, c, b, xuan, speed);
		num++;
		print_set(n + 1, a, b, c, xuan, speed);
		hn(n, b, a, c, xuan, speed);
	}
}
//输出提示函数
void tishi()
{
	cout << "-------------------------------- -" << endl;
	cout << "1.基本解" << endl;
	cout << "2.基本解(步数记录)" << endl;
	cout << "3.内部数组显示(横向)" << endl;
	cout << "4.内部数组显示(纵向 + 横向)" << endl;
	cout << "5.图形解 - 预备 - 画三个圆柱" << endl;
	cout << "6.图形解 - 预备 - 在起始柱上画n个盘子" << endl;
	cout << "7.图形解 - 预备 - 第一次移动" << endl;
	cout << "8.图形解 - 自动移动版本" << endl;
	cout << "9.图形解 - 游戏版" << endl;
	cout << "0.退出" << endl;
	cout << "-------------------------------- -" << endl;
	cout << "请输入(0-9)                                 " << endl;
	gotoxy(hout, 11, 12);
}
//初始化数组
void set(char a, int n)//初始化
{
	if (a == 'A')
	{
		a_num = n;
		for (int i = 0; i < n; i++)
			a1[i] = i + 1;
	}
	else if (a == 'B')
	{
		b_num = n;
		for (int i = 0; i < n; i++)
			b1[i] = i + 1;
	}
	else
	{
		c_num = n;
		for (int i = 0; i < n; i++)
			c1[i] = i + 1;
	}
}
//输入speed 
void shuru1(int *speed)
{
	int temp;
	while (1)
	{
		cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短)";
		cin >> temp;//记得要判断输入输出！！！！！！！！
		if (cin.fail())
		{
			cin.clear(1024);
			cin.ignore();
		}
		if (temp == 0 || temp == 1 || temp == 2 || temp == 3 || temp == 4 || temp == 5)
			break;
	}
	getchar();
	*speed = temp;

}
//输入函数
void shuru(int xuan, int *n, char *a, char *b, char *c, int *speed)
{
	while (1)
	{
		cout << "请输入汉诺塔的层数（1-10）:";
		cin >> *n;
		if (cin.fail())
		{
			cin.clear(1024);
			cin.ignore();
		}
		else if (*n >= 1 && *n <= 10)
			break;
	}
	while (1)
	{
		cout << "请输入起始柱(A-C):";
		cin >> *a;
		if (*a == 'A' || *a == 'B' || *a == 'C')
			break;
		else if (*a == 'a' || *a == 'b' || *a == 'c')
		{
			*a = *a - 32;
			break;
		}
	}
	while (1)
	{
		cout << "请输入目标柱(A-C):";
		cin >> *c;
		if (*c == *a)
		{
			cout << "目标柱不能与起始柱相同" << endl;
			continue;
		}
		else if (*c == 'A' || *c == 'B' || *c == 'C')
			break;
		else if (*c == 'a' || *c == 'b' || *c == 'c')
		{
			*c = *c - 32;
			break;
		}
	}
	*b = 198 - *a - *c;
	set(*a, *n);
	if (xuan == 4 || xuan == 8)
	{
		shuru1(speed);
		system("cls");
	}
}
//重新初始化
void clear()
{
	for (int i = 0; i < 10; i++)
	{
		a1[i] = 0;
		b1[i] = 0;
		c1[i] = 0;
	}
	a_num = 0;//a柱盘子数
	b_num = 0;//b柱盘子数
	c_num = 0;//c柱盘子数
}
//暂停函数+窗口大小重定义
void stop(int xuan_xiang)
{
	if (xuan_xiang == 4||xuan_xiang==6||xuan_xiang==7)
		gotoxy(hout, 0, 25);
	if(xuan_xiang==8)
		gotoxy(hout, 0, 34);
	cout << "按回车键继续...";
	while (_getch() != '\r')
		;
	setconsoleborder(hout, 100, 30);
}
//不同的函数的一些小参数
void change_mode(int *n, char *a, char *b, char *c, int *speed,int xuan_xiang)
{
	if (xuan_xiang == 5)
	{
		system("cls");
		huayuanzhu();
	}
	else
	{
		shuru(xuan_xiang, n, a, b, c, speed);
		if (xuan_xiang == 9)
		{
			system("cls");
			setconsoleborder(hout, 130, 50);
			huayuanzhu();
			huapanzi(*n, *a, *b, *c); 		
			gotoxy(hout, 0, 18 + 15);
			print(0, *a, *b, *c);
			printk(*n, *a, *b, *c, 0, 5, 11, 28, 15, xuan_xiang);
			youxiban(*n,*a,*b,*c,xuan_xiang,5);
		}
		else
		{
			if (xuan_xiang == 4)
			{
				printk(*n, *a, *b, *c, 0, *speed, 11, 13, 0, xuan_xiang);
				if(speed==0)
					getchar();
			}
			if (xuan_xiang == 8)
			{
				system("cls");
				setconsoleborder(hout, 130, 50);
				printk(*n, *a, *b, *c, num, *speed, 11, 28, 15,xuan_xiang);
				huayuanzhu();
				huapanzi(*n, *a, *b, *c);
			}
			if (xuan_xiang == 7)
			{
				system("cls");
				huayuanzhu();
				huapanzi(*n, *a, *b, *c);
				diyiciyidong(*n, *a, *b, *c);
			}
			if (xuan_xiang == 6)
			{
				system("cls");
				huayuanzhu();
				huapanzi(*n, *a, *b, *c);
			}
			else
				hn(*n, *a, *b, *c, xuan_xiang, *speed);
		}
	}
}
//主函数
int main()
{
	while (1)//输入选项
	{
		int n, speed = 5, xuan_xiang;
		char a, b, c;
		num = 0;
		system("cls");
		tishi();
		while (1)
		{
			xuan_xiang = _getch();
			xuan_xiang -= 48;
			cout << xuan_xiang << endl;
			if (xuan_xiang >= 0 && xuan_xiang <= 9)
				break;
			else
			{
				gotoxy(hout, 0, 0);
				tishi();
			}
		}
		if (xuan_xiang == 0)
			break;
		change_mode(&n, &a, &b, &c, &speed,xuan_xiang);
		stop(xuan_xiang);
		clear();
	}
	return 0;
}
