/*1650254 尤尧寅 计算机一班*/
#include"90-b3.h"
int output_CHINESE(const char *target_infile, const char *target_word, int x, int y, int back_c, int char_c)
{
	FILE* infile = NULL;
	int i, j, k;
	int flag;
	unsigned char buffer[32];
	unsigned char key[8] = {
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
	};

	infile = fopen(target_infile, "rb");
	if (infile == NULL)
	{
		return -1;
	}
	int m = 0;
	while (1)
	{
		if (target_word[m] == '\0')
			break;
		signed int offset = (94 * ((unsigned char)target_word[m] - 0xa0 - 1) + ((unsigned char)target_word[m + 1] - 0xa0 - 1)) * 32;
		fseek(infile, offset, SEEK_SET);
		fread(buffer, 1, 32, infile);

		for (k = 0; k < 16; k++) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					gotoxy(hout, x + m * 16 + (j * 8 + i) * 2, y + k);
					if (flag)
					{
						setcolor(hout, back_c, char_c);
						cout << "●";
					}
					else
					{
						setcolor(hout, back_c, back_c);
						cout << " ";
					}
				}
			}
		}
		m = m + 2;
	}
	fclose(infile);
	infile = NULL;
	return 0;
}

int output_CHINESE_BI(const char *target_infile, const char *target_word, int x, int y, int back_c, int char_c)
{
	FILE* infile = NULL;
	int i, j, k;
	int flag;
	unsigned char buffer[32];
	unsigned char key[8] = {
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
	};

	infile = fopen(target_infile, "rb");
	if (infile == NULL)
	{
		return -1;
	}
	int m = 0;
	while (1)
	{
		if (target_word[m] == '\0')
			break;
		signed int offset = (94 * ((unsigned char)target_word[m] - 0xa0 - 1) + ((unsigned char)target_word[m + 1] - 0xa0 - 1)) * 32;
		fseek(infile, offset, SEEK_SET);
		fread(buffer, 1, 32, infile);

		for (k = 0; k < 16; k++) {
			for (j = 0; j < 2; j++) {
				for (i = 0; i < 8; i++) {
					flag = buffer[k * 2 + j] & key[i];
					gotoxy(hout, x + m * 16 + (j * 8 + i) * 4, y + k * 2);
					if (flag)
					{
						setcolor(hout, back_c, char_c);
						cout << "●●";
						gotoxy(hout, x + m * 16 + (j * 8 + i) * 4, y + k * 2 + 1);
						cout << "●●";
					}
					else
					{
						setcolor(hout, back_c, back_c);
						cout << "    ";
						gotoxy(hout, x + m * 16 + (j * 8 + i) * 4, y + k * 2 + 1);
						cout << "    ";
					}
				}
			}
		}
		m = m + 2;
	}
	fclose(infile);
	infile = NULL;
	return 0;
}

int find_document(const char *name)
{
	long file;
	struct _finddata_t find;
	if ((file = _findfirst(name, &find)) == -1L)
	{
		_findclose(file);
		return 0;
	}
	else
	{
		_findclose(file);
		return 1;
	}
}

