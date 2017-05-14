/*1650254 尤尧寅 计算机一班*/
#include"90-b3.h"
int alarm_menu(int num)
{
	if (num == 0)
		show_add_alarm_menu();
	if (num == 1)
		show_del_alarm_menu();
	if (num == 2)
		show_all_alarm_menu();
	return 0;
}

int show_line(int x, int y, int length, int han, int bc, int fc)
{
	setcolor(hout, bc, fc);
	for (int i = 0; i < han; i++)
	{
		gotoxy(hout, x, y + i);
		for (int j = 0; j < length; j++)
			cout << "*";
	}
	return 0;
}

void show_line_all(int num, int bc, int fc)
{
	int weizhi_x[12] = { 100,300,100,148,100 + 48 * 2,100 + 48 * 3 ,100 + 48 * 4 ,100 + 48 * 5 ,100 + 48 * 6,100 + 48 * 7,120,120 + 48 * 2 };
	int weizhi_y[12] = { 82,82,136,136,136,136,136,136,136,136,200,200 };
	int weizhi_length[12] = { 120,120,32,32,32,32,32,32,32,64,64,64 };
	int han = 3;
	for (int i = 0; i < 12; i++)
	{
		if (num == i)
			show_line(weizhi_x[i], weizhi_y[i], weizhi_length[i], han, bc, fc);
		else
			show_line(weizhi_x[i], weizhi_y[i], weizhi_length[i], han, bc, bc);
	}
}

void show_day(int day[8], int x, int y, int bc, int fc, char *CHINESE, int whe)
{
	char week_day[][10] = { "一","二","三","四","五","六","日","单次" ,"确认","取消" };
	for (int i = 0; i < 8; i++)
	{
		if (day[i] == -1)
			output_CHINESE(CHINESE, week_day[i], x + i * 48, y, bc, fc);
		else
			output_CHINESE(CHINESE, week_day[i], x + i * 48, y, fc, bc);
	}
	if (whe == 1)
	{
		output_CHINESE(CHINESE, week_day[8], 120, 180, bc, fc);
		output_CHINESE(CHINESE, week_day[9], 120 + 96, 180, bc, fc);
	}
}

int show_add_alarm_menu()
{
	system("cls");
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	BASIC basic;
	get_from_document(&basic);
	int xuanxiang = 3;
	int num = 0;
	int set[2] = { 0,0 };
	show_menu(&xuanxiang, num, &num, basic.CHINESE, basic.backcolor, basic.frontcolor);
	output_CHINESE(basic.CHINESE, "添加闹钟", 100, 10, basic.backcolor, basic.frontcolor);
	TIME time0 = { 0,0,0,0,0,0 };
	int day[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
	shuzi(100, 50, time0, basic.backcolor, basic.frontcolor);
	show_line_all(num, basic.backcolor, basic.frontcolor);
	show_day(day, 100, 120, basic.backcolor, basic.frontcolor, basic.CHINESE, 1);
	while (1)
	{
		if (_kbhit())
		{
			set[0] = _getch();
			if (set[0] == 224)
			{
				set[1] = _getch();
				if (set[1] == 72)
				{
					if (num == 0)
					{
						if (time0.hour == 23)
							time0.hour = 0;
						else
							time0.hour++;
					}
					if (num == 1)
					{
						if (time0.minute == 59)
							time0.minute = 0;
						else
							time0.minute++;
					}
				}
				if (set[1] == 80)
				{
					if (num == 0)
					{
						if (time0.hour == 0)
							time0.hour = 23;
						else
							time0.hour--;
					}
					if (num == 1)
					{
						if (time0.minute == 0)
							time0.minute = 59;
						else
							time0.minute--;
					}

				}
				if (set[1] == 75)
				{
					if (num == 0)
						num = num;
					else
						num--;
				}
				if (set[1] == 77)
				{
					if (num == 11)
						num = num;
					else
						num++;
				}
			}
			if (set[0] == '\r'&&num != 0 && num != 1 && num != 10 && num != 11)
			{
				day[num - 2] = -day[num - 2];
				if (num - 2 != 7)
					for (int i = 0; i < 7; i++)
						if (day[i] == 1)
							day[7] = -1;
				if (day[7] == 1)
					for (int i = 0; i < 7; i++)
						day[i] = -1;
			}
			if (set[0] == '\r'&&num == 11)
			{
				system("cls");
				break;
			}
			if (set[0] == '\r'&&num == 10)
			{
				ALARM temp;
				if (day[7] == 1)
				{
					temp.repeat = 1;
					for (int i = 0; i < 7; i++)
						temp.day[i] = -1;
				}
				else
				{
					temp.repeat = 0;
					for (int i = 0; i < 7; i++)
						temp.day[i] = day[i];
				}
				temp.time_alarm = time0;
				temp.id = basic.num_alarm + 1;
				basic.num_alarm++;
				update_document_main(&basic);
				add_alarm(temp);
				system("cls");
				break;
			}
			shuzi(100, 50, time0, basic.backcolor, basic.frontcolor);
			show_line_all(num, basic.backcolor, basic.frontcolor);
			show_day(day, 100, 120, basic.backcolor, basic.frontcolor, basic.CHINESE, 1);
		}
	}
	return 0;
}

int delete_alarm(ALARM temp)
{
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	char GROUP[16] = "ALARM";
	char num[] = "0";
	num[0] += temp.id;
	strcat(GROUP, num);
	group_del(infile, GROUP);
	infile.close();
	return 0;
}

int add_alarm(ALARM temp)
{
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	char GROUP[16] = "ALARM0";
	int i = 1;
	for (i = 1; i <= 9; i++)
	{
		GROUP[5] = '0' + i;
		if (group_search(infile, GROUP) == END)
			break;
	}
	group_add(infile, GROUP);
	item_add(infile, GROUP, "ID", &i, TYPE_INT);
	item_add(infile, GROUP, "REPAET", &temp.repeat, TYPE_INT);
	item_add(infile, GROUP, "HOUR", &temp.time_alarm.hour, TYPE_DOUBLE);
	item_add(infile, GROUP, "MINUTE", &temp.time_alarm.minute, TYPE_DOUBLE);
	char day[] = "day0";
	for (int i = 0; i < 7; i++)
	{
		day[3]++;
		item_add(infile, GROUP, day, &temp.day[i], TYPE_INT);
	}
	infile.close();
	return 0;
}

int read_alarm(ALARM *temp)
{
	int target = 0;
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	char GROUP[16] = "ALARM0";
	int i = 1;
	for (i = 1; i <= 9; i++)
	{
		GROUP[5] = '0' + i;
		infile.seekp(0, ios::beg);
		if (group_search(infile, GROUP) != END)
		{
			item_get_value(infile, GROUP, "ID", &((temp+target)->id), TYPE_INT);
			item_get_value(infile, GROUP, "REPAET", &((temp + target)->repeat), TYPE_INT);
			item_get_value(infile, GROUP, "HOUR", &((temp + target)->time_alarm.hour), TYPE_DOUBLE);
			item_get_value(infile, GROUP, "MINUTE", &((temp + target)->time_alarm.minute), TYPE_DOUBLE);
			char day[] = "day0";
			for (int j = 0; j < 7; j++)
			{
				day[3]++;
				item_get_value(infile, GROUP, day, &((temp + target)->day[j]), TYPE_INT);
			}
			target++;
		}
	}
	infile.close();
	return 0;
}

int show_alarm(ALARM temp, int x, int y, int bc, int fc, char *CHINESE)
{
	shuzi_sm(x, y, temp.time_alarm, bc, fc);
	int temp_day[8];
	for (int i = 0; i < 7; i++)
		temp_day[i] = temp.day[i];
	if (temp.repeat == 1)
		temp_day[7] = 1;
	else
		temp_day[7] = -1;
	show_day(temp_day, x, y + 16, bc, fc, CHINESE, 0);
	return 0;
}

int show_del_alarm_menu()
{
	system("cls");
	BASIC basic;
	get_from_document(&basic);
	int xuanxiang = 3;
	int num1 = 0;
	int num = 0;
	if (basic.num_alarm == 0)
	{
		show_menu(&xuanxiang, num1, &num1, basic.CHINESE, basic.backcolor, basic.frontcolor);
		output_CHINESE(basic.CHINESE, "没有闹钟", 100, 80, basic.backcolor, basic.frontcolor);
		output_CHINESE(basic.CHINESE, "按任意键退回", 100, 150, basic.backcolor, basic.frontcolor);
		_getch();
	}
	else
	{
		show_menu(&xuanxiang, num1, &num1, basic.CHINESE, basic.backcolor, basic.frontcolor);
		output_CHINESE(basic.CHINESE, "按左箭头键退回", 100, 150, basic.backcolor, basic.frontcolor);
		ALARM *head;
		head = new(nothrow)ALARM[basic.num_alarm];
		read_alarm(head);
		int set[2] = { 0,0 };
		for (int i = 0; i < basic.num_alarm; i++)
			if (i == num)
				show_alarm(head[i], 100, 10 + i * 36, basic.frontcolor, basic.backcolor, basic.CHINESE);
			else
				show_alarm(head[i], 100, 10 + i * 36, basic.backcolor, basic.frontcolor, basic.CHINESE);
		while (1)
		{
			if (_kbhit())
			{
				set[0] = _getch();
				if (set[0] == 224)
				{
					set[1] = _getch();
					if (set[1] == 72)
						if (num != 0)
							num--;
					if (set[1] == 80)
						if (num != basic.num_alarm - 1)
							num++;
					if (set[1] == 75)
						break;
				}
				if (set[0] == '\r'&&basic.num_alarm != 0)
				{
					system("cls");
					delete_alarm(head[num]);
					basic.num_alarm--;
					delete head;
					head = new(nothrow)ALARM[basic.num_alarm];
					read_alarm(head);
					update_document_main(&basic);
					show_menu(&xuanxiang, num1, &num1, basic.CHINESE, basic.backcolor, basic.frontcolor);
					output_CHINESE(basic.CHINESE, "按左箭头键退回", 100, 150, basic.backcolor, basic.frontcolor);
					num = 0;
				}
				for (int i = 0; i < basic.num_alarm; i++)
					if (i == num)
						show_alarm(head[i], 100, 10 + i * 36, basic.frontcolor, basic.backcolor, basic.CHINESE);
					else
						show_alarm(head[i], 100, 10 + i * 36, basic.backcolor, basic.frontcolor, basic.CHINESE);
				setcolor(hout, basic.backcolor, basic.frontcolor);
			}

		}
		delete head;
	}
	setcolor(hout, basic.backcolor, basic.frontcolor);
	system("cls");
	return 0;
}

int show_all_alarm_menu()
{
	system("cls");
	BASIC basic;
	get_from_document(&basic);
	int xuanxiang = 3;
	int num = 0;
	show_menu(&xuanxiang, num, &num, basic.CHINESE, basic.backcolor, basic.frontcolor);
	ALARM *head;
	head = new(nothrow)ALARM[basic.num_alarm];
	read_alarm(head);
	for (int i = 0; i < basic.num_alarm; i++)
		show_alarm(head[i], 100, 10 + i * 36, basic.backcolor, basic.frontcolor, basic.CHINESE);
	output_CHINESE(basic.CHINESE, "按任意键退回", 20, 150, basic.backcolor, basic.frontcolor);
	_getch();
	system("cls");
	return 0;
}
int ring_alarm(const char *music)
{
	PlaySound(TEXT("demo.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return 0;
}
int judge_alarm(TIME now, int *music)
{
	BASIC basic;
	get_from_document(&basic);
	ALARM *head;
	head = new(nothrow)ALARM[basic.num_alarm];
	int k = basic.num_alarm;
	int flag = 0;

	read_alarm(head);
	for (int i = 0; i < k; i++)
	{
		if (head[i].time_alarm.hour == now.hour&&head[i].time_alarm.minute == now.minute)
		{
			if (head[i].repeat == 1)
			{
				flag = 1;
				delete_alarm(head[i]);
				basic.num_alarm--;
				continue;
			}
			int week = zeller((int)now.year, (int)now.month, (int)now.day);
			if (week == 0)
				week = 6;
			else
				week--;
			if (head[i].day[week] == 1)
			{
				flag = 1;
				continue;
			}
		}
	}
	update_document_main(&basic);
	delete head;
	if (flag == 1)
	{
		*music = 1;
		ring_alarm(basic.file_music);
	}
	return 0;
}