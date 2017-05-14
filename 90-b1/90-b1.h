#pragma once
/*1650254 尤尧寅 计算机1班*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include"cmd_console_tools.h"
using namespace std;
#define BASE_COLOR	COLOR_BLACK //背景颜色
#define BASE_WORD COLOR_WHITE   //文字颜色
#define SQUARE COLOR_WHITE   //棋盘颜色
#define MAX_ROW 9     //最大行数
#define MAX_COLUMN 9  //最大列数
#define MAX_BALL 9   //最大球数
#define SPEED 100
#define MAX_SPACE MAX_ROW*MAX_COLUMN //最大面积
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
const int step[][2] = { {1,0}, {0,1}};
const struct type_name {
	int front_color;//存储字符颜色
	char name[3];//存储字符形状
	int back_color;//存储背景颜色
};
const type_name ball[12] = { 
 COLOR_WHITE,   "■" ,SQUARE ,
 COLOR_BLACK,   "●" ,SQUARE ,
 COLOR_BLUE ,   "●" ,SQUARE ,
 COLOR_GREEN ,  "●" ,SQUARE ,
 COLOR_CYAN ,   "●" ,SQUARE ,
 COLOR_RED,     "●" ,SQUARE ,
 COLOR_PINK ,   "●" ,SQUARE ,
 COLOR_YELLOW , "●" ,SQUARE ,
 COLOR_HBLUE ,  "●" ,SQUARE ,
 COLOR_HGREEN,  "●" ,SQUARE,
 COLOR_HWHITE,  "■" ,SQUARE ,
 COLOR_HBLACK,  "●" ,SQUARE ,
};//小球颜色
const type_name signedball[11] = {
	COLOR_WHITE,   "■" ,SQUARE ,
	COLOR_BLACK,   "◎" ,SQUARE ,
	COLOR_BLUE ,   "◎" ,SQUARE ,
	COLOR_GREEN ,  "◎" ,SQUARE ,
	COLOR_CYAN ,   "◎" ,SQUARE ,
	COLOR_RED,     "◎" ,SQUARE ,
	COLOR_PINK ,   "◎" ,SQUARE ,
	COLOR_YELLOW , "◎" ,SQUARE ,
	COLOR_HBLUE ,  "◎" ,SQUARE ,
	COLOR_HGREEN,  "◎" ,SQUARE,
	COLOR_HWHITE,   "■" ,SQUARE ,
};//小球颜色
const  type_name ball_signed[10] = { 
 COLOR_WHITE,  "○" ,SQUARE,
 COLOR_BLACK,  "○" ,SQUARE,
 COLOR_BLUE ,  "○" ,SQUARE,
 COLOR_GREEN , "○" ,SQUARE,
 COLOR_CYAN ,  "○" ,SQUARE,
 COLOR_RED,    "○" ,SQUARE,
 COLOR_PINK ,  "○" ,SQUARE,
 COLOR_YELLOW ,"○" ,SQUARE,
 COLOR_HBLUE , "○" ,SQUARE,
 COLOR_HGREEN, "○" ,SQUARE
};
const type_name line[11] = {
 COLOR_HBLACK,"╔" ,SQUARE,//0
 COLOR_HBLACK,"═" ,SQUARE,//1
 COLOR_HBLACK,"╦" ,SQUARE,//2
 COLOR_HBLACK,"╗" ,SQUARE,//3
 COLOR_HBLACK,"╠" ,SQUARE,//4
 COLOR_HBLACK,"╬" ,SQUARE,//5
 COLOR_HBLACK,"╣" ,SQUARE,//6
 COLOR_HBLACK,"╚" ,SQUARE,//7
 COLOR_HBLACK,"╩" ,SQUARE,//8
 COLOR_HBLACK,"╝" ,SQUARE,//9
 COLOR_HBLACK,"║" ,SQUARE//10
};
void add_random_ball(int *temp);
void random_ball_origin(int p, int a[][MAX_COLUMN], int *row, int *column);
void shuru(int *a, int *b);
void tishi();
bool cin_switch(int *p);
bool change_mode(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void cout_orgin(int p, int a[][MAX_COLUMN], int *row, int *column, int book[][MAX_COLUMN]);
void print_array(int i_end, int j_end, int a[][MAX_COLUMN], int book[][MAX_COLUMN]);
bool end(int x, int y);
void output(char *name);
int judge_delete(int row, int column, int a[][MAX_COLUMN], int click_x, int click_y, int count);
int all_judge(int row, int column, int a[][MAX_COLUMN], int book[][MAX_COLUMN]);
int delete_ball(int row, int column, int a[][MAX_COLUMN], int book[][MAX_COLUMN]);
void mode1(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode2(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode3(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode4(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode5(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode6(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode7(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode8(int p, int(*a)[MAX_COLUMN], int *row, int *column);
void mode9(int p, int(*a)[MAX_COLUMN], int *row, int *column);
int down_ball(int row, int column, int a[][MAX_COLUMN]);
int reset(int a[][MAX_COLUMN]);
void set_sign(int book[][MAX_COLUMN], int a[][MAX_COLUMN]);
int autojudge(int row, int column, int a[][MAX_COLUMN], int book[][MAX_COLUMN], int moveable[][MAX_COLUMN]);
void color_origin(int p, int a[][MAX_COLUMN], int *row, int *column);
void color_origin_with(int p, int a[][MAX_COLUMN], int *row, int *column, int book[][MAX_COLUMN], int sign = 0);
void output_color(struct type_name vect);
void down_ball_color(int p, int(*a)[MAX_COLUMN], int *row, int *column);
int cal(int i, int j, int row, int column);
void move_ball(int p, int a[][MAX_COLUMN], int *row, int *column, int end, int now, int start);
void printf_ball(int a, int x, int y);
int ball_moveable(int p, int(*a)[MAX_COLUMN], int *row, int *column, int record[][MAX_COLUMN], int moveable[][MAX_COLUMN]);
void read_x_y(int p, int a[][MAX_COLUMN], int low, int column, int *X, int *Y, int *action, int *loop);
int read_loop(int p, int a[][MAX_COLUMN], int *row, int *column, int *start_y, int *start_x, int *action, int *loop, int moveable[][MAX_COLUMN]);
void printf_ball_signed(int a, int x, int y);
void exchange_ball(int p, int a[][MAX_COLUMN], int low, int column, int *start_x, int *start_y, int *end_x, int *end_y);
void printf_defeng(int num, int low, int column);
int cal_defeng(int book[][MAX_COLUMN]);
