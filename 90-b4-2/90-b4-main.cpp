#define _QR_ENCODE_H

#include <string.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

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

// qr��汾�����Ϣ

typedef struct rs_code
{
	int num_rs_code;		// rs�����
	int num_AllCodeWord;	// ���еĴ������
	int num_DataCodeWord;	// �����������������-rs���֣�

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


typedef struct QRcode
{
	int num_version;	   // �汾��(1��40)
	int num_all_word; // �����ܴ���

					   // �������������Ǿ����ʣ�0=l,1=m,2=q,3=h��
	int num_data_word[4];	// �����������������-rs���֣�

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

