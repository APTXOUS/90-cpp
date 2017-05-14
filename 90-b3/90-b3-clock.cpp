/*1650254 ”»“¢“˙ º∆À„ª˙“ª∞‡*/
#include"90-b3.h"
void circle(double x, double y, double length, TIME time,int color_b,int color_f)
{
	double ox = x + length / 2;
	double oy = y + length / 2;
	for (double i = x; i <= x + length; i++)
	{
		for (double j = y; j <= y + length; j++)
		{
			if (fabs((i - ox)*(i - ox) + (j - oy)*(j - oy) - (length / 2)*(length / 2)) < 100)
			{
				gotoxy(hout, int(2 * i), int(j));
				setcolor(hout, color_b, color_f);
				printf("*");
			}
			else
			{
				gotoxy(hout, int(2 * i), int(j));
				setcolor(hout, color_b, color_b);
				printf(" ");
			}
			if ((i - ox)*(i - ox) + (j - oy)*(j - oy) - (length / 2.5)*(length / 2.5) < 0)
			{
				if (int(time.second) % 30 != 0 && ((time.second < 30 && time.second>0)) && i - ox > 0)
				{
					if (!(int(time.second) == 15 || int(time.second) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.second) == 15 || int(time.second) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.second / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.second) % 30 != 0 && ((time.second < 60 && time.second>30)) && i - ox < 0)
				{
					if (!(int(time.second) == 15 || int(time.second) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.second) == 15 || int(time.second) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.second / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.second) == 30 && j - oy > 0)
				{
					if (!(int(time.second) == 15 || int(time.second) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.second) == 15 || int(time.second) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.second / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.second) == 0 && j - oy < 0)
				{
					if (!(int(time.second) == 15 || int(time.second) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.second) == 15 || int(time.second) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.second / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.second / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
			}
			if ((i - ox)*(i - ox) + (j - oy)*(j - oy) - (length / 3)*(length / 3) < 0)
			{
				if (int(time.minute) % 30 != 0 && ((time.minute < 30 && time.minute>0)) && i - ox > 0)
				{
					if (!(int(time.minute) == 15 || int(time.minute) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.minute) == 15 || int(time.minute) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.minute / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.minute) % 30 != 0 && ((time.minute < 60 && time.minute>30)) && i - ox < 0)
				{
					if (!(int(time.minute) == 15 || int(time.minute) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.minute) == 15 || int(time.minute) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.minute / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.minute) == 30 && j - oy > 0)
				{
					if (!(int(time.minute) == 15 || int(time.minute) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.minute) == 15 || int(time.minute) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.minute / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.minute) == 0 && j - oy < 0)
				{
					if (!(int(time.minute) == 15 || int(time.minute) == 45) && fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((int(time.minute) == 15 || int(time.minute) == 45) && fabs((j - oy) - (i - ox) * 1 / tan(time.minute / 30 * 3.1415926)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if (fabs((i - ox) - (j - oy) * 1 / tan(time.minute / 30 * 3.1415926 + 3.1415926 / 2)) <= 1)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
			}
			if ((i - ox)*(i - ox) + (j - oy)*(j - oy) - (length / 4)*(length / 4) < 0)
			{

				if (int(time.hour) % 6 != 0 && ((time.hour < 6 && time.hour>0) || (time.hour < 18 && time.hour>12)) && i - ox > 0)
				{
					if (!(time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((i - ox) - (j - oy) * 1 / tan(time.hour / 6 * 3.1415926 + 3.1415926 / 2)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((j - oy) - (i - ox) * 1 / tan(time.hour / 6 * 3.1415926)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if (int(time.hour) % 6 != 0 && ((time.hour < 12 && time.hour>6) || (time.hour < 24 && time.hour>18)) && i - ox < 0)
				{
					if (!(time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((i - ox) - (j - oy) * 1 / tan(time.hour / 6 * 3.1415926 + 3.1415926 / 2)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((j - oy) - (i - ox) * 1 / tan(time.hour / 6 * 3.1415926)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if ((time.hour == 0 || time.hour == 12) && j - oy < 0)
				{
					if (!(time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((i - ox) - (j - oy) * 1 / tan(time.hour / 6 * 3.1415926 + 3.1415926 / 2)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((j - oy) - (i - ox) * 1 / tan(time.hour / 6 * 3.1415926)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
				if ((time.hour == 6 || time.hour == 18) && j - oy > 0)
				{
					if (!(time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((i - ox) - (j - oy) * 1 / tan(time.hour / 6 * 3.1415926 + 3.1415926 / 2)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
					else if ((time.hour == 3 || time.hour == 9 || time.hour == 15 || time.hour == 21) && fabs((j - oy) - (i - ox) * 1 / tan(time.hour / 6 * 3.1415926)) <= 2)
					{
						gotoxy(hout, int(2 * i), int(j));
						setcolor(hout, color_b, color_f);
						printf("*");
					}
				}
			}
		}
	}
}

void shuzi(int x, int y, TIME time0, int color_b, int color_f)
{
	int num[6] = { 0,0,0,0,0,0 };
	num[0] = (int)time0.hour / 10;
	num[1] = (int)time0.hour % 10;
	num[2] = (int)time0.minute / 10;
	num[3] = (int)time0.minute % 10;
	num[4] = (int)time0.second / 10;
	num[5] = (int)time0.second % 10;
	for (int i = 0; i < 2; i++)
	{
		output_CHINESE_BI("HZK16", number[num[i]], x + i * 33*2, y, color_b, color_f);
	}
	output_CHINESE_BI("HZK16","£∫", x + 2 * 33 * 2, y, color_b, color_f);
	for (int i = 2; i < 4; i++)
	{
		output_CHINESE_BI("HZK16", number[num[i]], x + i * 33 * 2+66, y, color_b, color_f);
	}
	for (int i = 4; i < 6; i++)
	{
		output_CHINESE("HZK16", number[num[i]], x + i * 16 * 2, y+32, color_b, color_f);
	}
}
 
void shuzi_sm(int x, int y, TIME time0, int color_b, int color_f)
{
	int num[6] = { 0,0,0,0,0,0 };
	num[0] = (int)time0.hour / 10;
	num[1] = (int)time0.hour % 10;
	num[2] = (int)time0.minute / 10;
	num[3] = (int)time0.minute % 10;
	num[4] = (int)time0.second / 10;
	num[5] = (int)time0.second % 10;
	for (int i = 0; i < 2; i++)
	{
		output_CHINESE("HZK16", number[num[i]], x + i * 33 * 2, y, color_b, color_f);
	}
	output_CHINESE("HZK16", "£∫", x + 2 * 33 * 2, y, color_b, color_f);
	for (int i = 2; i < 4; i++)
	{
		output_CHINESE("HZK16", number[num[i]], x + i * 33 * 2 + 66, y, color_b, color_f);
	}
}

void riqi(int x, int y, TIME time0, int color_b, int color_f)
{
	int num[8] = { 0,0,0,0,0,0 };
	num[0] = (int)time0.year / 1000;
	num[1] = (int)time0.year /100- num[0]*10;
	num[2] = (int)time0.year / 10 - num[0] * 100-num[1]*10;
	num[3] = (int)time0.year % 10;
	num[4] = (int)time0.month / 10;
	num[5] = (int)time0.month % 10;
	num[6] = (int)time0.day / 10;
	num[7] = (int)time0.day % 10;
	for (int i = 0; i < 8; i++)
		output_CHINESE("HZK16", number[num[i]], x + i * 32, y, color_b, color_f);
}