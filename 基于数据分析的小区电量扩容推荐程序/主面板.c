//        
//                  电子佛驱仿生bug
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                       0\ = / 0
//                    ___ / `---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .' / --.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='


#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
#include"供电局小区家庭.h"
#include"文件的写入写出.h"
#include"初始化.h"
#include"表格.h"
//#define filePath "D:\\卓面\\基于数据分析的小区电量扩容推荐程序 - 2.0\\用户数据.dat"			//一定记得加引号！！！！！！！~！


void MyCls(HANDLE) ;
inline void clrscr(void)
{
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
MyCls(hStdOut);
return;
}
void MyCls(HANDLE hConsole)
{
COORD coordScreen={0,0};//设置清屏后光标返回的屏幕左上角坐标
BOOL bSuccess;
DWORD cCharsWritten;
CONSOLE_SCREEN_BUFFER_INFO csbi;//保存缓冲区信息
DWORD dwConSize;//当前缓冲区可容纳的字符数
bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//获得缓冲区信息
PERR(bSuccess,"GetConsoleScreenBufferInfo");
dwConSize=csbi.dwSize.X * csbi.dwSize.Y;//缓冲区容纳字符数目
//用空格填充缓冲区
bSuccess=FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
PERR(bSuccess,"FillConsoleOutputCharacter");
bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//获得缓冲区信息
PERR(bSuccess,"ConsoleScreenBufferInfo");
//填充缓冲区属性
bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
PERR(bSuccess,"FillConsoleOutputAttribute");
//光标返回屏幕左上角坐标
bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);
PERR(bSuccess,"SetConsoleCursorPosition");
return;
}


void menu();
void menuA();
void menuB();
void menuAA();
void menuAB();
void menuBA();
void fmenuA(Administration* adm);
void fmenuB(Administration* adm);
void fmenuAA(Administration* adm);//上面这坨是丑陋的菜单函数
void fmenuAB(Administration* adm);
void fmenuBA(Administration* adm);
void fmenuBAB(Family *fam);
void fmenuBAA(Community *com);
void menuBAA();
void menuBAB();
void fmenuAAA(Community *com);
void menuAAA();
void fmenuAAB(Administration *adm);
void fmenuABA(Administration *adm);
void fmenuABB(Administration* adm);
void WindowC(int startX, int startY, int width, int height);
void WindowM(int startX, int startY, int width, int height);
void WindowL(int startX, int startY, int width, int height);
void tan();
void back();


/*void fmenuBB();//从这
//到这是需要填充的具体函数，详见图*/
int main()
{
	int choice;
	Administration* adm=buildAdministration();
	FILE* fp;
	while (1)
	{
		errno_t err = fopen_s(&fp, filePath, "r");
		if (err)
		{
			printf("文件打开失败menu\n尝试新建文件\n");
			if ((err = fopen_s(&fp, filePath, "w"))==0)
			{
				fclose(fp);
				admWriteIn(adm);
			}
		}
		else
		{
			fclose(fp);
			admReadFile(adm);
			break;
		}
	}/*文件读出*/
	do
	{
		gotoxy(0, 0);
		system("cls");
		menu();                    /*显示开始菜单*/
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 2)
			switch (choice)
			{
			case 1:

				fmenuA(adm);             /* 1. 显示用电数据统计员菜单*/
				break;
			case 2:
				fmenuB(adm);    /* 2. 基本信息管理*/
				break;

			case 0:  break;
			}    /*选择开始菜单对应的功能*/
		else
			printf("错误！请重新输入。\n");
	} while (choice);
	admWriteIn(adm);
	free(adm);
	return 0;
}
//选择 用电数据统计员 的函数
void fmenuA(Administration* adm)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");
		menuA();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 2)
			switch (choice)
			{
			case 1:
				fmenuAA(adm);
				break;
			case 2:
				fmenuAB(adm);
				break;

			case 0:  break;
			}
		else
		{
			printf("错误！请重新输入。\n");
			system("puase");
		}
	} while (choice);
}
//选择 供电公司工作人员 的函数
void fmenuAA(Administration* adm)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");

		menuAA();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
			switch (choice)
			{
			case 1:
			{
				Community* goal = findCommunity(adm);
				if (goal != NULL)
					fmenuAAA(goal); // 选择小区 的函数          
				system("pause");
				break;
			}
				
			case 2:
			{
				initAdministration(adm); //添加新小区 的函数
				break;
			}
			case 3:
			{
				while (1)
				{
					char name[20];
					int check = 0;
					Community* p = adm->head;
					printf("请输入新录入小区的名字：");
					scanf_s("%s", name, 20);
					for ( int i = 0; i < adm->n; i++)
					{
						if (strcmp(name, p->comName) == 0)
						{
							printf("该小区名已被占用，请重新输入！\n");
							check++;
						}
						else
							p = p->next;
					}
					if (check == 0)
					{
						autoBuildCommunity(adm, name);
						printf("小区%s新建成功\n现有小区%d个\n", name, adm->n);
						system("pause");
						break;
					}
				}
			}
			case 0:  break;
			}
		else
		{
			system("puase");
			printf("错误！请重新输入。\n");
		}
	} while (choice);
}
//选择 在已有小区内进行家庭操作
void fmenuAAA(Community *com)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");
		menuAAA();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
			switch (choice)
			{
			case 1://向已有家庭加数据
			{
				Family* fam1;
				fam1 = findFamily(com);
				if (fam1 == NULL)
					break;
				addDate(fam1);
				break;
			}
			case 2://加入新家庭
			{
				initCommunity(com);
				break;
			}
			case 3://自动添加谋家庭数据（覆盖）
			{
				Family* fam1;
				fam1 = findFamily(com);
				if (fam1 == NULL)
					break;
				autoAddDate(fam1);
				break;
			}
			case 0:  break;
			}
		else
		{
			system("puase");
			printf("错误！请重新输入。\n");
		}
	} while (choice);
}

