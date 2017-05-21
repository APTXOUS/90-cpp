#pragma once
#pragma once
// QR_Encode.h : CQR_Encode クラス宣言およびインターフェイス定義
// Date 2006/05/17	Ver. 1.22	Psytec Inc.


#ifndef _QR_ENCODE_H
#define _QR_ENCODE_H

#include <string.h>
#include <stdlib.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// 定数

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


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// rs块计数
	int ncAllCodeWord;	// 块中的代码词数
	int ncDataCodeWord;	// 数据码词数（码字数-rs码字）

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// qr码版本相关信息

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本号(1～40)
	int ncAllCodeWord; // 代码总词数

					   // 以下数组索引是纠错率（0=l,1=m,2=q,3=h）
	int ncDataCodeWord[4];	// 数据码词数（总码字-rs码字）

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


class CQR_Encode
{
	// 生成/消失
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// 纠错级别
	int m_nVersion;		// 版本（型号）
	bool m_bAutoExtent;	// 版本（型号）auto-extended 标志
	int m_nMaskingNo;	// 掩码编号

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
														 // bit5:功能模块（未覆盖）标志
														 // bit4:功能模块绘图数据
														 // bit1:编码数据
														 // bit0:蒙版编码后的绘图数据
														 // 函数模块的确定由逻辑和

private:
	int m_ncDataCodeWordBit; // 数据码字位长度
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; // 输入数据编码区域

	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // 密码词总数 (包括 rs 纠错数据)
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // 总代码字计算区域
	BYTE m_byRSWork[MAX_CODEBLOCK]; // rs 码字计算工作

									// 数据编码相关函数
public:
	bool EncodeData(int nLevel, int nVersion, bool bAutoExtent, int nMaskingNo, LPCSTR lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, LPCSTR lpsSource, int ncLength);
	bool EncodeSourceData(LPCSTR lpsSource, int ncLength, int nVerGroup);

	int GetBitLength(BYTE nMode, int ncData, int nVerGroup);

	int SetBitStream(int nIndex, WORD wData, int ncData);

	bool IsNumeralData(unsigned char c);
	bool IsAlphabetData(unsigned char c);
	bool IsKanjiData(unsigned char c1, unsigned char c2);

	BYTE AlphabetToBinaly(unsigned char c);
	WORD KanjiToBinaly(WORD wc);

	void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

	// 模块放置功能
private:
	void FormatModule();

	void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	void SetVersionPattern();
	void SetCodeWordPattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	int CountPenalty();
};

/////////////////////////////////////////////////////////////////////////////

#endif