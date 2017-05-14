/*1650254 尤尧寅 计算机一班*/
#include"90-b3.h"
int clock_main()
{
	system("cls");
	setfontsize(hout, L"点阵字体", 1);
	int MODE = 1;//数字和表面切换
	int set[2] = { 0,0 };//输入字符
	int set_mode = 0;//主菜单
	int mode_next = 0;//是否在二级菜单
	int next = 0;//副菜单项数
	int timezone = 0;//目前时区
	int timezone_num = 1;
	timezone = time_zone_update(timezone_num);
	BASIC basic;
	get_from_document(&basic);
	TIME time0;
	get_time(&time0,basic.localtime - timezone);
	TIME temp = time0;
	int music=0;
	int if_show = 1;
	show_menu(&set_mode, mode_next, &next,basic.CHINESE, basic.backcolor, basic.frontcolor);
	output_CHINESE(basic.CHINESE, "按左箭头键退回上一菜单", 100, 200, basic.backcolor, basic.frontcolor);
	char area[15];
	time_zone_name_update(timezone_num, area);
	output_CHINESE(basic.CHINESE, area, 500, 100, basic.backcolor, basic.frontcolor);
	riqi(420, 120, time0,basic.backcolor, basic.frontcolor);
	while (1)
	{
		get_time(&time0, basic.localtime-timezone);
		if (time0.second != temp.second)
		{
			if (time0.minute != temp.minute&&time0.second == 0)
			{
				judge_alarm(time0, &music);
			}
			if (MODE == 1)
				circle(102, 50, 100, time0, basic.backcolor, basic.frontcolor);
			else
				shuzi(100, 80, time0, basic.backcolor, basic.frontcolor);
			temp = time0;
		}
		if (time0.day != temp.day)
		{
			if (time0.second != temp.second)
			{
				riqi(420, 120, time0, basic.backcolor, basic.frontcolor);
				temp = time0;
			}
		}
		if (_kbhit())
		{
			set[0] = _getch();
			if (set[0] == 224)
			{
				set[1] = _getch();
				if (music == 1)
				{
					music = 0;
					PlaySound(NULL, NULL, NULL);
				}
				else 
				{
					if (mode_next == 0)
						judge_input(set, &set_mode, &mode_next);
					else
					{
						judge_input(set, &next, &mode_next);
						if (next > 2)
							next = 2;
					}
				}
			}
			if (music == 1)
			{
				PlaySound(NULL, NULL, NULL);
				music = 0;
			}
			else
			{
				if (set[0] == '\r')
				{
					exchange_mode(set_mode, &MODE, &mode_next, &next, &timezone_num,&if_show);
					get_from_document(&basic);
					timezone=time_zone_update(timezone_num);
					time_zone_name_update(timezone_num, area);
					if(if_show==1)
						output_CHINESE(basic.CHINESE, area, 500, 100, basic.backcolor, basic.frontcolor);
				}
			}
			show_menu(&set_mode, mode_next, &next, basic.CHINESE, basic.backcolor, basic.frontcolor);
			output_CHINESE(basic.CHINESE, "按左箭头键退回上一菜单", 100,200, basic.backcolor, basic.frontcolor);
			riqi(420, 120, time0, basic.backcolor, basic.frontcolor);
		}
	}
}
int main()

{
	system("cls");
	if (origin_setbasic_data() == END)
		return END;
	clock_main();
	system("pause");
	return 0;
}