void fmenuAAB(Administration *adm)
{
	Community* newcom = buildCommunity(adm);
	Community* p = adm->head;
	while (1)
	{
		if (p->next != NULL)
			p = p->next;
		else
			break;
		p = newcom;
	}
}

//选择 查看统计报表 的函数
void fmenuAB(Administration* adm)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");
		menuAB();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 2)
			switch (choice)
			{
			case 1:
				fmenuABA(adm);
				/* //计算家庭统计报表的函数   */         
				break;
			case 2:
				fmenuABB(adm);
				/*; //计算小区统计报表的函数  */ 
				break;

			case 0:  break;
			}
		else
		{
			printf("错误！请重新输入。\n");
			system("puase");
		}
	} while (choice);
}

void fmenuABA(Administration *adm)
{
	Community* com = findCommunity(adm);
	int choice;
	if (com==NULL)
		system("pause");
	else 
	{
		Family* fam = findFamily(com);
		if(fam==NULL)
			system("pause");
		else 
		{
			do
			{
				gotoxy(0, 0);
				system("cls");
				menuBAB();
				scanf_s("%d", &choice);
				if (choice >= 0 && choice <= 4)
				{
					switch (choice)
					{
					case 1:
					{
						clrscr();
						printf("家庭月总用电量表：\n");
						formFamMonthEle(fam);
						//gotoxy(0,getMaxxy)
						break;
					}
					case 2:
					{
						clrscr();
						printf("家庭月总电费表：\n");
						formFamMonthFee(fam);
						break;
					}
					case 3:
						clrscr();
						printf("家庭年总电量表：\n");
						formFamYearTotalEle(fam);
						break;
					case 4:
						clrscr();
						printf("家庭年总电费：\n");
						formFamYearTotalFee(fam);
						break;
					case 0:  break;
					}
					system("pause");
				}
				else
				{
					printf("错误！请重新输入。\n");
					system("puase");
				}
			} while (choice);
		}
	}
}

