#pragma once
/*1650254 尤尧寅 计算机一班*/
#include"cmd_console_tools.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<Windows.h>
#include<fstream>
#include<io.h>
#include<conio.h>
#include<iomanip>
#define MAX_COLUMN 9
#define MAX_ROW 9
#define OPEN_FILE_ERROR 1000
#define CANT_FIND_FILE 1111
#define OK 1
#define BASE_COLOR COLOR_BLACK
#define BASE_WORD COLOR_WHITE
#define ROW_NUM 15;
#define COLUMN_NUM 8;
#define SQUARE COLOR_WHITE   //棋盘颜色

struct STEP {
	int x;
	int y;
	int num;
	int old;
	STEP *last;
	STEP *next;
};
struct FILE_NAME{
	char *name;
	FILE_NAME *last;
	FILE_NAME *next;
};
using namespace std;
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
void infile_document(int arr[][MAX_COLUMN]);
void find_document(const char *name);
int open_document(const char *file_name, int shudu[][MAX_COLUMN]);
void print_array(int i_end, int j_end, int a[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN], int origin[][MAX_COLUMN], int x, int y);
bool end(int x, int y);
int reset(int a[][MAX_COLUMN]);
int judge_error(int book[][MAX_COLUMN], const int a[][MAX_COLUMN],int color[][MAX_COLUMN]);
int search1(int x, int y, const int a[][MAX_COLUMN], int color[][MAX_COLUMN]);
int search2(int x, int y, const int a[][MAX_COLUMN], int color[][MAX_COLUMN]);
int search3(int x, int y, const int a[][MAX_COLUMN], int color[][MAX_COLUMN]);
int search1_1(int x, int y, const int a[][MAX_COLUMN]);
int search2_1(int x, int y, const int a[][MAX_COLUMN]);
int search3_1(int x, int y, const int a[][MAX_COLUMN]);
int judge_error_1(const int a[][MAX_COLUMN]);
void judge(int x, int y, int a[][MAX_COLUMN], int book[]);
int dfs(int a[][MAX_COLUMN], int n, int origin[][MAX_COLUMN], int book_[][MAX_COLUMN], int clear);
int shuru(int *x, int *y, int *num, int _x, int _y, int book[][MAX_COLUMN]);
int add_list(int *count, int x, int y, int num, STEP **head, STEP **l, STEP **q);
int delete_list(int *count, int x, int y, int num, STEP **head, STEP **l, STEP **q);
int judge_zero(const int arr[][MAX_COLUMN]);
int input_document(const char *name, FILE_NAME **document_name);
void output_document(FILE_NAME *file_name, FILE_NAME **target);
int move_1();
void print_element(int x, int y, int num);
void print_color(int a[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN], int origin[][MAX_COLUMN], int x, int y, int bo);
int print_judege_array(int p, int i_end, int j_end, int arr[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN], int origin[][MAX_COLUMN], int x, int y);
void copy_arr(int arr[][MAX_COLUMN], int o[][MAX_COLUMN]);
int linklist_destroy_step(STEP *head);
int linklist_destroy_name(FILE_NAME *head);
void tishi();
bool cin_switch(int *p);
int mode2(const int p);
int mode3(const int p);
bool change_mode(const int p);
int shuru_color(int *x, int *y, int *num, int _x, int _y, int origin[][MAX_COLUMN], int a[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN]);