/*1650254 ��Ң�� �����1��*/
#include"90-b1.h"
void cout_orgin(int p, int a[][MAX_COLUMN], int *row, int *column, int book[][MAX_COLUMN])
{
	random_ball_origin(p, a, row, column);
	cout << "��ʼ����Ϊ��" << endl;
	if (p < 6)
		print_array(*row, *column, a, book);
}
//��ӡ����
void print_array(int i_end, int j_end, int a[][MAX_COLUMN], int book[][MAX_COLUMN])
{
	cout << "\n     ";
	for (int i = 0; i < j_end; i++)
		cout << i + 1 << "  ";
	cout << endl << "---";
	for (int i = 0; i < j_end; i++)
		cout << "---";
	cout << endl;
	for (int i = 0; i < i_end; i++)
	{
		cout << (char)(65 + i) << " " << "|  ";
		for (int j = 0; j < j_end; j++)
		{
			setcolor(hout, 0, 7);
			if (book[i][j] != 0 || a[i][j] == 0)
				setcolor(hout, 14, 7);
			cout << a[i][j];
			setcolor(hout, 0, 7);
			cout << "  ";
		}
		cout << endl;
	}
}
void mode1(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	output("\n\n���س�������Ѱ�ҳ�ʼ��������Ĳ���...");
	if (all_judge(*row, *column, a, record))
		print_array(*row, *column, a, record);
	else
		cout << "û�п�����������\n";
	end(-1, -1);
}
void mode2(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	output("\n\n���س�������Ѱ�ҳ�ʼ��������Ĳ���...");
	if ((!all_judge(*row, *column, a, record)) && p == 2)
	{
		cout << "\n\nû�п�����������,��С���޷����ԣ����˳�������\n";
		return;
	}
	while (all_judge(*row, *column, a, record))
	{
		print_array(*row, *column, a, record);
		output("\n\n���س����������������0����..\n");
		cout << "�����0�������(��ͬɫ��ʶ)��";
		delete_ball(*row, *column, a, record);
		down_ball(*row, *column, a);
		reset(record);
		print_array(*row, *column, a, record);
		set_sign(record, a);
		output("\n\n���س���������ֵ���...\n");
		cout << "��ֵ���������(��ͬɫ��ʶ)��";
		random_ball_origin(-1, a, row, column);
		print_array(*row, *column, a, record);
		reset(record);
		if (!all_judge(*row, *column, a, record))
			break;
		output("\n\n���س�������Ѱ�ҳ�ʼ��������Ĳ���...");
	}
	cout << "\n\n��ʼ���޿�����������\n";
}
void mode3(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	mode2(p, a, row, column);
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int moveable[MAX_ROW][MAX_COLUMN] = { 0 };
	if (!autojudge(*row, *column, a, record, moveable))
	{
		cout << "û�п����������\n";
		end(-1, -1);
		return;
	}
	else
	{
		cout << "\n\n��ѡ���������ʾ����ͬɫ��ʶ����\n";
		print_array(*row, *column, a, moveable);
		cout << "��С�������";
		end(-1, -1);
	}
}
void mode9(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	system("cls");
	setconsoleborder(hout, 100, 100);
	cout << "������ѧ��(���� 1651234 ��Ӧ��� test\\1651234.dat �ļ�)" << endl;
	char name[20] = "test\\1651234";
	cin >> (name + 5);
	name[strlen(name)] = '.';
	name[strlen(name)] = 'd';
	name[strlen(name)] = 'a';
	name[strlen(name)] = 't';
	name[strlen(name)] = '\0';
	ifstream fin;
	fin.open(name, ios::in);
	if (!fin.is_open())
	{
		cout << "��" << name << "�ļ�ʧ��" << endl;
		end(-1, -1);
		return;
	}
	fin >> *row >> *column;
	for (int i = 0; i < *row; i++)
		for (int j = 0; j < *column; j++)
			fin >> a[i][j];
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int moveable[MAX_ROW][MAX_COLUMN] = { 0 };
	cout << "\n\n��ʼ����Ϊ��";
	print_array(*row, *column, a, record);
	autojudge(*row, *column, a, record, moveable);
	cout << "\n\n��ѡ���������ʾ����ͬɫ��ʶ����\n";
	print_array(*row, *column, a, moveable);
	name[strlen(name)-3] = 'a';
	name[strlen(name)-2] = 'n';
	name[strlen(name)-1] = 's';
	fin.close();
	fin.open(name, ios::in);
	if (!fin.is_open())
	{
		cout << "��" << name << "�ļ�ʧ��" << endl;
		end(-1, -1);
		return;
	}
	int b[MAX_ROW][MAX_COLUMN];
	for (int i = 0; i < *row; i++)
		for (int j = 0; j < *column; j++)
			fin >> b[i][j];
	fin.close();
	cout << "\n\n���ļ�������\n";
	cout << "\n     ";
	for (int i = 0; i < *column; i++)
		cout << i + 1 << "  ";
	cout << endl << "---";
	for (int i = 0; i < *column; i++)
		cout << "---";
	cout << endl;
	for (int i = 0; i < *row; i++)
	{
		cout << (char)(65 + i) << " " << "|  ";
		for (int j = 0; j < *column; j++)
		{
			setcolor(hout, 0, 7);
			if (b[i][j] > 90)
			{
				setcolor(hout, 14, 7);
				b[i][j] -= 90;
			}
			cout << b[i][j];
			setcolor(hout, 0, 7);
			cout << "  ";
		}
		cout << endl;
	}
	end(-1, -1);
}