int origin_tishi(const char *FILE_NAME, int x, int y)
{
	setconsoleborder(hout, 720, 450 / 2);
	setcursor(hout, CURSOR_INVISIBLE);
	setcolor(hout, COLOR_WHITE, COLOR_BLACK);
	system("cls");
	setcolor(hout, COLOR_BLACK, COLOR_BLACK);
	output_CHINESE(FILE_NAME, "　欢迎使用", x, y, COLOR_WHITE, COLOR_BLACK);
	output_CHINESE(FILE_NAME, "ＡＰＴＸＯＮ", x, y + 16, COLOR_WHITE, COLOR_BLACK);
	output_CHINESE(FILE_NAME, "　闹钟系统", x, y + 2 * 16, COLOR_WHITE, COLOR_BLACK);
	output_CHINESE(FILE_NAME, "正在进入系统", x, y + 4 * 16, COLOR_WHITE, COLOR_BLACK);
	output_CHINESE(FILE_NAME, "○○○○○○", x, y + 3 * 16, COLOR_WHITE, COLOR_BLACK);
	Sleep(1000);
	while (1)
	{
		static int i = 0;
		if (i == 6)
			break;
		Sleep(10);
		output_CHINESE(FILE_NAME, "●", x + i * 16 * 2, y + 3 * 16, COLOR_WHITE, COLOR_BLACK);
		i++;
	}
	Sleep(1000);
	system("cls");
	if (!find_document(INI_DOCUMENT))
	{
		output_CHINESE(FILE_NAME, "未找到配置文件", x, y + 1 * 16, COLOR_WHITE, COLOR_BLACK);
		output_CHINESE(FILE_NAME, "　新建文件中", x, y + 2 * 16, COLOR_WHITE, COLOR_BLACK);
		output_CHINESE(FILE_NAME, "○○○○○○○", x, y + 3 * 16, COLOR_WHITE, COLOR_BLACK);
		Sleep(1000);
		while (1)
		{
			static int i = 0;
			if (i == 7)
				break;
			Sleep(10);
			output_CHINESE(FILE_NAME, "●", x + i * 16 * 2, y + 3 * 16, COLOR_WHITE, COLOR_BLACK);
			i++;
		}
		if (origin_create() == END)
		{
			output_CHINESE(FILE_NAME, "创建文件失败！", x, y + 4 * 16, COLOR_WHITE, COLOR_BLACK);
			return END;
		}
		else
		{
			output_CHINESE(FILE_NAME, "创建文件成功！", x, y + 4 * 16, COLOR_WHITE, COLOR_BLACK);
		}
	}
	else
	{
		output_CHINESE(FILE_NAME, "找到配置文件！", x, y + 2 * 16, COLOR_WHITE, COLOR_BLACK);
		output_CHINESE(FILE_NAME, "○○○○○○○", x, y + 3 * 16, COLOR_WHITE, COLOR_BLACK);
		Sleep(1000);
		while (1)
		{
			static int i = 0;
			if (i == 7)
				break;
			Sleep(10);
			output_CHINESE(FILE_NAME, "●", x + i * 16 * 2, y + 3 * 16, COLOR_WHITE, COLOR_BLACK);
			i++;
		}
	}
	return OK;
}

int origin_create()
{
	ofstream infile;
	infile.open(INI_DOCUMENT, ios::out | ios::binary);
	char origin[] = "[MAINOPTION]\r\nCHINESE=HZK16\r\nLOCALTIME=8\r\nNUM_CLOCK=2\r\nBACKCOLOR=7\r\nFRONTCOLOR=0\r\nNUM_ALARM=0\r\nFILE_MUSIC=demo.wav\r\nNUM_INFOR=0\r\n[TIMECLOCK1]\r\ntimezone=8\r\ntimearea=上海\r\n";
	infile.write(origin, sizeof(origin));
	infile.close();
	if (!find_document(INI_DOCUMENT))
		return END;
	return OK;
}

int origin_setbasic_data()
{
	system("cls");
	setfontsize(hout, L"点阵字体", 20);
	cout << "请切换新版控制台使用此系统！" << endl;
	if (!find_document("HZK16"))
	{
		cout << "未找到简体点阵字库" << endl;
		system("pause");
		return END;
	}
	else
		cout << "确认找到简体点阵字库" << endl;
	if (!find_document("HZK16F"))
	{
		cout << "未找到繁体点阵字库" << endl;
		system("pause");
		return END;
	}
	else
		cout << "确认找到繁体点阵字库" << endl;
	cout << "请使用方向键操作本程序！" << endl;
	cout << "系统默认为简体汉字表示,如需修改请在设置->语言中修改" << endl;
	cout << "系统localtime为东八区换算后得来，如与实际有错请在设置->时间中修改" << endl;
	cout << "系统默认时区为上海（东八）和格林威治时间,如需修改请在时区中修改" << endl;
	cout << "更多操作请看说明选项！" << endl;
	system("pause");
	setfontsize(hout, L"点阵字体", 1);
	return origin_tishi("HZK16", 200, 20);
}