void fmenuABB(Administration* adm)
{
	Community* com = findCommunity(adm);
	if (com == NULL)
	{
		printf("查找失败，无该小区");
		system("pause");
	}
	else
	{
		int choice;
		do
		{
			gotoxy(0, 0);
			system("cls");
			menuBAA();
			scanf_s("%d", &choice);
			if (choice >= 0 && choice <= 6)
			{
				switch (choice)
				{
				case 1:
					clrscr();
					printf("小区峰时电量表：\n");
					formComPeak(com);

					break;
				case 2:
					clrscr();
					printf("小区谷时电量表：\n");
					formComValley(com);

					break;

				case 3:
					clrscr();
					printf("小区月总用电量表：\n");
					formComMonthTotalEle(com);
					break;

				case 4:
					clrscr();
					printf("小区月总电费表：\n");
					formComMonthTotalFee(com);
					break;
				case 5:
					clrscr();
					printf("小区年总用电量表：\n");
					formComYearTotalEle(com);
					break;
				case 6:
					clrscr();
					printf("小区年总电费表：\n");
					formComYearTotalFee(com);

					break;
				case 0:  break;
				}
				system("pause");
			}
			else
			{
				printf("错误！请重新输入。\n");
				system("puase");
			}
		} while (choice);
	}
}

void fmenuB(Administration* adm)
{
	int choice;
	do
	{
		clrscr();
		gotoxy(0, 0);
		//system("cls");
		menuB();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
			switch (choice)
			{
			case 1:
				fmenuBA(adm);     //查询用电数据  */      
				break;
			case 2:
			{
				printf("请输入扩容小区需求数量：");
				scanf_s("%d", &adm->kn);
				break;
			}
			case 3:
				FindKuoRongCommunity(adm);
				system("pause");
				break;
			case 0:  break;
			}
		else
		{
			printf("错误！请重新输入。\n");
			system("puase");
		}
			system("cls");
	} while (choice);
}

//选择 查询用电数据 的函数
void fmenuBA(Administration* adm)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");
		menuBA();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 3)
		{
			switch (choice)
			{
			case 1:
			{
				Community* goal = findCommunity(adm);
				if (goal == NULL)
					system("pause");
				else
					fmenuBAA(goal);
				/*       //查询小区数据*/
				break;
			}
			case 2:
			{
				Community* goal = findCommunity(adm);
				if (goal == NULL)
					system("pause");
				else
				{
					Family* goal2 = findFamily(goal);
					if (goal2 == NULL)
						system("pause");
					else
						fmenuBAB(goal2);
					/*      //查询家庭数据*/
				}
				break;
}
			case 3:
				FindKuoRongCommunity(adm);
				/*;*/
				break;

			case 0:  break;
			}
		}
		else
		{
			printf("错误！请重新输入。\n");
			system("puase");
		}
	} while (choice);
}

void fmenuBAA(Community *com)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");
		menuBAA();
		scanf_s("%d", &choice);
		
		if (choice >= 0 && choice <= 6)
		{
			switch (choice)
			{
			case 1:
				clrscr();
				printf("小区峰时电量表：\n");
				formComPeak(com);

				break;
			case 2:
				clrscr();
				printf("小区谷时电量表：\n");
				formComValley(com);

				break;

			case 3:
				clrscr();
				printf("小区月总用电量表：\n");
				formComMonthTotalEle(com);
				break;

			case 4:
				clrscr();
				printf("小区月总电费表：\n");
				formComMonthTotalFee(com);
				break;
			case 5:
				clrscr();
				printf("小区年总用电量表：\n");
				formComYearTotalEle(com);
				break;
			case 6:
				clrscr();
				printf("小区年总电费表：\n");
				formComYearTotalFee(com);

				break;
			case 0:  break;
			}
			system("pause");
		}
		else
		{
			printf("错误！请重新输入。\n");
			system("puase");
		}
		} while (choice);
}

void fmenuBAB(Family *fam)
{
	int choice;
	do
	{
		gotoxy(0, 0);
		system("cls");
		menuBAB();
		scanf_s("%d", &choice);
		if (choice >= 0 && choice <= 4)
		{
			switch (choice)
			{
			case 1:
			{
				clrscr();
				printf("家庭月总用电量表：\n");
				formFamMonthEle(fam);
				break;
			}
			case 2:
			{
				clrscr();
				printf("家庭月总电费表：\n");
				formFamMonthFee(fam);
				break;
			}
			case 3:
				clrscr();
				printf("家庭年总电量表：\n");
				formFamYearTotalEle(fam);
				break;
			case 4:
				clrscr();
				printf("家庭年总电费：\n");
				formFamYearTotalFee(fam);
				break;
			case 0:  break;
			}
			system("pause");
		}
		else
		{
			printf("错误！请重新输入。\n");
			system("puase");
		}
		} while (choice);
}

