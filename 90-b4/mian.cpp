#include"qrcode.h"
#include <iostream>
#include <Windows.h>
//初始化句柄
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
using namespace std;
//GB2312到UTF-8的转换

char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

int main() {
	CQR_Encode test;
	test.EncodeData(1, 1, 1, 1, G2U("http://iceie.tongji.edu.cn"), 0);

	int i, j;

	for (i = 0; i < MAX_MODULESIZE; i++) {
		for (j = 0; j < sizeof("■■■■■■■  ■  ■  ■  ■■■■■■■"); j++) {
			if (test.m_byModuleData[i][j]) {
				SetConsoleTextAttribute(hout, 0 * 16 + 7);
				cout << "  ";
			}
			else {
				SetConsoleTextAttribute(hout, 7 * 16 + 7);
				cout << "  ";

			}
		}
		cout << endl;
	}
	system("pause");
	return 0;
}