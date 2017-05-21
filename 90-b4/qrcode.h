#pragma once
#pragma once
// QR_Encode.h : CQR_Encode クラス傚冱およびインタ�`フェイス協�x
// Date 2006/05/17	Ver. 1.22	Psytec Inc.


#ifndef _QR_ENCODE_H
#define _QR_ENCODE_H

#include <string.h>
#include <stdlib.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// 協方

// 樟危雫艶
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// 方象庁塀
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// 井云(侏催)怏
#define QR_VRESION_S	0 // 1 ゛ 9
#define QR_VRESION_M	1 // 10 ゛ 26
#define QR_VRESION_L	2 // 27 ゛ 40

#define MAX_ALLCODEWORD	 3706 // 悳旗鷹忖恷寄峙
#define MAX_DATACODEWORD 2956 // 方象鷹忖恷寄峙
#define MAX_CODEBLOCK	  153 // 恷寄翠方象鷹方�┛�凄rs鷹忖��
#define MAX_MODULESIZE	  177 // 恷寄庁翠方

//了夕紙崙円鉦
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// rs翠柴方
	int ncAllCodeWord;	// 翠嶄議旗鷹簡方
	int ncDataCodeWord;	// 方象鷹簡方��鷹忖方-rs鷹忖��

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// qr鷹井云�犢慚渡�

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 井云催(1゛40)
	int ncAllCodeWord; // 旗鷹悳簡方

					   // 參和方怏沫哈頁樟危楕��0=l,1=m,2=q,3=h��
	int ncDataCodeWord[4];	// 方象鷹簡方��悳鷹忖-rs鷹忖��

	int ncAlignPoint;	// 墓庁塀恫炎方
	int nAlignPoint[6];	// 墓庁塀嶄伉恫炎

	RS_BLOCKINFO RS_BlockInfo1[4]; //rs翠佚連(1)
	RS_BLOCKINFO RS_BlockInfo2[4]; //rs翠佚連(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;

typedef unsigned short WORD;

typedef unsigned char BYTE;

typedef BYTE* LPBYTE;

typedef const char* LPCSTR;

#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))


class CQR_Encode
{
	// 伏撹/��払
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// 樟危雫艶
	int m_nVersion;		// 井云��侏催��
	bool m_bAutoExtent;	// 井云��侏催��auto-extended 炎崗
	int m_nMaskingNo;	// 凉鷹園催

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
														 // bit5:孔嬬庁翠��隆顕固��炎崗
														 // bit4:孔嬬庁翠紙夕方象
														 // bit1:園鷹方象
														 // bit0:檀井園鷹朔議紙夕方象
														 // 痕方庁翠議鳩協喇貸辞才

private:
	int m_ncDataCodeWordBit; // 方象鷹忖了海業
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; // 補秘方象園鷹曝囃

	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // 畜鷹簡悳方 (淫凄 rs 樟危方象)
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // 悳旗鷹忖柴麻曝囃
	BYTE m_byRSWork[MAX_CODEBLOCK]; // rs 鷹忖柴麻垢恬

									// 方象園鷹�犢愃�方
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

	// 庁翠慧崔孔嬬
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