void get_time(TIME *time0,int num)
{
	//此部分为坚坚之前作业中的函数
	struct tm *tt;	//struct tm 为系统定义的结构体
	time_t local_time = time(0)-num*60*60;
	tt = localtime(&local_time);	//localtime为系统函数

									/* tm_*** 为struct tm中的成员，和本题的struct tj_time具体的内容不完全符合，具体含义自己查找相关资料 */
	time0->year = tt->tm_year + 1900;
	time0->month = tt->tm_mon + 1;
	time0->day = tt->tm_mday;
	time0->hour = tt->tm_hour;
	time0->minute = tt->tm_min;
	time0->second = tt->tm_sec;
	return;
}

void judge_input(int *set, int *xuanxiang, int *mode)
{
	if (set[1] == 72)
	{
		if (*xuanxiang == 0)
			;
		else
			(*xuanxiang)--;
	}
	if (set[1] == 80)
	{
		if (*xuanxiang == 5)
			;
		else
			(*xuanxiang)++;
	}
	if (set[1] == 75)
	{
		if (*mode != 0)
			*mode = 0;;
	}
	return;
}

void show_menu(int *xuanxiang, int num, int *xuanxiang_next, char *file_name, int back_c, int char_c)
{
	static int ju = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i != *xuanxiang)
			output_CHINESE(file_name, name[i], 10, 10 + i * 18, back_c, char_c);
		else
			output_CHINESE(file_name, name[i], 10, 10 + i * 18, char_c, back_c);
		if (num != 0)
		{
			ju = num;
			for (int i = 0; i < 3; i++)
			{
				if (i != *xuanxiang_next)
					output_CHINESE(file_name, name1[num - 1][i], 10 + 32 * 2, 10 + i * 18 + num * 18, back_c, char_c);
				else
					output_CHINESE(file_name, name1[num - 1][i], 10 + 32 * 2, 10 + i * 18 + num * 18, char_c, back_c);
			}
		}
		else
		{
			if (ju != 0)
			{
				for (int i = 0; i < 3; i++)
					output_CHINESE(file_name, name1[ju - 1][i], 10 + 32 * 2, 10 + i * 18 + ju * 18, back_c, char_c);
				for (int i = 0; i < 10; i++)
				{
					output_CHINESE(file_name, "　　　　", 10 + 32 * 2, 10 + i * 18, back_c, back_c);

				}
				*xuanxiang_next = 0;
				ju = 0;
			}
		}
	}
}

void exchange_mode(const int setmode, int *MODE, int *NEXT, int *next_mode,int *timezone_num,int *if_show)
{
	if (setmode == 0)
	{
		*MODE = (*MODE)*-1;
		system("cls");
	}
	if (setmode == 5)
		show_detail();
	if (*NEXT == 0)
	{
		if (setmode == 1)
			*NEXT = 1;
		if (setmode == 2)
			*NEXT = 2;
		if (setmode == 3)
			*NEXT = 3;
		if (setmode == 4)
			*NEXT = 4;
	}
	else if (*NEXT != 0)
	{
		if (setmode == 1)
			timezone_menu(*next_mode,timezone_num,if_show);
		if (setmode == 2)
			1 == 1;//	timezone_menu();
		if (setmode == 3)
			alarm_menu(*next_mode);
		if (setmode == 4)
			setup(next_mode);
	}
}


//********************zeller************************
int reng(int x)
{
	if ((x % 4 == 0 && x % 100 != 0) || (x % 400 == 0))
		return 1;
	else
		return 0;
}
int zeller(int year, int month, int day)
{
	int c, y, m, d, w;
	if (month == 1 || month == 2)
	{
		c = (int)((year - 1) / 100);
		y = (int)((year - 1) % 100);
		m = month + 12;
	}
	else
	{
		c = (int)(year / 100);
		y = (int)(year % 100);
		m = month;
	}
	d = day;
	w = y + y / 4 + c / 4 - 2 * c + 13 * (m + 1) / 5 + d - 1;
	if (w < 0)
		while (w < 0)
			w = w + 7;
	w = w % 7;
	return w;
}