/*1650254 ��Ң�� �����һ��*/
#include"90-b4.h"
/*****************************************************************/
void QRcode::FormatModule()
{

	memset(module_code, 0, 177 * 177);

	SetFunctionModule();
	// �ǩ`���ѥ��`������
	SetCodeWordPattern();

	// ���m�ޥ����󥰥ѥ��`���x�k
	int	m_nMaskingNo = 0;

	SetMaskingPattern(m_nMaskingNo); // �ޥ�����
	SetFormatInfoPattern(m_nMaskingNo); // �ե��`�ޥå����ѥ��`������

	int nMinPenalty = CountPenalty();

	for (int i = 1; i <= 7; ++i)
	{
		SetMaskingPattern(i); // �ޥ�����
		SetFormatInfoPattern(i); // �ե��`�ޥå����ѥ��`������

		int nPenalty = CountPenalty();

		if (nPenalty < nMinPenalty)
		{
			nMinPenalty = nPenalty;
			m_nMaskingNo = i;
		}
	}

	SetMaskingPattern(m_nMaskingNo); // �ޥ�����
	SetFormatInfoPattern(m_nMaskingNo); // �ե��`�ޥå����ѥ��`������

										// �⥸��`��ѥ��`���֩`�낎�ˉ�Q
	for (int i = 0; i < m_nSymbleSize; ++i)
	{
		for (int j = 0; j < m_nSymbleSize; ++j)
		{
			module_code[i][j] = (BYTE)((module_code[i][j] & 0x11) != 0);
		}
	}
}
void QRcode::SetFunctionModule()
{
	int i, j;

	// λ�×ʳ��ѥ��`��
	SetFinderPattern(0, 0);
	SetFinderPattern(m_nSymbleSize - 7, 0);
	SetFinderPattern(0, m_nSymbleSize - 7);

	// λ�×ʳ��ѥ��`�󥻥ѥ�`��
	for (i = 0; i < 8; ++i)
	{
		module_code[i][7] = module_code[7][i] = '\x20';
		module_code[m_nSymbleSize - 8][i] = module_code[m_nSymbleSize - 8 + i][7] = '\x20';
		module_code[i][m_nSymbleSize - 8] = module_code[7][m_nSymbleSize - 8 + i] = '\x20';
	}

	// �ե��`�ޥå����ӛ��λ�ä�C�ܥ⥸��`�벿�Ȥ��Ƶ��h
	for (i = 0; i < 9; ++i)
	{
		module_code[i][8] = module_code[8][i] = '\x20';
	}

	for (i = 0; i < 8; ++i)
	{
		module_code[m_nSymbleSize - 8 + i][8] = module_code[8][m_nSymbleSize - 8 + i] = '\x20';
	}

	// �Щ`��������ѥ��`��
	SetVersionPattern();

	// λ�úϤ碌�ѥ��`��
	for (i = 0; i < QR_VersonInfo[version].ncAlignPoint; ++i)
	{
		SetAlignmentPattern(QR_VersonInfo[version].nAlignPoint[i], 6);
		SetAlignmentPattern(6, QR_VersonInfo[version].nAlignPoint[i]);

		for (j = 0; j < QR_VersonInfo[version].ncAlignPoint; ++j)
		{
			SetAlignmentPattern(QR_VersonInfo[version].nAlignPoint[i], QR_VersonInfo[version].nAlignPoint[j]);
		}
	}

	// �����ߥ󥰥ѥ��`��
	for (i = 8; i <= m_nSymbleSize - 9; ++i)
	{
		module_code[i][6] = (i % 2) == 0 ? '\x30' : '\x20';
		module_code[6][i] = (i % 2) == 0 ? '\x30' : '\x20';
	}
}
void QRcode::SetFinderPattern(int x, int y)
{
	static BYTE byPattern[] = { 0x7f,  // 1111111b
		0x41,  // 1000001b
		0x5d,  // 1011101b
		0x5d,  // 1011101b
		0x5d,  // 1011101b
		0x41,  // 1000001b
		0x7f }; // 1111111b
	int i, j;

	for (i = 0; i < 7; ++i)
	{
		for (j = 0; j < 7; ++j)
		{
			module_code[x + j][y + i] = (byPattern[i] & (1 << (6 - j))) ? '\x30' : '\x20';
		}
	}
}
void QRcode::SetAlignmentPattern(int x, int y)
{
	static BYTE byPattern[] = { 0x1f,  // 11111b
		0x11,  // 10001b
		0x15,  // 10101b
		0x11,  // 10001b
		0x1f }; // 11111b
	int i, j;

	if (module_code[x][y] & 0x20)
		return; // �C�ܥ⥸��`������}���뤿�����

	x -= 2; y -= 2; // ���������ˤˉ�Q

	for (i = 0; i < 5; ++i)
	{
		for (j = 0; j < 5; ++j)
		{
			module_code[x + j][y + i] = (byPattern[i] & (1 << (4 - j))) ? '\x30' : '\x20';
		}
	}
}
void QRcode::SetVersionPattern()
{
	int i, j;

	if (version <= 6)
		return;

	int nVerData = version << 12;

	// ����ӥå����
	for (i = 0; i < 6; ++i)
	{
		if (nVerData & (1 << (17 - i)))
		{
			nVerData ^= (0x1f25 << (5 - i));
		}
	}

	nVerData += version << 12;

	for (i = 0; i < 6; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			module_code[m_nSymbleSize - 11 + j][i] = module_code[i][m_nSymbleSize - 11 + j] =
				(nVerData & (1 << (i * 3 + j))) ? '\x30' : '\x20';
		}
	}
}
void QRcode::SetCodeWordPattern()
{
	int x = m_nSymbleSize;
	int y = m_nSymbleSize - 1;

	int nCoef_x = 1; // ���S������
	int nCoef_y = 1; // ���S������

	int i, j;

	for (i = 0; i < num_code_word_without; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			do
			{
				x += nCoef_x;
				nCoef_x *= -1;

				if (nCoef_x < 0)
				{
					y += nCoef_y;

					if (y < 0 || y == m_nSymbleSize)
					{
						y = (y < 0) ? 0 : m_nSymbleSize - 1;
						nCoef_y *= -1;

						x -= 2;

						if (x == 6) // �����ߥ󥰥ѥ��`��
							--x;
					}
				}
			} while (module_code[x][y] & 0x20); // �C�ܥ⥸��`������

			module_code[x][y] = (code_word_final[i] & (1 << (7 - j))) ? '\x02' : '\x00';
		}
	}
}
void QRcode::SetMaskingPattern(int nPatternNo)
{
	int i, j;

	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize; ++j)
		{
			if (!(module_code[j][i] & 0x20)) // �C�ܥ⥸��`������
			{
				bool bMask;
				//bMask = ((i + j) % 3 == 0);
				switch (nPatternNo)
				{
				case 0:
					bMask = ((i + j) % 2 == 0);
					break;

				case 1:
					bMask = (i % 2 == 0);
					break;

				case 2:
					bMask = (j % 3 == 0);
					break;

				case 3:
					bMask = ((i + j) % 3 == 0);
					break;

				case 4:
					bMask = (((i / 2) + (j / 3)) % 2 == 0);
					break;

				case 5:
					bMask = (((i * j) % 2) + ((i * j) % 3) == 0);
					break;

				case 6:
					bMask = ((((i * j) % 2) + ((i * j) % 3)) % 2 == 0);
					break;

				default: // case 7:
					bMask = ((((i * j) % 3) + ((i + j) % 2)) % 2 == 0);
					break;
				}

				module_code[j][i] = (BYTE)((module_code[j][i] & 0xfe) | (((module_code[j][i] & 0x02) > 1) ^ bMask));
			}
		}
	}
}
void QRcode::SetFormatInfoPattern(int nPatternNo)
{
	int nFormatInfo;
	int i;

	switch (version_level)
	{
	case QR_LEVEL_M:
		nFormatInfo = 0x00; // 00nnnb
		break;

	case QR_LEVEL_L:
		nFormatInfo = 0x08; // 01nnnb
		break;

	case QR_LEVEL_Q:
		nFormatInfo = 0x18; // 11nnnb
		break;

	default: // case QR_LEVEL_H:
		nFormatInfo = 0x10; // 10nnnb
		break;
	}

	nFormatInfo += nPatternNo;

	int nFormatData = nFormatInfo << 10;

	// ����ӥå����
	for (i = 0; i < 5; ++i)
	{
		if (nFormatData & (1 << (14 - i)))
		{
			nFormatData ^= (0x0537 << (4 - i)); // 10100110111b
		}
	}

	nFormatData += nFormatInfo << 10;

	// �ޥ�����
	nFormatData ^= 0x5412; // 101010000010010b

						   // ����λ�×ʳ��ѥ��`���ܤ�����
	for (i = 0; i <= 5; ++i)
		module_code[8][i] = (nFormatData & (1 << i)) ? '\x30' : '\x20';

	module_code[8][7] = (nFormatData & (1 << 6)) ? '\x30' : '\x20';
	module_code[8][8] = (nFormatData & (1 << 7)) ? '\x30' : '\x20';
	module_code[7][8] = (nFormatData & (1 << 8)) ? '\x30' : '\x20';

	for (i = 9; i <= 14; ++i)
		module_code[14 - i][8] = (nFormatData & (1 << i)) ? '\x30' : '\x20';

	// ����λ�×ʳ��ѥ��`��������
	for (i = 0; i <= 7; ++i)
		module_code[m_nSymbleSize - 1 - i][8] = (nFormatData & (1 << i)) ? '\x30' : '\x20';

	// ����λ�×ʳ��ѥ��`��������
	module_code[8][m_nSymbleSize - 8] = '\x30'; // �̶����⥸��`��

	for (i = 8; i <= 14; ++i)
		module_code[8][m_nSymbleSize - 15 + i] = (nFormatData & (1 << i)) ? '\x30' : '\x20';
}
int QRcode::CountPenalty()
{
	int nPenalty = 0;
	int i, j, k;

	// ͬɫ���Ф��O�ӥ⥸��`��
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 4; ++j)
		{
			int nCount = 1;

			for (k = j + 1; k < m_nSymbleSize; k++)
			{
				if (((module_code[i][j] & 0x11) == 0) == ((module_code[i][k] & 0x11) == 0))
					++nCount;
				else
					break;
			}

			if (nCount >= 5)
			{
				nPenalty += 3 + (nCount - 5);
			}

			j = k - 1;
		}
	}

	// ͬɫ���Ф��O�ӥ⥸��`��
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 4; ++j)
		{
			int nCount = 1;

			for (k = j + 1; k < m_nSymbleSize; k++)
			{
				if (((module_code[j][i] & 0x11) == 0) == ((module_code[k][i] & 0x11) == 0))
					++nCount;
				else
					break;
			}

			if (nCount >= 5)
			{
				nPenalty += 3 + (nCount - 5);
			}

			j = k - 1;
		}
	}

	// ͬɫ�Υ⥸��`��֥�å�����������
	for (i = 0; i < m_nSymbleSize - 1; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 1; ++j)
		{
			if ((((module_code[i][j] & 0x11) == 0) == ((module_code[i + 1][j] & 0x11) == 0)) &&
				(((module_code[i][j] & 0x11) == 0) == ((module_code[i][j + 1] & 0x11) == 0)) &&
				(((module_code[i][j] & 0x11) == 0) == ((module_code[i + 1][j + 1] & 0x11) == 0)))
			{
				nPenalty += 3;
			}
		}
	}

	// ͬһ�Фˤ����� 1:1:3:1:1 ���ʣ���:��:��:��:�����Υѥ��`��
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 6; ++j)
		{
			if (((j == 0) || (!(module_code[i][j - 1] & 0x11))) && // �� �ޤ��� ����ܥ���
				(module_code[i][j] & 0x11) && // �� - 1
				(!(module_code[i][j + 1] & 0x11)) && // �� - 1
				(module_code[i][j + 2] & 0x11) && // �� ��
				(module_code[i][j + 3] & 0x11) && // �� ��3
				(module_code[i][j + 4] & 0x11) && // �� ��
				(!(module_code[i][j + 5] & 0x11)) && // �� - 1
				(module_code[i][j + 6] & 0x11) && // �� - 1
				((j == m_nSymbleSize - 7) || (!(module_code[i][j + 7] & 0x11))))   // �� �ޤ��� ����ܥ���
			{
				// ǰ�ޤ������4���Ϥ����ѥ��`��
				if (((j < 2 || !(module_code[i][j - 2] & 0x11)) &&
					(j < 3 || !(module_code[i][j - 3] & 0x11)) &&
					(j < 4 || !(module_code[i][j - 4] & 0x11))) ||
					((j >= m_nSymbleSize - 8 || !(module_code[i][j + 8] & 0x11)) &&
					(j >= m_nSymbleSize - 9 || !(module_code[i][j + 9] & 0x11)) &&
						(j >= m_nSymbleSize - 10 || !(module_code[i][j + 10] & 0x11))))
				{
					nPenalty += 40;
				}
			}
		}
	}

	// ͬһ�Фˤ����� 1:1:3:1:1 ���ʣ���:��:��:��:�����Υѥ��`��
	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize - 6; ++j)
		{
			if (((j == 0) || (!(module_code[j - 1][i] & 0x11))) && // �� �ޤ��� ����ܥ���
				(module_code[j][i] & 0x11) && // �� - 1
				(!(module_code[j + 1][i] & 0x11)) && // �� - 1
				(module_code[j + 2][i] & 0x11) && // �� ��
				(module_code[j + 3][i] & 0x11) && // �� ��3
				(module_code[j + 4][i] & 0x11) && // �� ��
				(!(module_code[j + 5][i] & 0x11)) && // �� - 1
				(module_code[j + 6][i] & 0x11) && // �� - 1
				((j == m_nSymbleSize - 7) || (!(module_code[j + 7][i] & 0x11))))   // �� �ޤ��� ����ܥ���
			{
				// ǰ�ޤ������4���Ϥ����ѥ��`��
				if (((j < 2 || !(module_code[j - 2][i] & 0x11)) &&
					(j < 3 || !(module_code[j - 3][i] & 0x11)) &&
					(j < 4 || !(module_code[j - 4][i] & 0x11))) ||
					((j >= m_nSymbleSize - 8 || !(module_code[j + 8][i] & 0x11)) &&
					(j >= m_nSymbleSize - 9 || !(module_code[j + 9][i] & 0x11)) &&
						(j >= m_nSymbleSize - 10 || !(module_code[j + 10][i] & 0x11))))
				{
					nPenalty += 40;
				}
			}
		}
	}

	// ȫ��ˌ����밵�⥸��`���ռ�����
	int nCount = 0;

	for (i = 0; i < m_nSymbleSize; ++i)
	{
		for (j = 0; j < m_nSymbleSize; ++j)
		{
			if (!(module_code[i][j] & 0x11))
			{
				++nCount;
			}
		}
	}

	nPenalty += (abs(50 - ((nCount * 100) / (m_nSymbleSize * m_nSymbleSize))) / 5) * 10;

	return nPenalty;
}
char* QRcode::G2U(const char* gb2312)
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
/*******************************************************************/