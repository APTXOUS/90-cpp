/*1650254 尤尧寅 计算机一班*/
#include"90-b4.h"
int main() {

	QRcode a;
	cout << "请输入需要转成二进制的字符：" << endl;
	cout << "网址请输入http://前缀！" << endl;
	char input_[200];
	cin.getline(input_,200,'\n');
	cout << "请输入纠错级别！(0-3)" << endl;
	int num;
	cin >> num;
	int num_str = strlen(input_);
	if (num_str > 20)
		setfontsize(hout, L"点阵字体", 5);
	else
		setfontsize(hout, L"点阵字体", 10);
	setconsoleborder(hout, 200, 100);
	a.encode_qrcode(input_ ,num);
	system("cls");
	int i, j;
	for (i = 0; i < 17 + a.version * 4; i++) {
		for (j = 0; j < 17 + a.version * 4; j++) {
			if (a.module_code[i][j]) {
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