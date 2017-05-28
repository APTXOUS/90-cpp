#pragma once
/*1650254 尤尧寅 计1*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
#define BASE_COLOR	0
#define BASE_WORD 7
#define MAX_LOW 9
#define MAX_COLUMN 9
#define MAX_BALL 7
#define MAX_SPACE MAX_LOW*MAX_COLUMN
#define MAX_ADD 3
#define MAX_BALL_ORI 5
const int a_step[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
const int a_color[7]= {1,2,3,4,12,14,11};
void print_routinue_black(int low, int column, int astep[][MAX_COLUMN], int x, int y);
void print_routinue_colour(int low, int column, int astep[][MAX_COLUMN], int x, int y, int a[][MAX_COLUMN]);
int CHange_array(int root[][MAX_SPACE], int step[][MAX_COLUMN], int start_x, int start_y, int end_x, int end_y);
void reform(int step[][MAX_COLUMN], int root[][MAX_SPACE]);
int BFS(int low, int column, int a[][MAX_COLUMN], int start_x, int start_y, int end_x, int end_y, int step[][MAX_COLUMN], int rout[][MAX_SPACE]);
int judge_delete_low(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y);
int judge_delete_column(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y);
int judge_delete_angle(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y);
void delete_ball(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y, int temp1, int temp2, int temp3, int temp4);
int judge_delete_ball_aftermove(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y);
bool end(int x, int y);
void tishi();
bool cin_switch(int *p);
void shuru(int *a, int *b);
void add_random_ball(int n, int low, int col, int a[][MAX_COLUMN], int *x);
void print_array(int i_end, int j_end, int a[][MAX_COLUMN]);
void random_ball_origin(int p, int a[][MAX_COLUMN], int *low, int *column);
bool check_60(int p, int a[][MAX_COLUMN], int low, int column, double c);
void print_nextthree(int *b);
int change_shuru(int *x, int*y);
void shuru_start_end(int *start_x, int *start_y, int *end_x, int *end_y, int a[][MAX_COLUMN], int low, int column);
void auto_game(int p, int a[][MAX_COLUMN], int low, int column);
int check_win_lose(int a[][MAX_COLUMN], int low, int column);
void man_game(int p, int a[][MAX_COLUMN], int low, int column);
bool change_mode(int p, int(*a)[MAX_COLUMN], int *low, int *column);
void cout_orgin(int p, int a[][MAX_COLUMN], int *low, int *column);
void color_origin(int p, int a[][MAX_COLUMN], int *low, int *column);
void color_origin_with(int p, int a[][MAX_COLUMN], int *low, int *column);
int auto_color(int p, int a[][MAX_COLUMN], int low, int column);
void read_x_y(int p, int a[][MAX_COLUMN], int low, int column, int *X, int *Y, int *action, int *loop);
void printf_ball(int a, int x, int y);
void move(int rout[][MAX_SPACE], int a[][MAX_COLUMN], int low, int column);
int cal(int i, int j, int low, int column);
int color_game(int p, int a[][MAX_COLUMN], int low, int column);
void print_nextthree_color(int *b, int low, int column, int k);
void printf_defeng(int num, int low, int column);
int judge_delete_angle_anti(int low, int column, int a[][MAX_COLUMN], int click_x, int click_y);
void printf_detail(int low, int column, int a[][MAX_COLUMN], int k, int num, int l, int clear_ball = 0);
void origin_ball(int column, int low);
void printf_after_move(int a[][MAX_COLUMN], int i, int j);
int read_mouse_and_key(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved);
void clear(int a[][MAX_COLUMN]);
int random_next_three(int b[MAX_ADD]);
void action_2(int a[][MAX_COLUMN], int *count_num, int b[MAX_ADD], int low, int column, int k, int action, int p);
//菜单项9废弃代码
//int read_mouse2(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved);
//int read_moused(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved);