/*1650254 ��Ң�� �����һ��*/
#include"90-b3.h"
int get_from_document(BASIC *basic)
{
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	const char GROUP[] = "MAINOPTION";
	item_get_value(infile, GROUP, "CHINESE", &basic->CHINESE, TYPE_STRING);
	item_get_value(infile, GROUP, "LOCALTIME", &basic->localtime, TYPE_INT);
	item_get_value(infile, GROUP, "NUM_CLOCK", &basic->num_clock, TYPE_INT);
	item_get_value(infile, GROUP, "BACKCOLOR", &basic->backcolor, TYPE_INT);
	item_get_value(infile, GROUP, "FRONTCOLOR", &basic->frontcolor, TYPE_INT);
	item_get_value(infile, GROUP, "NUM_ALARM", &basic->num_alarm, TYPE_INT);
	item_get_value(infile, GROUP, "FILE_MUSIC", &basic->file_music, TYPE_STRING);
	item_update(infile, GROUP, "NUM_INFOR", &basic->num_infor, TYPE_INT);
	infile.close();
	return 0;
}
int update_document_main(BASIC *basic)
{
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	const char GROUP[] = "MAINOPTION";
	item_update(infile, GROUP, "CHINESE", &basic->CHINESE, TYPE_STRING);
	item_update(infile, GROUP, "LOCALTIME", &basic->localtime, TYPE_INT);
	item_update(infile, GROUP, "NUM_CLOCK", &basic->num_clock, TYPE_INT);
	item_update(infile, GROUP, "BACKCOLOR", &basic->backcolor, TYPE_INT);
	item_update(infile, GROUP, "FRONTCOLOR", &basic->frontcolor, TYPE_INT);
	item_update(infile, GROUP, "NUM_ALARM", &basic->num_alarm, TYPE_INT);
	item_update(infile, GROUP, "FILE_MUSIC", &basic->file_music, TYPE_STRING);
	item_update(infile, GROUP, "NUM_INFOR", &basic->num_infor, TYPE_INT);
	infile.close();
	return 0;
}
int time_zone_change(int *main_time_zone)
{
	BASIC basic;
	get_from_document(&basic);
	if (*main_time_zone == basic.num_clock)
		*main_time_zone = 1;
	else
		(*main_time_zone)++;
	return 0;
}
int timezone_menu(int num, int *main_time_zone, int *if_show)
{

	if (num == 0)
	{
		system("cls");
		time_zone_change(main_time_zone);
	}
	if (num == 1)
		show_all_time_menu();
	if (num == 2)
	{
		system("cls");
		*if_show *= -1;
	}
	return 0;
}
int time_zone_update(int num)
{
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	char GROUP[20] = "TIMECLOCK0";
	GROUP[9] += num;
	int temp;
	item_get_value(infile, GROUP, "timezone", &temp, TYPE_INT);
	return temp;
}
int time_zone_name_update(int num, char *time_name)
{
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	char GROUP[20] = "TIMECLOCK0";
	GROUP[9] += num;
	item_get_value(infile, GROUP, "timearea", time_name, TYPE_STRING);
	return 0;
}
int read_TIMEZONE(TIMEZONE *temp)
{
	int target = 0;
	fstream infile;
	infile.open(INI_DOCUMENT, ios::in | ios::out | ios::binary);
	if (!infile.is_open())
		return END;
	char GROUP[20] = "TIMECLOCK0";
	int i = 1;
	for (i = 1; i <= 9; i++)
	{
		GROUP[9] = '0' + i;
		infile.seekp(0, ios::beg);
		if (group_search(infile, GROUP) != END)
		{
			item_get_value(infile, GROUP, "ID", &((temp + target)->id), TYPE_INT);
			item_get_value(infile, GROUP, "timeznoe", &((temp + target)->timezone), TYPE_INT);
			item_get_value(infile, GROUP, "timearea", ((temp + target)->name), TYPE_STRING);
			target++;
		}
	}
	infile.close();
	return 0;
}
int show_all_time_menu()
{
	system("cls");
	BASIC basic;
	get_from_document(&basic);
	int xuanxiang = 1;
	int num = 0;
	show_menu(&xuanxiang, num, &num, basic.CHINESE, basic.backcolor, basic.frontcolor);
	TIMEZONE *head;
	head = new(nothrow)TIMEZONE[basic.num_clock];
	read_TIMEZONE(head);
	for (int i = 0; i < basic.num_clock; i++)
		output_CHINESE(basic.CHINESE, head[i].name, 100, 10 + i * 16, basic.backcolor, basic.frontcolor);
	output_CHINESE(basic.CHINESE, "��������˻�", 20, 150, basic.backcolor, basic.frontcolor);
	_getch();
	system("cls");
	return 0;
}
int setup(int *next_mode)
{
	system("cls");
	if (*next_mode == 0)
	{
		int b_color;
		int f_color;
		gotoxy(hout, 0, 0);
		setcolor(hout, COLOR_HBLACK, COLOR_WHITE);
		system("cls");
		setfontsize(hout, L"��������", 15);
		cout << "0	//��" << endl;
		cout << "1	//��" << endl;
		cout << "2	//��" << endl;
		cout << "3	//��" << endl;
		cout << "4	//��" << endl;
		cout << "5	//��" << endl;
		cout << "6	//��" << endl;
		cout << "7	//��" << endl;
		cout << "8	//����" << endl;
		cout << "9	//����" << endl;
		cout << "10	//����" << endl;
		cout << "11	//����" << endl;
		cout << "12	//����" << endl;
		cout << "13	//����" << endl;
		cout << "14	//����" << endl;
		cout << "15	//����" << endl;
		cout << "�����뱳����ɫ���룡" << endl;
		cin >> b_color;
		cout << "������ǰ����ɫ���룡" << endl;
		cin >> f_color;
		BASIC basic;
		get_from_document(&basic);
		basic.backcolor = b_color;
		basic.frontcolor = f_color;
		update_document_main(&basic);
		setcolor(hout, basic.backcolor, basic.frontcolor);
		system("cls");
		setfontsize(hout, L"��������", 1);
		//time_zone_change(main_time_zone);
		//;
	}
	if (*next_mode == 1)
	{
		BASIC basic;
		get_from_document(&basic);
		if (strcmp(basic.CHINESE, "HZK16") == 0)
			strcpy(basic.CHINESE, "HZK16F");
		else
			strcpy(basic.CHINESE, "HZK16");
		update_document_main(&basic);
	}
	if (*next_mode == 2)
	{
		gotoxy(hout, 0, 0);
		setcolor(hout, COLOR_HBLACK, COLOR_WHITE);
		system("cls");
		setfontsize(hout, L"��������", 15);
		cout << "�������̨�豸Ŀǰʱ������У׼��" << endl;
		cout << "����������8������������-8" << endl;
		int local;
		cin >> local; 
		BASIC basic;
		get_from_document(&basic);
		basic.localtime = local;
		update_document_main(&basic);
		setcolor(hout, basic.backcolor, basic.frontcolor);
		system("cls");
		setfontsize(hout, L"��������", 1);
	}
	return 0;
}
void show_detail()
{
	gotoxy(hout, 0, 0);
	setcolor(hout, COLOR_HBLACK, COLOR_WHITE);
	system("cls");
	setfontsize(hout, L"��������", 15);
	cout << "��ϵͳһ�����ýԴ�����clock.ini�У��û����������޸ģ�" << endl;
	cout << "��ϵͳ��������������д��ҵ�����Ӻ�ʱ����֧��9��" << endl;
	cout << "���ӿ�ֱ���ڳ��������ӣ�ʱ����Ҫ�û������������ļ��а���ʽ��ӣ�" << endl;
	cout << "���ѹ�����δ���ߣ�ԭ��������������д��ҵ��" << endl;
	system("pause");
	BASIC basic;
	get_from_document(&basic);
	setcolor(hout, basic.backcolor, basic.frontcolor);
	system("cls");
	setfontsize(hout, L"��������", 1);
}
//**************************************
//int group_search(fstream &fp, const char *group_name)
//����:�ӵ�ǰָ��֮��Ѱ��ĳһ�ض���[group_name]
//���group_nameΪ"\0\0"
//�򷵻ص�һ��������[�ĵ�ַ
//������ʹ�ú�clear����һ�·�ֹ�����ƶ�
//**************************************
int group_search(fstream &fp, const char *group_name)
{
	int flag1 = 1;
	int temp_P, temp_G;
	while (!fp.eof())
	{
		char c;
		fp.read((char *)&c, sizeof(c));
		if ((c == '\n' || c == '\t' || c == ' ' || c == '\r') && flag1 == 0)
		{
			fp.read((char *)&c, sizeof(c));
			if (c == '[')
				flag1 = 1;
			fp.seekp(-1, ios::cur);
			continue;
		}
		else if (c == '['&&flag1 == 1)
		{
			flag1 = 2;
			temp_P = (int)fp.tellp();
			continue;
		}
		else if (c == ']'&&flag1 == 2)
		{
			temp_G = (int)fp.tellp();
			fp.seekp(temp_P, ios::beg);
			flag1 = 3;
			continue;
		}
		else if (flag1 == 3)
		{
			int i = 0, flag = 0;
			if (group_name[i] == '\0')
			{
				fp.clear();
				return temp_P - 1;
			}
			while (1)
			{
				if (c == ']')
				{
					if (group_name[i] == '\0')
						break;
					else
					{
						flag = 1;
						break;
					}

				}
				if (group_name[i] == '\0'&&c != ']')
				{
					flag = 1;
					break;
				}
				if (c != group_name[i])
				{
					flag = 1;
					break;
				}
				i++;
				fp.read((char *)&c, sizeof(c));
			}
			if (flag == 1)
			{
				fp.seekp(temp_G, ios::beg);
				flag1 = 0;
			}
			else
			{
				fp.clear();
				return temp_G;
			}
		}
		else if (flag1 == 2)
		{
			if (c == '\n' || c == '\t' || c == ' ' || c == '\r')
				flag1 = 0;
			else
				flag1 = 2;
		}
		else
			flag1 = 0;

	}
	fp.clear();
	return END;
}

//**************************************
//int group_add(fstream &fp, const char *group_name)
//����:����ض���[group_name]
//**************************************
int group_add(fstream &fp, const char *group_name)
{
	fp.seekp(0, ios::beg);
	if (group_search(fp, group_name) != END)
		return 1;
	fp.seekp(0, ios::end);
	char temp_a[] = "\r\n[";
	char temp_b[] = "]\r\n";
	fp.write(temp_a, strlen(temp_a));
	fp.write(group_name, strlen(group_name));
	fp.write(temp_b, strlen(temp_b));
	fp.clear();
	return OK;
}

//**************************************
//int group_add(fstream &fp, const char *group_name)
//����:��ӡ�ļ�ȫ������
//**************************************
int group_show(fstream &fp)
{
	fp.seekp(0, ios::beg);
	while (!fp.eof())
	{
		cout << (char)fp.get();
	}
	fp.clear();
	return OK;
}

//**************************************
//int group_save_temp(fstream &fp,char *save)
//����:�Ӹô�ָ����ݴ��ļ�֮��ȫ������
//**************************************
int group_save_temp(fstream &fp, char **save)
{
	int start = (int)fp.tellp();
	fp.seekp(0, ios::end);
	int end = (int)fp.tellp();
	int length = (int)end - start + 1;
	*save = new(nothrow)char[length];
	if (*save == NULL)
		return END;
	int i = 0;
	fp.seekp(start, ios::beg);
	while (!fp.eof())
	{
		fp.read((char *)&(*save)[i], sizeof((*save)[i]));
		i++;
	}
	(*save)[length - 1] = '\0';
	fp.clear();
	fp.seekp(start, ios::beg);
	return OK;
}

//**************************************
//int group_del(fstream &fp,const char *group_name)
//����:ɾ���ض���[group_name]������Ԫ��
//
//**************************************
int group_del(fstream &fp, const char *group_name)
{
	fp.seekp(0, ios::beg);
	int target = group_search(fp, group_name);
	if (target == END)
		return 0;
	fp.seekp(target, ios::beg);
	int tar = group_search(fp, "\0");
	if (tar != END)
	{
		char *ch;
		fp.seekp(tar, ios::beg);
		group_save_temp(fp, &ch);
		target = target - 2 - strlen(group_name);
		int i = 0;
		fp.seekp(target, ios::beg);
		while (ch[i] != '\0')
		{
			fp.write((char *)&ch[i], 1);
			i++;
		}
		experimental::filesystem::resize_file(fname, ((int)fp.tellp()) - 1);
		delete ch;
	}
	else
	{
		target = target - 2 - strlen(group_name);
		fp.seekp(target, ios::beg);
		experimental::filesystem::resize_file(fname, ((int)fp.tellp()) - 1);
	}
	return OK;
}


//*********************item_part**********************

//**************************************
//int item_search(fstream &fp, const char *group_name, const char *item_name)
//����:Ѱ���ض���[group_name]��[item_name]��
//**************************************
int item_search(fstream &fp, const char *group_name, const char *item_name)
{
	fp.seekp(0, ios::beg);
	int target = group_search(fp, group_name);
	if (target == END)
		return END;
	fp.seekp(target, ios::beg);
	int tar = group_search(fp, "\0");
	fp.seekp(target + 2, ios::beg);
	char temp[128];
	int n = (int)fp.tellp();
	while (!fp.eof())
	{
		int flag = 0;
		fp.getline(temp, 128, '=');
		fp.ignore(1024, '\n');
		if (strcmp(temp, item_name) != 0)
			flag = 0;
		else
			flag = 1;

		if (flag == 1)
			return n;
		n = (int)fp.tellp();

		if (tar != END&&n >= tar)
			break;
	}
	fp.clear();
	return END;
}

//**************************************
//int item_add(fstream &fp, const char *group_name, const char *item_name��const void *item_value,const enum ITEM_TYPE item_type)
//����:�����ض���[group_name]��[item_name]��
//**************************************
int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	fp.seekp(0, ios::beg);
	int target = group_search(fp, group_name);
	if (target == END)
		return 1;
	int tar = item_search(fp, group_name, item_name);
	if (tar != END)
		return 1;
	fp.seekp(target, ios::beg);
	int c = group_search(fp, "\0");
	char *ch;
	fp.clear();
	if (c == END)
	{
		fp.seekp(0, ios::end);
		while (1)
		{
			fp.seekp(-1, ios::cur);
			char ch = fp.get();
			fp.seekp(-1, ios::cur);
			if (ch != '\n'&&ch != '\r'&&ch != ' '&&ch != '\t')
				break;
		}
		fp.seekp(3, ios::cur);
		int k = (int)fp.tellp();
		group_save_temp(fp, &ch);
		fp.seekp(k, ios::beg);
		fp.write(item_name, strlen(item_name));
		fp << "=";
		if (item_type == TYPE_INT)
			fp << *((int *)item_value);
		else if (item_type == TYPE_DOUBLE)
			fp << *((double *)item_value);
		else if (item_type == TYPE_STRING)
			fp << (char *)item_value;
		else if (item_type == TYPE_CHARACTER)
			fp << *((char *)item_value);
		else if (item_type == TYPE_NULL)
			fp << '\0';
		fp << '\r' << '\n';
	}
	else
	{
		fp.seekp(c, ios::beg);
		while (1)
		{
			fp.seekp(-1, ios::cur);
			char ch = fp.get();
			fp.seekp(-1, ios::cur);
			if (ch != '\n'&&ch != '\r'&&ch != ' '&&ch != '\t')
				break;
		}
		fp.seekp(3, ios::cur);
		int k = (int)fp.tellp();
		group_save_temp(fp, &ch);
		fp.seekp(k, ios::beg);
		fp.write(item_name, strlen(item_name));
		fp << '=';
		if (item_type == TYPE_INT)
			fp << *((int *)item_value);
		else if (item_type == TYPE_DOUBLE)
			fp << *((double *)item_value);
		else if (item_type == TYPE_STRING)
			fp << (char *)item_value;
		else if (item_type == TYPE_CHARACTER)
			fp << *((char *)item_value);
		else if (item_type == TYPE_NULL)
			fp << '\0';
		fp << '\r' << '\n';
		int i = 0;
		while (ch[i] != '\0')
		{
			fp.write((char *)&ch[i], 1);
			i++;
		}
		fp.clear();
		int end_ = (int)fp.tellp();
		experimental::filesystem::resize_file(fname, end_);
		delete ch;
	}
	fp.clear();
	return OK;
}

//**************************************
//int item_del(fstream &fp, const char *group_name, const char *item_name)
//����:ɾ���ض���[group_name]��[item_name]��
//**************************************
int item_del(fstream &fp, const char *group_name, const char *item_name)
{
	fp.seekp(0, ios::beg);
	int target = group_search(fp, group_name);
	if (target == END)
		return 1;
	int tar = item_search(fp, group_name, item_name);

	if (tar == END)
		return 1;
	fp.seekp(tar, ios::beg);
	char c;
	while (1)
	{
		c = fp.get();
		if (fp.eof())
			break;
		if (c == '\n' || c == '\t' || c == '\r')
			break;
	}
	fp.seekp(-1, ios::cur);
	cin.clear();
	char *ch;
	group_save_temp(fp, &ch);
	fp.seekp(tar, ios::beg);
	experimental::filesystem::resize_file(fname, ((int)fp.tellp()) - 1);
	int i = 0;
	fp.seekp(0, ios::end);
	while (ch[i] != '\0')
	{
		fp.write((char *)&ch[i], 1);
		i++;
	}
	experimental::filesystem::resize_file(fname, ((int)fp.tellp()) - 1);
	delete ch;
	fp.clear();
	return OK;
}

//**************************************
//int item_update(fstream &fp, const char *group_name, const char *item_name��const void *item_value,const enum ITEM_TYPE item_type)
//����:�����ض���[group_name]��[item_name]��
//**************************************
int item_update(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	fp.seekp(0, ios::beg);
	int target = group_search(fp, group_name);
	if (target == END)
		return 0;
	int tar = item_search(fp, group_name, item_name);
	if (tar == END)
		return 0;
	fp.seekp(tar + strlen(item_name) + 1, ios::beg);
	while (fp.get() != '\n')
		;
	char *ch;
	group_save_temp(fp, &ch);
	fp.seekp(tar + strlen(item_name) + 1, ios::beg);
	if (item_type == TYPE_INT)
		fp << *((int *)item_value);
	else if (item_type == TYPE_DOUBLE)
		fp << *((double *)item_value);
	else if (item_type == TYPE_STRING)
		fp << (char *)item_value;
	else if (item_type == TYPE_CHARACTER)
		fp << *((char *)item_value);
	else if (item_type == TYPE_NULL)
		fp << '\0';
	fp << '\r' << '\n';

	int i = 0;
	while (ch[i] != '\0')
	{
		fp.write((char *)&ch[i], 1);
		i++;
	}
	fp.clear();
	int end_ = (int)fp.tellp();
	experimental::filesystem::resize_file(fname, end_);
	delete ch;
	return OK;
}


//**************************************
//int item_get_value(fstream &fp, const char *group_name, const char *item_name��const void *item_value,const enum ITEM_TYPE item_type)
//����:��ȡ�ض���[group_name]��[item_name]��
//**************************************
int item_get_value(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	fp.seekp(0, ios::beg);
	int target = group_search(fp, group_name);
	if (target == END)
		return 0;
	int tar = item_search(fp, group_name, item_name);
	if (tar == END)
		return 0;
	fp.seekp(tar + strlen(item_name) + 1, ios::beg);
	if (item_type == TYPE_INT)
		fp >> (*(int*)item_value);
	else if (item_type == TYPE_DOUBLE)
		fp >> *((double *)item_value);
	else if (item_type == TYPE_STRING)
		fp >> (char *)item_value;
	else if (item_type == TYPE_CHARACTER)
		fp >> *((char *)item_value);
	else if (item_type == TYPE_NULL)
		;
	else
		;
	return OK;
}

