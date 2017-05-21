/*1650254 ÓÈÒ¢Òú ¼ÆËã»úÒ»°à*/
#include"90-b4.h"
int main() {

	QRcode a;
	system("pause");
	a.encode_qrcode("http://iceie.tongji.edu.cn", 3);
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