void WindowC(int startX, int startY, int width, int height)    //画弯曲框函数，形参分别为，框的左上角的横纵坐标
{                                                              //框的宽度 框的高度
	int i = 0, j = 0;
	//画顶
	gotoxy(startX, startY);
	printf("╭");
	for (i = 0; i < width; i++)
	{
		printf("━");
	}
	printf("╮");
	//左
	for (i = 0; i < height; i++)
	{
		gotoxy(startX, startY + 1 + i);
		printf("┃");
	}
	//右
	for (i = 0; i < height; i++)
	{
		gotoxy(startX + 1 + width, startY + 1 + i);
		printf("┃");
	}
	//底
	gotoxy(startX, startY + 1 + height);
	printf("╰");
	gotoxy(startX + 2, startY + 1 + height);
	for (i = 0; i <= width - 2; i++)
	{
		printf("━");
	}
	printf("╯");
	gotoxy(0, 0);

}
void WindowM(int startX, int startY, int width, int height)  //
{
	int i = 0, j = 0;
	//画顶
	gotoxy(startX, startY);
	printf("·");
	for (i = 0; i < width; i++)
	{
		printf("-");
	}
	printf("·");

	//底
	gotoxy(startX, startY + 1 + height);
	printf("·");
	gotoxy(startX + 2, startY + 1 + height);
	for (i = 0; i <= width - 2; i++)
	{
		printf("-");
	}
	printf("·");
	gotoxy(0, 0);

}
void WindowL(int startX, int startY, int width, int height)  //画直框函数  形参分别为，框的左上角的横纵坐标 框的宽度 框的高度
{
	int i = 0, j = 0;
	//画顶
	gotoxy(startX, startY);
	printf("┏");
	for (i = 0; i < width; i++)
	{
		printf("━");
	}
	printf("┓");
	//左
	for (i = 0; i < height; i++)
	{
		gotoxy(startX, startY + 1 + i);
		printf("┃");
	}
	//右
	for (i = 0; i < height; i++)
	{
		gotoxy(startX + 1 + width, startY + 1 + i);
		printf("┃");
	}
	//底
	gotoxy(startX, startY + 1 + height);
	printf("┗");
	gotoxy(startX + 2, startY + 1 + height);
	for (i = 0; i <= width - 2; i++)
	{
		printf("━");
	}
	printf("┛");
	gotoxy(0, 0);

}

void tan()
{
	gotoxy(7, 3);
	printf("◤");
	gotoxy(84, 3);
	printf("◥");
	gotoxy(7, 32);
	printf("◣");
	gotoxy(84, 32);
	printf("◢");
}
void back()
{
	gotoxy(7, 4);
	printf("←按“0”返回");
}




void menu()         /*开始菜单函数*/
{
	tan();
	gotoxy(28, 8);
	printf("【基于数据分析的小区电量扩容推荐程序】");
	gotoxy(28, 6);
	WindowL(5, 2, 80, 30);
	WindowC(31, 15, 20, 1);
	WindowC(31, 19, 20, 1);
	gotoxy(36, 13);
	printf("请选择你的身份：");
	gotoxy(33, 16);
	printf("1.用电数据统计员");
	gotoxy(33, 20);
	printf("2.供电公司管理员");
	gotoxy(33, 24);
	printf("制作人：吴思弈 李致远 杨洋");
	gotoxy(2, 34);

}

void menuA()     /*2、用电数据统计员菜单函数*/
{
	WindowL(5, 2, 80, 30);//外框的绘制
	tan();
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【用电数据统计员】");
	WindowC(31, 15, 20, 1);
	WindowC(31, 19, 20, 1);
	WindowM(25, 24, 30, 5);
	gotoxy(31, 13);
	printf("请选择你要进行的操作：");
	gotoxy(31, 9);
	printf("（按“0”重新选择身份）");
	gotoxy(33, 16);
	printf("1.录入用电数据");
	gotoxy(33, 20);
	printf("2.查看统计报表");
	gotoxy(29, 26);
	printf("测电千万条，安全第一条！");
	gotoxy(29, 28);
	printf("查表不规范，亲人两行泪！");
	gotoxy(2, 34);

}

