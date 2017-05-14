#include<iostream>
#include<cstdlib>
#include<Windows.h>
using namespace std;
#define MAX_COLUMN 9
#define MAX_ROW 9
const int INF = 0x7ffffff;
const int NN = 350;
const int MM = 750;
int n, m;
int cate[NN];
int L[NN*MM], R[NN*MM], U[NN*MM], D[NN*MM];
int C[NN*MM];
int head;
int mx[MM][NN];
int O[MM], idx;
int ans[10][10];
int sort_[9][9];
int line[81][2];
int num;
/* 返回值：0  ：有解
-1 : 原始数据有0-9之外的非法值
-2 ：原始值行/列/九宫有冲突
-3 ：无解
-4 : 其它错误（无内存等）
*/
int search1(int x, int y, const int a[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = 0; i < MAX_ROW; i++)
		if (a[i][y] == temp&&i != x)
		{
			return 1;
		}
	return 0;
}
int search2(int x, int y, const int a[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = 0; i < MAX_COLUMN; i++)
		if (a[x][i] == temp&&i != y)
		{
			return 1;
		}
	return 0;
}
int search3(int x, int y, const int a[][MAX_COLUMN])
{
	int temp = a[x][y];
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
			if (a[i][j] == temp && !(i == x&&j == y))
			{
				return 1;
			}
	return 0;
}
int judge_error(const int a[][MAX_COLUMN])
{
	int flag = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < MAX_COLUMN; j++)
			if (a[i][j] != 0)
			{
				int temp1 = search1(i, j, a);
				int temp2 = search2(i, j, a);
				int temp3 = search3(i, j, a);
				if (temp1 || temp2 || temp3)
				{
					flag++;
				}
			}
	return flag;
}

void remove(int c)
{
	int i, j;
	L[R[c]] = L[c];
	R[L[c]] = R[c];
	for (i = D[c]; i != c; i = D[i])
	{
		for (j = R[i]; j != i; j = R[j])
		{
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			cate[C[j]]--;
		}
	}
}

void resume(int c)
{
	int i, j;
	R[L[c]] = c;
	L[R[c]] = c;
	for (i = D[c]; i != c; i = D[i])
	{
		for (j = R[i]; j != i; j = R[j])
		{
			U[D[j]] = j;
			D[U[j]] = j;
			cate[C[j]]++;
		}
	}
}

bool dfs_()
{
	int i, j, c;
	if (R[head] == head)
		return true;
	int min = INF;
	for (i = R[head]; i != head; i = R[i])
	{
		if (cate[i] < min)
		{
			min = cate[i];
			c = i;
		}
	}
	remove(c);
	for (i = D[c]; i != c; i = D[i])
	{
		//i是某点的序号，将该点所在行的行号保存  
		O[idx++] = (i - 1) / n;
		for (j = R[i]; j != i; j = R[j])
			remove(C[j]);
		if (dfs_())
			return true;
		for (j = L[i]; j != i; j = L[j])
			resume(C[j]);
		idx--;
	}
	resume(c);
	return false;
}

bool build()
{
	int i, j, now, pre, first;
	idx = head = 0;
	for (i = 0; i < n; i++)
	{
		R[i] = i + 1;
		L[i + 1] = i;
	}
	R[n] = 0;
	L[0] = n;
	for (j = 1; j <= n; j++)
	{
		pre = j;
		cate[j] = 0;
		for (i = 1; i <= m; i++)
		{
			if (mx[i][j])
			{
				cate[j]++;
				now = i*n + j;
				C[now] = j;
				D[pre] = now;
				U[now] = pre;
				pre = now;
			}
		}
		U[j] = pre;
		D[pre] = j;
		if (cate[j] == 0)
			return false;
	}
	for (i = 1; i <= m; i++)
	{
		pre = first = -1;
		for (j = 1; j <= n; j++)
		{
			if (mx[i][j])
			{
				now = i*n + j;
				if (pre == -1)
					first = now;
				else
				{
					R[pre] = now;
					L[now] = pre;
				}
				pre = now;
			}
		}
		if (first != -1)
		{
			R[pre] = first;
			L[first] = pre;
		}
	}
	return true;
}

int T;

