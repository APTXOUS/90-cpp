/*1650254 尤尧寅 计算机一班*/
#include"90-b4.h"

QRcode::QRcode()
{
	;
}
QRcode::~QRcode()
{
	if (target)
		delete target;
	if (ans)
		delete ans;
	if (code)
		delete code;
	if (code_word_final)
		delete code_word_final;
}
bool QRcode::encode_byte()
{
	int length = strlen(target);
	ans[0] = 0;
	ans[1] = 1;
	ans[2] = 0;
	ans[3] = 0;
	int head = 4;
	int nobicci;
	if (version_group == QR_VRESION_S)
		nobicci = 8;
	else
		nobicci = 16;
	int temp = 0x0001;
	for (int i = 0; i < nobicci; i++)
	{
		if ((temp&length) != 0x0000)
			ans[head + nobicci - i - 1] = 1;
		temp = temp << 1;
	}
	int i = 0;
	head = head + nobicci;
	while (target[i] != '\0')
	{
		unsigned char temp1 = 0x80;
		for (int j = 0; j < 8; j++)
		{
			if ((temp1&target[i]) != 0x0000)
				ans[head] = 1;
			temp1 = temp1 >> 1;
			head++;
		}
		i++;
	}
	len_num = head;
	return 1;
}
void QRcode::add_zeros()
{
	while (len_num % 8 != 0)
	{
		ans[len_num] = 0;
		len_num++;
	}
}
void QRcode::add_what()
{

	if (len_num < version_num)
	{
		int &i = len_num;
		int n = 1;
		while (i < version_num)
		{

			if (n == 1)
			{
				ans[i++] = 1;
				ans[i++] = 1;
				ans[i++] = 1;
				ans[i++] = 0;
				ans[i++] = 1;
				ans[i++] = 1;
				ans[i++] = 0;
				ans[i++] = 0;
				n = -n;
			}
			else
			{
				ans[i++] = 0;
				ans[i++] = 0;
				ans[i++] = 0;
				ans[i++] = 1;
				ans[i++] = 0;
				ans[i++] = 0;
				ans[i++] = 0;
				ans[i++] = 1;
				n = -n;
			}

		}
	}
}
int QRcode::auto_version()
{
	int num = 1 + strlen(target);

	for (int i = 0; i <= QR_VRESION_L; i++)
	{

		if (i == QR_VRESION_S)
		{
			for (int j = 1; j <= 9; j++)
			{
				if ((num + 1) <= QR_VersonInfo[j].ncDataCodeWord[version_level])
					return j;
			}
		}
		else if (i == QR_VRESION_M)
		{
			for (int j = 10; j <= 26; j++)
			{
				if ((num + 2) <= QR_VersonInfo[j].ncDataCodeWord[version_level])
					return j;
			}
		}
		else if (i == QR_VRESION_L)
		{
			for (int j = 27; j <= 40; j++)
			{
				if ((num + 2) <= QR_VersonInfo[j].ncDataCodeWord[version_level])
					return j;
			}
		}
	}

	return 0;
}
void QRcode::auto_version_group()
{
	if (version >= 27)
		version_group = QR_VRESION_L;
	else if (version >= 10)
		version_group = QR_VRESION_M;
	else
		version_group = QR_VRESION_S;
}
void QRcode::add_code_data()
{
	num_code_word_without = QR_VersonInfo[version].ncAllCodeWord;
	memset(code_word_final, 0, num_code_word_without);

	int nDataCwIndex = 0; // 数据码字处理位置

						  // 数据块分区数
	int ncBlock1 = QR_VersonInfo[version].RS_BlockInfo1[version_level].ncRSBlock;
	int ncBlock2 = QR_VersonInfo[version].RS_BlockInfo2[version_level].ncRSBlock;
	int ncBlockSum = ncBlock1 + ncBlock2;

	int nBlockNo = 0; // 进程中的块数

					  // 按块的数据码数
	int ncDataCw1 = QR_VersonInfo[version].RS_BlockInfo1[version_level].ncDataCodeWord;
	int ncDataCw2 = QR_VersonInfo[version].RS_BlockInfo2[version_level].ncDataCodeWord;

	// 数据码字交错放置
	int i, j;
	for (i = 0; i < ncBlock1; ++i)
	{
		for (j = 0; j < ncDataCw1; ++j)
		{
			code_word_final[(ncBlockSum * j) + nBlockNo] = code[nDataCwIndex++];
		}

		++nBlockNo;
	}

	for (i = 0; i < ncBlock2; ++i)
	{
		for (j = 0; j < ncDataCw2; ++j)
		{
			if (j < ncDataCw1)
			{
				code_word_final[(ncBlockSum * j) + nBlockNo] = code[nDataCwIndex++];
			}
			else
			{
				// 二次事件块分数排列
				code_word_final[(ncBlockSum * ncDataCw1) + i] = code[nDataCwIndex++];
			}
		}

		++nBlockNo;
	}

}
void QRcode::add_rs_code_data()
{
	int nBlockNo = 0;
	int ncBlock[] = { QR_VersonInfo[version].RS_BlockInfo1[version_level].ncRSBlock, QR_VersonInfo[version].RS_BlockInfo2[version_level].ncRSBlock };
	int ncDataCw[] = { QR_VersonInfo[version].RS_BlockInfo1[version_level].ncDataCodeWord, QR_VersonInfo[version].RS_BlockInfo2[version_level].ncDataCodeWord };
	// 每个块的 rs 代码单词数 (与当前状态相同)
	int ncRSCw[] = { QR_VersonInfo[version].RS_BlockInfo1[version_level].ncAllCodeWord - ncDataCw[0], QR_VersonInfo[version].RS_BlockInfo2[version_level].ncAllCodeWord - ncDataCw[1] };
	int ncBlockSum = ncBlock[0] + ncBlock[1];
	//****************如过数据大的情况，则分两个block进行运算**************************
	int num = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < ncBlock[k]; i++)
		{
			memset(m_byRSWork, 0, sizeof(m_byRSWork));//初始化rs纠错码数组
			memmove(m_byRSWork, code + num, ncDataCw[k]);//从数据码中提取第nDataCwIndex的数据
			encode_rscode(m_byRSWork, ncDataCw[k], ncRSCw[k]);//运算纠错码
			// rs 码字放置
			for (int j = 0; j < ncRSCw[k]; j++)
				code_word_final[len_num_char + (ncBlockSum * j) + nBlockNo] = m_byRSWork[j];
			num += ncDataCw[k];
			nBlockNo++;
		}
	}
	m_nSymbleSize = version * 4 + 17;
}
void QRcode::change_bool_into_char()
{
	int num_a = len_num;
	len_num_char = len_num / 8;
	int j_ = 0;
	for (int i = 0; i < num_a; i = i + 8)
	{
		int num = 0;
		if (ans[i + 7] == 1)
			num += 1;
		if (ans[i + 6] == 1)
			num += 2;
		if (ans[i + 5] == 1)
			num += 4;
		if (ans[i + 4] == 1)
			num += 8;
		if (ans[i + 3] == 1)
			num += 16;
		if (ans[i + 2] == 1)
			num += 32;
		if (ans[i + 1] == 1)
			num += 64;
		if (ans[i + 0] == 1)
			num += 128;
		code[j_] = num;
		j_++;
	}
	delete ans;
	ans = NULL;
}
bool QRcode::encode_qrcode(const char * source, int nlevel)
{
	target = G2U(source);
	
	//target = (char *)source;
	target_num = strlen(target);
	version_level = nlevel;
	version = auto_version();
	auto_version_group();
	code_word_final = new(nothrow) unsigned char[(17 + version * 4)*(17 + version * 4)];
	version_num = QR_VersonInfo[version].ncDataCodeWord[version_level] * 8;
	ans = new (nothrow)bool[version_num];
	memset(ans, 0, version_num);
	encode_byte();
	add_zeros();
	add_what();
	cout << endl;
	code = new unsigned char[version_num + 1];
	change_bool_into_char();
	add_code_data();
	add_rs_code_data();
	FormatModule();
	return 0;
}
void QRcode::encode_rscode(LPBYTE datacode, int ncDataCodeWord, int ncRSCodeWord)
{
	//*************生成多项式除消息多项式*******************
	for (int i = 0; i < ncDataCodeWord; i++)
	{
		if (datacode[0] != 0)
		{
			BYTE temp_first = byIntToExp[datacode[0]]; // 从第一项系数计算乘数

			for (int j = 0; j < ncRSCodeWord; j++)
			{
				// 将第一项的消息指数和生成多项式指数相加，假如大于255要对255取余
				BYTE nExpElement = (BYTE)(((int)(byRSExp[ncRSCodeWord][j] + temp_first)) % 255);

				//********同时进行xor运算**************************************
				datacode[j] = (BYTE)(datacode[j + 1] ^ byExpToInt[nExpElement]);//XOR运算
			}
			

			// 移位剩余数字
			for (int j = ncRSCodeWord; j < ncDataCodeWord + ncRSCodeWord - 1; j++)
				datacode[j] = datacode[j + 1];
		}
		else
		{
			// 移位剩余数字
			// 丢弃系数为0的项：
			for (int j = 0; j < ncDataCodeWord + ncRSCodeWord - 1; j++)
				datacode[j] = datacode[j + 1];
		}
	}
}