void menuB()     /*3、供电公司管理员菜单函数*/
{
	WindowL(5, 2, 80, 34);
	gotoxy(7, 3);
	printf("◤");
	gotoxy(84, 3);
	printf("◥");
	gotoxy(7, 36);
	printf("◣");
	gotoxy(84, 36);
	printf("◢");
	gotoxy(24, 3);
	
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【供电公司管理员】");
	WindowC(31, 15, 20, 1);
	WindowC(31, 19, 20, 1);
	WindowC(31, 23, 20, 1);
	WindowM(23, 29, 34, 5);
	gotoxy(31, 13);
	printf("请选择你要进行的操作：");
	gotoxy(31, 9);
	printf("（按“0”重新选择身份）");
	gotoxy(33, 16);
	printf("1.查询用电数据");
	gotoxy(33, 20);
	printf("2.分析优先扩容名单");
	gotoxy(33, 24);
	printf("3.输出扩容小区名单");
	gotoxy(25, 32);
	printf("保证配电装置安全、可靠、连续、合格！");
	gotoxy(2, 40);

}

void menuAA()    /*4、录入用电数据菜单函数*/
{
	WindowL(5, 2, 80, 34);
	back();
	gotoxy(7, 3);
	printf("◤");
	gotoxy(84, 3);
	printf("◥");
	gotoxy(7, 36);
	printf("◣");
	gotoxy(84, 36);
	printf("◢");
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【用电数据统计员】");
	WindowC(31, 15, 20, 1);
	WindowC(31, 19, 20, 1);
	WindowC(31, 23, 20, 1);
	WindowM(23, 28, 34, 5);
	gotoxy(31, 13);
	printf("请选择你要进行的操作：");
	gotoxy(31, 9);
	printf("→录入用电数据");
	gotoxy(33, 16);
	printf("1.选择已有小区");
	gotoxy(33, 20);
	printf("2.添加新小区");
	gotoxy(33, 24);
	printf("3.自动新建小区");
	gotoxy(29, 30);
	printf("谨慎、客观、公平、公正！");
	gotoxy(29, 34);
	printf("不弄虚作假、不主观臆断！");
	gotoxy(2, 38);

}

void menuAB()    /*5、查看统计报表菜单函数*/
{
	WindowL(5, 2, 80, 30);
	back();
	tan();
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【用电数据统计员】");
	WindowC(31, 15, 20, 1);
	WindowC(31, 19, 20, 1);
	WindowM(23, 24, 34, 5);
	gotoxy(31, 13);
	printf("请选择你要查询的数据：");
	gotoxy(31, 9);
	printf("→查看统计报表");
	gotoxy(33, 16);
	printf("1.查看家庭统计报表");
	gotoxy(33, 20);
	printf("2.查看小区统计报表");
	gotoxy(29, 26);
	printf("谨慎、客观、公平、公正！");
	gotoxy(29, 28);
	printf("不弄虚作假、不主观臆断！");
	gotoxy(2, 34);

}

void menuBA()    /*6、查询用电数据菜单函数*/
{
	WindowL(5, 2, 80, 30);
	back();
	tan();
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【供电公司管理员】");
	WindowC(31, 15, 20, 1);
	WindowC(31, 19, 20, 1);
	WindowM(23, 24, 34, 5);
	gotoxy(31, 13);
	printf("请选择你要查询的数据：");
	gotoxy(31, 9);
	printf("→查询用电数据");
	gotoxy(33, 16);
	printf("1.查询小区数据");
	gotoxy(33, 20);
	printf("2.查询家庭数据");
	gotoxy(24, 27);
	printf("满足广大客户经济建设和生活用电的需要！");
	gotoxy(2, 34);

}

