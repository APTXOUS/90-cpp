#define _QR_ENCODE_H

#include <string.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

// 纠错级别
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// 数据模式
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// 版本(型号)组
#define QR_VRESION_S	0 // 1 ～ 9
#define QR_VRESION_M	1 // 10 ～ 26
#define QR_VRESION_L	2 // 27 ～ 40

#define MAX_ALLCODEWORD	 3706 // 总代码字最大值
#define MAX_DATACODEWORD 2956 // 数据码字最大值
#define MAX_CODEBLOCK	  153 // 最大块数据码数（包括rs码字）
#define MAX_MODULESIZE	  177 // 最大模块数

//位图绘制边距
#define QR_MARGIN	4

// qr码版本相关信息

typedef struct rs_code
{
	int num_rs_code;		// rs块计数
	int num_AllCodeWord;	// 块中的代码词数
	int num_DataCodeWord;	// 数据码词数（码字数-rs码字）

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


typedef struct QRcode
{
	int num_version;	   // 版本号(1～40)
	int num_all_word; // 代码总词数

					   // 以下数组索引是纠错率（0=l,1=m,2=q,3=h）
	int num_data_word[4];	// 数据码词数（总码字-rs码字）

	int ncAlignPoint;	// 疏模式坐标数
	int nAlignPoint[6];	// 疏模式中心坐标

	RS_BLOCKINFO RS_BlockInfo1[4]; //rs块信息(1)
	RS_BLOCKINFO RS_BlockInfo2[4]; //rs块信息(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;

typedef unsigned short WORD;

typedef unsigned char BYTE;

typedef BYTE* LPBYTE;

typedef const char* LPCSTR;

#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))