int print(int sudoku[9][9])
{
	int i;
	int x, y, k;
	for (i = 0; i < idx; i++)
	{
		int r = O[i];
		k = r % 9;
		if (k == 0) k = 9;
		int num = (r - k) / 9 + 1;
		y = num % 9;
		if (y == 0) y = 9;
		x = (num - y) / 9;
		sudoku[x][y - 1] = k;
	}
	if (idx == 0)
		return -3;
	else
		return 0;
}
int link(int s[9][9])
{
	int i, j, k;
	memset(mx, 0, sizeof(mx));
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			int t = (i) * 9 + j + 1;
			if (s[i][j] == 0)
			{
				for (k = 1; k <= 9; k++)
				{
					mx[9 * (t - 1) + k][t] = 1;
					mx[9 * (t - 1) + k][81 + (i) * 9 + k] = 1;
					mx[9 * (t - 1) + k][162 + (j) * 9 + k] = 1;
					mx[9 * (t - 1) + k][243 + ((i) / 3 * 3 + (j + 3) / 3 - 1) * 9 + k] = 1;
				}
			}
			else
			{
				k = s[i][j];
				mx[9 * (t - 1) + k][t] = 1;
				mx[9 * (t - 1) + k][81 + (i) * 9 + k] = 1;
				mx[9 * (t - 1) + k][162 + (j) * 9 + k] = 1;
				mx[9 * (t - 1) + k][243 + ((i) / 3 * 3 + (j + 3) / 3 - 1) * 9 + k] = 1;
			}
		}
	}
	build();
	dfs_();
	return print(s);
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
int dfs_1(int a[][MAX_COLUMN], int n, int book_[][MAX_COLUMN])
{
	int x = n / 9;
	int y = n % 9;
	if (n >= 81)
	{
		return 0;
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
				if (dfs_1(a, n + 1, book_) == 0)
					return 0;
				a[x][y] = 0;
			}
		}
	}
	else
		if (dfs_1(a, n + 1, book_) == 0)
			return 0;
		else
			return -3;
	return -3;
}
int dfs(int a[][MAX_COLUMN], int n, int book_[][MAX_COLUMN])
{
	int x = line[n][0];
	int y = line[n][1];
	//int x = n / 9;
	//int y = n % 9;
	if (n >= 81)
	{
		return 0;
	}
	if (n >= num + 1)
	{
		return 0;
	}
	if (line[n][0] == -1)
		return 0;
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
				if (dfs(a, n + 1, book_) == 0)
					return 0;
				a[x][y] = 0;
			}
		}
	}
	return -3;
}

int solving_sudoku(int sudoku[9][9])
{
	for (int i = 0; i < 1000; i++)
		Sleep(1000);
	num = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] < 0 || sudoku[i][j]>9)
				return -1;
			if (sudoku[i][j] == 0)
				num++;
		}
	if (judge_error(sudoku) != 0)
		return -2;
	if (num < 17)
	{
		int book[9][9];
		memset(book, 0, sizeof(book));
		return dfs_1(sudoku, 0, book);
	}
	else if (num < 81 / 5 * 4)
		return link(sudoku);
	else
	{
		num = 81;
		int book[9][9];
		memset(book, 0, sizeof(book));
		memset(sort_, 0, sizeof(sort_));
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (sudoku[i][j] != 0)
					for (int k = 0; k < 9; k++)
						sort_[i][k]++;
		for (int j = 0; j < 9; j++)
			for (int i = 0; i < 9; i++)
				if (sudoku[i][j] != 0)
					for (int k = 0; k < 9; k++)
						sort_[k][j]++;
		for (int k = 0; k < 9; k++)
		{
			int sum = 0;
			for (int i = k % 3 * 3; i < k % 3 * 3 + 3; i++)
				for (int j = k / 3 * 3; j < k / 3 * 3 + 3; j++)
					if (sudoku[i][j] != 0)
						sum++;
			for (int i = k % 3 * 3; i < k % 3 * 3 + 3; i++)
				for (int j = k / 3 * 3; j < k / 3 * 3 + 3; j++)
					sort_[i][j] += sum;
		}
		memset(line, -1, sizeof(line));
		for (int i = 0; i < 81; i++)
		{
			int max = -2;
			int max_x = 0;
			int max_y = 0;
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
				{
					if (sort_[i][j] != -1 && sort_[i][j] >= max&&sudoku[i][j] == 0)
					{
						max_x = i;
						max_y = j;
						max = sort_[i][j];
					}
				}
			line[i][0] = -1;
			if (max == -2)
			{
				num = i;
				//	cout << num;
				break;
			}
			line[i][0] = max_x;
			line[i][1] = max_y;
			//cout << max_x << max_y << endl;
			sort_[max_x][max_y] = -1;
		}
		return dfs(sudoku, 0, book);
	}
}