void menuBAA()
{
	WindowL(5, 2, 80, 38);
	back();
	gotoxy(7, 3);
	printf("◤");
	gotoxy(84, 3);
	printf("◥");
	gotoxy(7, 40);
	printf("◣");
	gotoxy(84, 40);
	printf("◢");
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【供电公司管理员】");
	WindowC(31, 15, 21, 1);
	WindowC(31, 19, 21, 1);
	WindowC(31, 23, 21, 1);
	WindowC(31, 27, 21, 1);
	WindowC(31, 31, 21, 1);
	WindowC(31, 35, 22, 1);
	gotoxy(31, 13);
	printf("请选择你要查询的数据：");
	gotoxy(31, 9);
	printf("→查询小区数据");
	gotoxy(33, 16);
	printf("1.查询小区峰时用电量");
	gotoxy(33, 20);
	printf("2.查询小区谷时用电量");
	gotoxy(33, 24);
	printf("3.查询小区月用电量");
	gotoxy(33, 28);
	printf("4.查询小区月总电费");
	gotoxy(33, 32);
	printf("5.查询小区年总电量");
	gotoxy(33, 36);
	printf("6.查询小区年总电费表");

	gotoxy(2, 34);
}

void menuBAB()
{
	WindowL(5, 2, 80, 30);
	back();
	tan();
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【供电公司管理员】");
	WindowC(31, 15, 21, 1);
	WindowC(31, 19, 21, 1);
	WindowC(31, 23, 21, 1);
	WindowC(31, 27, 21, 1);
	

	gotoxy(31, 13);
	printf("请选择你要查询的数据：");
	gotoxy(31, 9);
	printf("→查询家庭数据");
	gotoxy(33, 16);
	printf("1.查询家庭某月用电量");
	gotoxy(33, 20);
	printf("2.查询家庭某月电费");
	gotoxy(33, 24);
	printf("3.查询家庭某年电量");
	gotoxy(33, 28);
	printf("4.查询家庭某年电费");
	

	gotoxy(2, 34);
}


//void menuBAB()
//{
//	printf("######## 1. 查询家庭某月用电量   ########\n");
//	printf("######## 2. 查询家庭某月电费   ########\n");
//	printf("######## 3. 查询家庭某年电量   ########\n");
//	printf("######## 4. 查询家庭某年电费   ########\n");
//	printf("######## 0. 返回上层菜单   ########\n");
//}

void menuAAA()
{
	WindowL(5, 2, 80, 30);
	back();
	tan();
	gotoxy(31, 9);
	printf("→添加家庭数据");
	gotoxy(24, 3);
	printf("----基于数据分析的小区电量扩容推荐程序-----");
	gotoxy(28, 8);
	printf("您当前身份为：【用电数据统计员】");
	WindowC(31, 15, 23, 1);
	WindowC(31, 19, 15, 1);
	WindowC(31, 23, 25, 1);
	gotoxy(31, 13);
	printf("请选择你要进行的操作：");
	gotoxy(33, 16);
	printf("1.向已有家庭中加入数据 ");
	gotoxy(33, 20);
	printf("2.新建新家庭");
	gotoxy(33, 24);
	printf("3.向已有家庭自动添加数据");
	gotoxy(2, 34);
}

/*int mai()
{
	int choice;
	Administration* adm = buildAdministration();
	FILE* fp;
	while (1)
	{
		errno_t err = fopen_s(&fp, filePath, "r");
		if (err)
		{
			printf("文件打开失败menu\n尝试新建文件\n");
			if ((err = fopen_s(&fp, filePath, "w")) == 0)
			{
				fclose(fp);
				admWriteIn(adm);
			}
		}
		else
		{
			fclose(fp);
			admReadFile(adm);
			break;
		}
	}//文件读出
	printf("%p\n", adm);
	printf("%p\n", adm->head);
	printf("%d\n", adm->n);
	printf("%s\n", adm->head->comName);//310de
	printf("%d\n", adm->head->n);
	printf("%s\n", adm->head->next->comName);//311的户个数
	printf("%d\n", adm->head->next->n);
	printf("%s\n", adm->head->head->famName);
	printf("%s\n", adm->head->head->next->famName);
}*/

int mai()
{
	//srand((unsigned int)time(0));
	//int rand_number = rand() % 150 + 50;
	//printf("%d\n", rand_number);

	//Community* com1 = (Community*)malloc(sizeof(Community) * 1);
	//com1->n = 20;
	//autoBuildFamily(com1);
	//formComMonthTotalEle(com1);

	Family* fam=(Family*)malloc(sizeof(Family)*1);
	autoAddDate(fam);
	formFamMonthEle(fam);
	free(fam);
}