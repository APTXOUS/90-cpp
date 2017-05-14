/*1650254 尤尧寅 计算机1班*/
#include"90-b1.h"
void cout_orgin(int p, int a[][MAX_COLUMN], int *row, int *column, int book[][MAX_COLUMN])
{
	random_ball_origin(p, a, row, column);
	cout << "初始数组为：" << endl;
	if (p < 6)
		print_array(*row, *column, a, book);
}
//打印数组
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
	output("\n\n按回车键进行寻找初始可消除项的操作...");
	if (all_judge(*row, *column, a, record))
		print_array(*row, *column, a, record);
	else
		cout << "没有可以消除的项\n";
	end(-1, -1);
}
void mode2(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	cout_orgin(p, a, row, column, record);
	output("\n\n按回车键进行寻找初始可消除项的操作...");
	if ((!all_judge(*row, *column, a, record)) && p == 2)
	{
		cout << "\n\n没有可以消除的项,本小题无法测试，请退出后重做\n";
		return;
	}
	while (all_judge(*row, *column, a, record))
	{
		print_array(*row, *column, a, record);
		output("\n\n按回车键进行数组下落除0操作..\n");
		cout << "下落除0后的数组(不同色标识)：";
		delete_ball(*row, *column, a, record);
		down_ball(*row, *column, a);
		reset(record);
		print_array(*row, *column, a, record);
		set_sign(record, a);
		output("\n\n按回车键进行新值填充...\n");
		cout << "新值填充后的数组(不同色标识)：";
		random_ball_origin(-1, a, row, column);
		print_array(*row, *column, a, record);
		reset(record);
		if (!all_judge(*row, *column, a, record))
			break;
		output("\n\n按回车键进行寻找初始可消除项的操作...");
	}
	cout << "\n\n初始已无可以消除的项\n";
}
void mode3(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	mode2(p, a, row, column);
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int moveable[MAX_ROW][MAX_COLUMN] = { 0 };
	if (!autojudge(*row, *column, a, record, moveable))
	{
		cout << "没有可以消除的项！\n";
		end(-1, -1);
		return;
	}
	else
	{
		cout << "\n\n可选择的消除提示（不同色标识）：\n";
		print_array(*row, *column, a, moveable);
		cout << "本小题结束，";
		end(-1, -1);
	}
}
void mode9(int p, int(*a)[MAX_COLUMN], int *row, int *column)
{
	system("cls");
	setconsoleborder(hout, 100, 100);
	cout << "请输入学号(输入 1651234 对应会打开 test\\1651234.dat 文件)" << endl;
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
		cout << "打开" << name << "文件失败" << endl;
		end(-1, -1);
		return;
	}
	fin >> *row >> *column;
	for (int i = 0; i < *row; i++)
		for (int j = 0; j < *column; j++)
			fin >> a[i][j];
	int record[MAX_ROW][MAX_COLUMN] = { 0 };
	int moveable[MAX_ROW][MAX_COLUMN] = { 0 };
	cout << "\n\n初始数组为：";
	print_array(*row, *column, a, record);
	autojudge(*row, *column, a, record, moveable);
	cout << "\n\n可选择的消除提示（不同色标识）：\n";
	print_array(*row, *column, a, moveable);
	name[strlen(name)-3] = 'a';
	name[strlen(name)-2] = 'n';
	name[strlen(name)-1] = 's';
	fin.close();
	fin.open(name, ios::in);
	if (!fin.is_open())
	{
		cout << "打开" << name << "文件失败" << endl;
		end(-1, -1);
		return;
	}
	int b[MAX_ROW][MAX_COLUMN];
	for (int i = 0; i < *row; i++)
		for (int j = 0; j < *column; j++)
			fin >> b[i][j];
	fin.close();
	cout << "\n\n答案文件的内容\n";
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