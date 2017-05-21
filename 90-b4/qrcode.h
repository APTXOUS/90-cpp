#pragma once
#pragma once
// QR_Encode.h : CQR_Encode ���饹���Ԥ���ӥ��󥿩`�ե��������x
// Date 2006/05/17	Ver. 1.22	Psytec Inc.


#ifndef _QR_ENCODE_H
#define _QR_ENCODE_H

#include <string.h>
#include <stdlib.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// ����

// ������
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// ����ģʽ
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// �汾(�ͺ�)��
#define QR_VRESION_S	0 // 1 �� 9
#define QR_VRESION_M	1 // 10 �� 26
#define QR_VRESION_L	2 // 27 �� 40

#define MAX_ALLCODEWORD	 3706 // �ܴ��������ֵ
#define MAX_DATACODEWORD 2956 // �����������ֵ
#define MAX_CODEBLOCK	  153 // ������������������rs���֣�
#define MAX_MODULESIZE	  177 // ���ģ����

//λͼ���Ʊ߾�
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// rs�����
	int ncAllCodeWord;	// ���еĴ������
	int ncDataCodeWord;	// �����������������-rs���֣�

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// qr��汾�����Ϣ

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // �汾��(1��40)
	int ncAllCodeWord; // �����ܴ���

					   // �������������Ǿ����ʣ�0=l,1=m,2=q,3=h��
	int ncDataCodeWord[4];	// �����������������-rs���֣�

	int ncAlignPoint;	// ��ģʽ������
	int nAlignPoint[6];	// ��ģʽ��������

	RS_BLOCKINFO RS_BlockInfo1[4]; //rs����Ϣ(1)
	RS_BLOCKINFO RS_BlockInfo2[4]; //rs����Ϣ(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;

typedef unsigned short WORD;

typedef unsigned char BYTE;

typedef BYTE* LPBYTE;

typedef const char* LPCSTR;

#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))


class CQR_Encode
{
	// ����/��ʧ
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// ������
	int m_nVersion;		// �汾���ͺţ�
	bool m_bAutoExtent;	// �汾���ͺţ�auto-extended ��־
	int m_nMaskingNo;	// ������

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
														 // bit5:����ģ�飨δ���ǣ���־
														 // bit4:����ģ���ͼ����
														 // bit1:��������
														 // bit0:�ɰ�����Ļ�ͼ����
														 // ����ģ���ȷ�����߼���

private:
	int m_ncDataCodeWordBit; // ��������λ����
	BYTE m_byDataCodeWord[MAX_DATACODEWORD]; // �������ݱ�������

	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // ��������� (���� rs ��������)
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // �ܴ����ּ�������
	BYTE m_byRSWork[MAX_CODEBLOCK]; // rs ���ּ��㹤��

									// ���ݱ�����غ���
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

	// ģ����ù���
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