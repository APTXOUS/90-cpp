#include"90-b2.h"
/*1650254 尤尧寅 计算机一班*/
bool end(int x, int y)
{
	setcolor(hout, 0, 7);
	if (x != -1 && y != -1)
		gotoxy(hout, x, y);
	cout << "请输入end返回菜单:            ";
	while (1)
	{
		char ans[100];
		cin >> ans;
		if ((ans[0] == 'e' || ans[0] == 'E') && (ans[1] == 'n' || ans[1] == 'N') && (ans[2] == 'd' || ans[2] == 'D'))
			break;
		else
		{
			gotoxy(hout, x, y);
			cout << "请输入end返回菜单:                                            ";
			gotoxy(hout, x + 18, y);
		}
	}
	return 1;
}
int open_document(const char *file_name, int shudu[][MAX_COLUMN])
{
	ifstream fin;
	fin.open(file_name, ios::in);
	if (!fin.is_open())
	{
		cout << "打开" << file_name << "文件失败" << endl;
		return -1;
	}

	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			int temp;
			fin >> temp;
			if (cin.fail())
			{
				cin.ignore(1024, '\n');
				cin.clear();
				cout << "文件含有非法字符！" << endl;
			}
			else if (temp < 0 || temp >= 10)
				return -1;
			else
				shudu[i][j] = temp;
		}
	return OK;
}
void find_document(const char *name)
{
	long file;
	struct _finddata_t find;
	char *file_name;
	file_name = new(nothrow)char[strlen(name) + 4];
	if (file_name == NULL)
		return;
	for (int i = 0; i < int(strlen(name)) + 1; i++)
		file_name[i] = name[i];
	int temp = (int)strlen(file_name);
	file_name[temp++] = '*';
	file_name[temp++] = '.';
	file_name[temp++] = '*';
	file_name[temp++] = '\0';
	if ((file = _findfirst(file_name, &find)) == -1L)
	{
		cout << "空白!\n";
		return;
	}
	cout << find.name << endl;
	while (_findnext(file, &find) == 0)
		cout << find.name << endl;
	delete file_name;
	_findclose(file);
}
void infile_document(int arr[][MAX_COLUMN])
{
	system("cls");
	setconsoleborder(hout, 100, 100);
	cout << "请输入想要打开的数独文件（需要输入扩展名):" << endl;
	cout << "以下为当前目录下符合要求的文件：" << endl;
	find_document("sudoku");
	while (1)
	{
		char name[128];
		cin >> name;
		if (open_document(name, arr) != -1)
			break;
	}
}
int search1(int x, int y, const int a[][MAX_COLUMN], int color[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = 0; i < MAX_ROW; i++)
		if (a[i][y] == temp&&i != x)
		{
			for (int k = 0; k < MAX_ROW; k++)
				color[k][y] = 1;
			return 1;
		}
	return 0;
}
int search2(int x, int y, const int a[][MAX_COLUMN], int color[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = 0; i < MAX_COLUMN; i++)
		if (a[x][i] == temp&&i != y)
		{
			for (int k = 0; k < MAX_COLUMN; k++)
				color[x][k] = 1;
			return 1;
		}
	return 0;
}
int search3(int x, int y, const int a[][MAX_COLUMN], int color[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			if (a[i][j] == temp && !(i == x&&j == y))
			{
				for (int m = x / 3 * 3; m < x / 3 * 3 + 3; m++)
					for (int n = y / 3 * 3; n < y / 3 * 3 + 3; n++)
						color[m][n] = 1;
				return 1;
			}
	return 0;
}
int judge_error(int book[][MAX_COLUMN], const int a[][MAX_COLUMN], int color[][MAX_COLUMN])
{
	int flag = 0;
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			if (a[i][j] != 0)
			{
				int temp1 = search1(i, j, a, color);
				int temp2 = search2(i, j, a, color);
				int temp3 = search3(i, j, a, color);
				if (temp1 || temp2 || temp3)
				{
					book[i][j] = 1;
					flag++;
				}
			}
	return flag;
}
int reset(int a[][MAX_COLUMN])
{
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			a[i][j] = 0;
	return 0;
}
int add_list(int *count, int x, int y, int num, STEP  **head, STEP **l, STEP **q)
{
	if (*count > 0)
		*q = *l;
	*l = new(nothrow)STEP;
	if (*l == NULL)
		return -1;
	if (*count == 0)
	{
		*head = *l;
		(*l)->last = NULL;
	}
	else
	{
		(*q)->next = *l;
		(*l)->last = *q;
	}
	(*l)->x = x;
	(*l)->y = y;
	(*l)->num = num;
	(*l)->next = NULL;
	(*count)++;
	return 0;
}
int delete_list(int *count, int x, int y, int num, STEP **head, STEP **l, STEP **q)
{
	if (*l != NULL)
	{
		*q = *l;
		if (*l != *head)
		{
			((*l)->last)->next = NULL;
			*l = (*l)->last;
			delete *q;
		}
		else
		{
			delete *l;
			*head = NULL;
			*l = NULL;
		}
		if (*count > 0)
			(*count)--;
	}
	return 0;
}
int judge_zero(const int arr[][MAX_COLUMN])
{
	int flag = 0;
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			if (arr[i][j] == 0)
				flag = 1;
	return flag;
}
int input_document(const char *name, FILE_NAME **document_name)
{
	long long file;
	struct _finddata_t find;
	char *file_name;
	file_name = new(nothrow)char[strlen(name) + 4];
	if (file_name == NULL)
		return 0;
	for (int i = 0; i < int(strlen(name)) + 1; i++)
		file_name[i] = name[i];
	int temp = (int)strlen(file_name);
	file_name[temp++] = '*';
	file_name[temp++] = '.';
	file_name[temp++] = '*';
	file_name[temp++] = '\0';
	if ((file = _findfirst(file_name, &find)) == -1L)
	{
		cout << "空白!\n";
		return -1;
	}
	FILE_NAME *p = NULL, *q = NULL;
	p = new(nothrow)FILE_NAME; //思考：为什么不能用malloc
	if (p == NULL)
		return -1;
	*document_name = p;
	p->name = new(nothrow)char[strlen(find.name) + 1];
	if (p->name == NULL)
		return -1;
	int i = 0;
	while (find.name[i] != '\0')
	{
		p->name[i] = find.name[i];
		i++;
	}
	p->last = NULL;
	p->name[i] = find.name[i];
	p->next = NULL;
	while (_findnext(file, &find) == 0)
	{
		q = p;
		p = new(nothrow)FILE_NAME;
		if (p == NULL)
			return -1;
		p->name = new(nothrow)char[strlen(find.name) + 1];
		if (p->name == NULL)
			return -1;
		int j = 0;
		while (find.name[j] != '\0')
		{
			p->name[j] = find.name[j];
			j++;
		}
		q->next = p;
		p->name[j] = find.name[j];
		p->next = NULL;
		p->last = q;
	}
	delete file_name;
	_findclose(file);
	return 0;
}
int print_judege_array(int p, int i_end, int j_end, int arr[][MAX_COLUMN], int book[][MAX_COLUMN], int color[][MAX_COLUMN], int origin[][MAX_COLUMN], int x, int y)
{
	reset(book);
	reset(color);
	int num;
	if (num = judge_error(book, arr, color))
	{
		if (p == 2||p==3||p==4)
		{
			print_color(arr, book, color, origin, x, y, -1);
		}
		cout << "一共有" << num << "处错误的数字" << endl;
		if (p == 1)
			print_array(MAX_ROW, MAX_COLUMN, arr, book, color, origin, x, y);
	}
	else
		if (p == 1)
			print_array(MAX_ROW, MAX_COLUMN, arr, book, color, origin, x, y);
		else if (p == 2 || p == 3 || p == 4)
			print_color(arr, book, color, origin, x, y, -1);
	return num;
}
void copy_arr(int arr[][MAX_COLUMN], int o[][MAX_COLUMN])
{
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			o[i][j] = arr[i][j];
}
int linklist_destroy_step(STEP *head)
{
	STEP *p, *q;

	p = head; //p复位，指向第1个结点
	while (p) {  //循环进行各结点释放
		q = p->next;
		delete p;
		p = q;
	}
	return OK;
}
int linklist_destroy_name(FILE_NAME *head)
{
	FILE_NAME *p, *q;

	p = head; //p复位，指向第1个结点
	while (p) {  //循环进行各结点释放
		q = p->next;
		delete p->name;
		delete p;
		p = q;
	}
	return OK;
}
int search1_1(int x, int y, const int a[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = 0; i < MAX_ROW; i++)
		if (a[i][y] == temp&&i != x)
			return 1;
	return 0;
}
int search2_1(int x, int y, const int a[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = 0; i < MAX_COLUMN; i++)
		if (a[x][i] == temp&&i != y)
			return 1;
	return 0;
}
int search3_1(int x, int y, const int a[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			if (a[i][j] == temp && !(i == x&&j == y))
				return 1;
	return 0;
}
int judge_error_1(const int a[][MAX_COLUMN])
{
	int flag = 0;
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			if (a[i][j] != 0)
			{
				int temp1 = search1_1(i, j, a);
				int temp2 = search2_1(i, j, a);
				int temp3 = search3_1(i, j, a);
				if (temp1 || temp2 || temp3)
				{
					flag = 1;
					break;
				}

			}
	return flag;
}
void judge(int x, int y, int a[][MAX_COLUMN], int book[])
{
	for (int i = 0; i < 9; i++)
		book[i] = 0;
	for (int i = 0; i < 9; i++)
		if (a[x][i] != 0)
			book[a[x][i] - 1] = 1;
	for (int i = 0; i < 9; i++)
		if (a[i][y] != 0)
			book[a[i][y] - 1] = 1;
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			if (a[i][j] != 0)
				book[a[i][j] - 1] = 1;
}
int dfs(int a[][MAX_COLUMN], int n, int origin[][MAX_COLUMN], int book_[][MAX_COLUMN],int clear)
{
	static int step = 0;
	if (clear == 1)
		step = 0;
	int x = n / 9;
	int y = n % 9;
	if (judge_error_1(a))
		return 0;
	gotoxy(hout, 0, 0);
	if (a[x][y] == 0)
	{
		step++;
		print_color(a, book_, book_, origin, x, y, 1);
		gotoxy(hout, 0, 3 * MAX_COLUMN + 4);
		cout << "搜索步数：" << step;
	}
	if (n >= 81)
	{
		print_color(a, book_, book_, origin, x, y, 1);
		gotoxy(hout, 0, 3 * MAX_COLUMN + 4);
		cout << "搜索步数：" << step;
		return 1;
	}
	if (a[x][y] == 0)
	{
		int book[9];
		judge(x, y, a, book);
		for (int i = 0; i < 9; i++)
		{
			if (book[i] != 0)
				continue;
			else
			{
				a[x][y] = i + 1;
				if (dfs(a, n + 1, origin, book_,0) == 1)
					return 1;
				a[x][y] = 0;
			}
		}
	}
	else
		if (dfs(a, n + 1, origin, book_,0) == 1)
			return 1;
		else
			return 0;
	return 0;
}
