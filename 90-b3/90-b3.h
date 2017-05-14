/*1650254 尤尧寅 计算机一班*/
#pragma once
#pragma comment(lib, "Winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#include"cmd_console_tools.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<Windows.h>
#include<fstream>
#include<io.h>
#include<conio.h>
#include<iomanip>
#include<time.h>
#include <experimental/filesystem>
#include<strstream>
#include<string.h>
using namespace std;
#define INI_DOCUMENT "CLOCK.ini"
#define OK              1
#define INPUT_ERROR    -1
#define THE_FILE_IS_MISSING -1
#define HAVE_FOUND_THE_FILE 1
#define END -999
const char fname[] = INI_DOCUMENT;
const char number[10][3] = { "０","１","２","３","４","５","６","７","８","９" };
enum ITEM_TYPE { TYPE_INT, TYPE_DOUBLE, TYPE_STRING, TYPE_CHARACTER, TYPE_NULL };
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
const char name[][15] = { "切换","时区","提醒（暂无）","闹钟","设置","说明" };
const char name1[4][3][11] = { "切换时区","显示时区","开闭显示","增加提醒","删除提醒","显示提醒" ,"增加闹钟","删除闹钟","显示闹钟" ,"颜色","语言","时间" };
struct TIME{
	double hour;
	double minute;
	double second;
	double day;
	double month;
	double year;
};
struct ALARM {
	TIME time_alarm;
	int id;
	int repeat;
	int day[7];
};
struct TIMEZONE {
	int id;
	int timezone;
	char name[30];
};
struct BASIC {
	char CHINESE[7], file_music[9];
	int localtime, num_clock, backcolor, frontcolor, num_alarm, num_infor;
};

//*************************************
int group_search(fstream &fp, const char *group_name);
int group_add(fstream &fp, const char *group_name);
int group_show(fstream &fp);
int group_del(fstream &fp, const char *group_name);
int group_save_temp(fstream &fp, char **save);
int item_search(fstream &fp, const char *group_name, const char *item_name);
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_del(fstream &fp, const char *group_name, const char *item_name);
int item_update(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
int item_get_value(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type);
//**************************************


void circle(double x, double y, double length, TIME time, int color_b, int color_f);
int output_CHINESE(const char *target_infile, const char *target_word, int x, int y, int back_c, int char_c);
int origin_tishi(const char *FILE_NAME, int x, int y);
int origin_create();
int find_document(const char *name);
int origin_setbasic_data();
void get_time(TIME *time0, int num);
void judge_input(int *set, int *xuanxiang, int *mode);
void show_menu(int *xuanxiang, int num, int *xuanxiang_next, char *file_name, int back_c, int char_c);
void shuzi(int x, int y, TIME time0, int color_b, int color_f);
void exchange_mode(const int setmode, int *MODE, int *NEXT, int *next_mode, int *timezone_num, int *if_show);
int output_CHINESE_BI(const char *target_infile, const char *target_word, int x, int y, int back_c, int char_c);
void riqi(int x, int y, TIME time0, int color_b, int color_f);
int get_from_document(BASIC *basic);
int clock_main();
int show_add_alarm_menu();
int alarm_menu(int num);
int show_line(int x, int y, int length, int han, int bc, int fc);
int update_document_main(BASIC *basic);
int add_alarm(ALARM temp);
void shuzi_sm(int x, int y, TIME time0, int color_b, int color_f);
int show_all_alarm_menu();
int show_del_alarm_menu();
int judge_alarm(TIME now, int *music);
int reng(int x);
int zeller(int year, int month, int day);
int time_zone_update(int num);
int timezone_menu(int num, int *main_time_zone, int *if_show);
int time_zone_name_update(int num, char *time_name);
int show_all_time_menu();
int setup(int *next_mode);
void show_detail();
//void show_document();
//int set_alarm(const int set_mode);




