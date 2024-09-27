#include<stdio.h>
#include<string.h>
#include"供电局小区家庭.h"
//#include"表格.h"
#define xform 50
#define yform 250
//计算函数
//家庭数据计算
//计算某家庭每年每月用电量
void calFamMonthEle(Family *fam,int *famMonthEle)
{
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			*(famMonthEle+(year*12)+month) = fam->famPeak[year][month] + fam->famValley[year][month];
		}
	}
}
//绘制某家庭每年每月用电量表
void formFamMonthEle(Family* fam)
{
	gotoxy(xform, 247);
	printf("该家庭的每年每月用电量表如下：");
	int famMonthEle[2][12] = { 0 };
	calFamMonthEle(fam, famMonthEle);
	for (int i = -1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 12 * 2 + 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform + 7, yform + 2 * i - 1);
		for (int j = 1; j <= 2; j++)
		{
			gotoxy(xform +j*7, yform + 2 * i - 1);
			printf("%7d", famMonthEle[j-1][i-1]);
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%5d月", i);
	}
	gotoxy(xform + 7 * 1, yform - 1);
	printf("  2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("  2022\n");
}
//计算某家庭每年每月电费
void calFamMonthFee(Family *fam, double *famMonthFee)
{
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			*(famMonthFee+(year*12)+month)= fam->famPeak[year][month] * peakFee + fam->famValley[year][month] * valleyFee;
		}
	}
}
//绘制某家庭每年每月电费表
void formFamMonthFee(Family* fam)
{
	gotoxy(xform, 247);
	printf("该家庭的每年每月电费表如下：");
	double famMonthFee[2][12] = { 0 };
	calFamMonthFee(fam, famMonthFee);
	for (int i = -1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 12 * 2 + 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform + 7, yform + 2 * i - 1);
		for (int j = 1; j <= 2; j++)
		{
			gotoxy(xform + j * 7, yform + 2 * i - 1);
			printf("%7.1lf", famMonthFee[j - 1][i - 1]);
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%5d月", i);
	}
	gotoxy(xform + 7 * 1, yform - 1);
	printf("  2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("  2022\n");
}
//计算某家庭某年总用电量
void calFamYearTotalEle(Family *fam,int *famYearTotalEle, int *famMonthEle)
{
	calFamMonthEle(fam, famMonthEle);
	for (int year = 0; year < 2; year++)
	{
		for (int i = 0; i < 12; i++)
		{
			*(famYearTotalEle+year) += *(famMonthEle+(year*12) + i);
		}
	}
}
//绘制某家庭每年总用电量表
void formFamYearTotalEle(Family* fam)
{
	gotoxy(xform, 247);
	printf("该家庭的每年用电量表如下：");
	int famYearTotalEle[2] = { 0 };
	int famMonthEle[2][12] = { 0 };
	calFamYearTotalEle(fam, famYearTotalEle, famMonthEle);
	for (int i = -1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 3; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform + 7*i, yform + 1);
		for (int j = 0; j < 2; j++)
		{
			printf("%7d", famYearTotalEle[j]);
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i-1);
		printf("   电量");
	}
	gotoxy(xform+ 7, yform - 1);
	printf("   2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("   2022\n");
}
//计算某家庭每年总电费
void calFamYearTotalFee(Family *fam, double *famYearTotalFee, double *famMonthFee)
{
	calFamMonthFee(fam, famMonthFee);
	for (int year = 0; year < 2; year++)
	{
		for (int i = 0; i < 12; i++)
		{
			*(famYearTotalFee+year) += *(famMonthFee+year*12+i);
		}
	}
}
//绘制某家庭每年总电费表
void formFamYearTotalFee(Family* fam)
{
	gotoxy(xform, 247);
	printf("该家庭的每年总电费表如下：");
	double famYearTotalFee[2] = { 0 };
	double famMonthFee[2][12] = { 0 };
	calFamYearTotalFee(fam, famYearTotalFee, famMonthFee);
	for (int i = -1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 3; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform + 7 * i, yform + 1);
		for (int j = 0; j < 2; j++)
		{
			printf("%7.1lf", famYearTotalFee[j]);
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("   电量");
	}
	gotoxy(xform + 7, yform - 1);
	printf("   2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("   2022\n");
}

//小区数据计算

//计算某小区每月峰时用电量
void calComPeak(Community *com, int *comPeak)
{
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			Family* p = com->head;
			for (int i = 0; i < com->n; i++)
			{
				*(comPeak+year*12+month) += p->famPeak[year][month];
				p = p->next;
			}
			*(comPeak + year * 12 + month) = (*(comPeak + year * 12 + month));
		}
	}
}
//绘制某小区每月峰时用电量表
void formComPeak(Community* com)
{
	gotoxy(xform, 247);
	printf("该小区的每月峰时用电量表如下：");
	int comPeak[2][12] = { 0 };
	calComPeak(com, comPeak);
	for (int i = -1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 12 * 2 + 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform + 7, yform + 2 * i - 1);
		for (int j = 1; j <= 2; j++)
		{
			gotoxy(xform + j * 7, yform + 2 * i - 1);
			printf("%7d", comPeak[j - 1][i - 1]);
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%5d月", i);
	}
	gotoxy(xform + 7 * 1, yform - 1);
	printf("  2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("  2022\n");
}
//计算某小区每月谷时用电量
void calComValley(Community *com, int *comValley)
{
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			Family* p = com->head;
			for (int i = 0; i < com->n; i++)
			{
				*(comValley+year*12+month) += p->famValley[year][month];
				p = p->next;
			}
			*(comValley + year * 12 + month) = (*(comValley + year * 12 + month)) / 10000;
		}
	}
}
//绘制某小区每月谷时用电量表
void formComValley(Community* com)
{
	gotoxy(xform, 247);
	printf("该小区的每月谷时用电量表如下：");
	int comValley[2][12] = { 0 };
	calComValley(com, comValley);
	for (int i = -1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 12 * 2 + 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform + 7, yform + 2 * i - 1);
		for (int j = 1; j <= 2; j++)
		{
			gotoxy(xform + j * 7, yform + 2 * i - 1);
			printf("%7d", comValley[j - 1][i - 1]);
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%5d月", i);
	}
	gotoxy(xform + 7 * 1, yform - 1);
	printf("  2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("  2022\n");
}
//计算某小区每月总用电量
void calComMonthTotalEle(Community *com,int *comMonthTotalEle)
{
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			Family* p = com->head;
			for (int i = 0; i < com->n; i++)
			{
				*(comMonthTotalEle+year*12+month) += (p->famPeak[year][month]+p->famValley[year][month]);
				p = p->next;
			}
			*(comMonthTotalEle + year * 12 + month) = (*(comMonthTotalEle + year * 12 + month)) / 10000;
		}
	}
	
}
//绘制某小区每月总用电量表
void formComMonthTotalEle(Community* com)
{
	gotoxy(xform, 247);
	printf("该小区的每月总用电量表如下：");
	int comMonthTotalEle[2][12] = { 0 };
	calComMonthTotalEle(com,comMonthTotalEle);
	for (int i = -1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 12 * 2 + 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform + 7, yform + 2 * i - 1);
		for (int j = 1; j <= 2; j++)
		{
			gotoxy(xform + j * 7, yform + 2 * i - 1);
			printf("%7d", comMonthTotalEle[j - 1][i - 1]);
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%5d月", i);
	}
	gotoxy(xform + 7 * 1, yform - 1);
	printf("  2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("  2022\n");
}
//计算某小区每月总电费
void calComMonthTotalFee(Community* com, double *comMonthTotalFee)
{
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			Family* p = com->head;
			for (int i = 0; i < com->n; i++)
			{
				*(comMonthTotalFee+year*12+month) += (p->famPeak[year][month] * peakFee + p->famValley[year][month] * valleyFee);
				p = p->next;
			}
			*(comMonthTotalFee + year * 12 + month) = (*(comMonthTotalFee + year * 12 + month)) / 10000;
		}
	}
}
//绘制某小区每月总电费表格
void formComMonthTotalFee(Community *com)
{
	gotoxy(xform, yform-3);
	printf("该小区的每月总电费表如下：");
	double comMonthTotalFee[2][12] = { 0 };
	calComMonthTotalFee(com, comMonthTotalFee);
	for (int i = -1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 12 * 2 + 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform + 7, yform + 2 * i - 1);
		for (int j = 1; j <= 2; j++)
		{
			gotoxy(xform + j * 7, yform + 2 * i - 1);
			printf("%7.2lf", comMonthTotalFee[j - 1][i - 1]);
		}
	}
	for (int i = 1; i < 12 + 1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%5d月", i);
	}
	gotoxy(xform + 7 * 1, yform - 1);
	printf("  2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("  2022\n");
}
//计算某小区每年总用电量
void calComYearTotalEle(Community *com,int *comYearTotalEle,int *comMonthTotalEle)
{
	calComMonthTotalEle(com, comMonthTotalEle);
	for (int year = 0; year < 2; year++)
	{
		for (int i = 0; i < 12; i++)
		{
			*(comYearTotalEle+year) += *(comMonthTotalEle+year*12+i);
		}
		*(comYearTotalEle + year) = (*(comYearTotalEle + year)) / 10000;
	}
}
//绘制某小区每年总用电量
void formComYearTotalEle(Community* com)
{
	gotoxy(xform,yform-3);
	printf("该小区的每年总用电量表如下：");
	int comYearTotalEle[2] = { 0 };
	int comMonthTotalEle[2][12] = { 0 };
	calComYearTotalEle(com, comYearTotalEle, comMonthTotalEle);
	for (int i = -1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 3; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform + 7 * i, yform + 1);
		for (int j = 0; j < 2; j++)
		{
			printf("%7d", comYearTotalEle[j]);
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("   电量");
	}
	gotoxy(xform + 7, yform - 1);
	printf("   2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("   2022\n");
}
//计算某小区每年总电费
void calComYearTotalFee(Community *com,double *comYearTotalFee,double *comMonthTotalFee)
{
	calComMonthTotalFee(com, comMonthTotalFee);
	for (int year = 0; year < 2; year++)
	{
		for (int i = 0; i < 12; i++)
		{
			*(comYearTotalFee + year) += *(comMonthTotalFee+year*12+i);
		}
		*(comYearTotalFee + year) = (*(comYearTotalFee + year)) / 10000;
	}
}
//绘制某小区每年总电费表
void formComYearTotalFee(Community* com)
{
	gotoxy(xform, yform-3);
	printf("该小区的年总电费表如下：");
	double comYearTotalFee[2] = { 0 };
	double comMonthTotalFee[2][12] = { 0 };
	calComYearTotalFee(com, comYearTotalFee, comMonthTotalFee);
	for (int i = -1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < 3; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform + 7 * i, yform + 1);
		for (int j = 0; j < 2; j++)
		{
			printf("%7.2lf", comYearTotalFee[j]);
		}
	}
	for (int i = 1; i < 2; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("   电量");
	}
	gotoxy(xform + 7, yform - 1);
	printf("   2021");
	gotoxy(xform + 7 * 2, yform - 1);
	printf("   2022\n");
}
//计算某小区每户平均用电量
double calAverageELe(Community *com)
{
	int comYearTotalEle[2] = { 0 };
	int comMonthTotalEle[2][12] = { 0 };
	calComYearTotalEle(com, comYearTotalEle, comMonthTotalEle);
	double average;
	average= (comYearTotalEle[0]+comYearTotalEle[1]) / 2;
	printf("该小区每户每年平均用电量为：%lf", average);
	return average;
}
//计算某小区每户平均电费
double calAverageFee(Community *com)
{
	double average;
	int comYearTotalFee[2] = { 0 };
	int comMonthTotalFee[2][12] = { 0 };
	calComMonthTotalFee(com, comYearTotalFee, comMonthTotalFee);
	average = (comYearTotalFee[0] + comYearTotalFee[1]) / 2;
	printf("该小区每户每年平均电费为：%lf", average);
	return average;
}

int calComTotalPeak(Community *com)//计算某小区两年内的峰时用电总量
{
	int comPeak[2][12] = { 0 };
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			Family* p = com->head;
			for (int i = 0; i < com->n; i++)
			{
				comPeak[year][month] += p->famPeak[year][month];
				p = p->next;
			}
		}
	}
	int total = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			total += comPeak[i][j];
		}
	}
	return total;
}
int calComTotalValley(Community *com)//计算某小区两年内的谷时用电总量
{
	int comValley[2][12] = { 0 };
	for (int year = 0; year < 2; year++)
	{
		for (int month = 0; month < 12; month++)
		{
			Family* p = com->head->next;
			for (int i = 0; i < com->n; i++)
			{
				comValley[year][month] += p->famValley[year][month];
				p = p->next;
			}
		}
	}
	int total = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			total += comValley[i][j];
		}
	}
	return total;
}


//排序函数
//峰时用电量排序
void sortComPeak(Administration *adm)
{
	if (adm->head == NULL)
	{
		printf("链表为空，冒泡排序失败\n");
		return NULL;
	}
	else
	{

		Community* p = adm->head; //移动指针
		Community* q = p->next;
		int pComTotalPeak = calComTotalPeak(p);
		int qComTotalPeak = calComTotalPeak(q);
		//需要进行(n-1)次遍历,假设 3 2 1 那么第三个元素1移动到第一个位置上需要进过3-1=2轮移动  
		for (int i = 0; i < adm->n - 1; i++)
		{
			//这里不能用pMove != NULL 因为下面比较是pMove-date 与pMove-next-date比较。所以是pMove-next != NULL
			//pMove-next会比pMove先到达NULL
			while (p->next != NULL)
			{
				if (pComTotalPeak > qComTotalPeak)//两两比较,每次都把小的放到前面。然后往下移动再两两比较
				{
					//只要交换这两个节点的元素值就可以了
					char midName[20];
					strcpy_s(midName, 21,p->comName);
					strcpy_s(p->comName,21,q->comName);
					strcpy_s(q->comName,21,midName);
					int midN = p->n;
					p->n = q->n;
					q->n = midN;
					Family* midHead = p->head;
					p->head = q->head;
					q->head = midHead;
				}
				p = p->next;             //移动指针继续往下比较

			}
			//printf("第%d轮排序结束:\n",i+1);
			//Print_all_ListNode(phead);
			//每次遍历结束，pMove重新移动到链表头部,再来一轮两两比较,一共需要n-1轮两两比较
			p = adm->head;
		}
	}
}
//绘制峰时用电量排序表
void formSortComPeak(Administration* adm)
{
	gotoxy(xform, yform-3);
	printf("峰时电量排序表如下：");
	sortComPeak(adm);
	Community* p = adm->head;
	for (int i = -1; i < adm->n+1; i++)
	{
		gotoxy(xform,yform + 2 * i);
		for (int j = 0; j < 2 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3; i++)
	{
		gotoxy(xform + i * 7, yform);
		for (int j = -1; j < (adm->n+1) * 2 - 1; j++)
		{
			gotoxy(xform + i * 7, yform + j);
			printf("|");
		}
	}
	for (int i = 1; i < adm->n+1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("%7s", p->comName);
		gotoxy(xform + 7, yform + 2 * i - 1);
		printf("%7d", calComTotalPeak(p));
		p = p->next;
	}
	for (int i = 1; i < adm->n+1; i++)
	{
		gotoxy(xform, yform + 2 * i - 1);
		printf("  %d", i);
	}
	gotoxy(xform+ 1, yform - 1);
	printf("小区");
	gotoxy(xform + 7 + 1, yform - 1);
	printf("电量");
}
//每月电费总量排序
void sortComFee(Administration *adm)
{
	int year, month;
	printf("请输入该组数据的采集时间：\n年份：");
	scanf_s("%d", &year);
	printf("月份：");
	scanf_s("%d", &month);
	if (year < 2021 || year>2022 || month < 1 || month>12)//时间检查
	{
		printf("时间输入有误或超范（请输入在范围2021年1月-2022年12间的时间）\n请重新输入\n");
		sortComAverageFee(adm);
	}
	else
	{
		Community* head0 = (Community*)malloc(sizeof(Community) * 1);
		head0->next = adm->head;
		Community* p = head0->next, * pre;
		Community* r = p->next;
		p->next = NULL;
		p = r;
		while (p != NULL)
		{
			r = p->next;
			pre = head0;
			int preNextComMonthTotalFee[2][12] = { 0 };
			int pComMonthTotalFee[2][12] = { 0 };
			calComMonthTotalFee(pre->next, preNextComMonthTotalFee);
			calComMonthTotalFee(p->next, pComMonthTotalFee);
			while (pre->next != NULL && preNextComMonthTotalFee[year - 1][month - 1] < pComMonthTotalFee[year - 1][month - 1])
			{
				pre = pre->next;
				int preNextComMonthTotalFee[2][12] = { 0 };
				calComMonthTotalFee(pre->next, preNextComMonthTotalFee);
			}
			p->next = pre->next;
			pre->next = p;
			p = r;
		}
		free(head0);
	}
}
//绘制每月电费总量排序表
void formSortComFee(Administration *adm)
{
	int month;
	int year;
	printf("您想要哪一年，几月份的小区电费总量排序表？请输入一个年份和月份（例：2022.2)");
	scanf_s("%d.%d", &year,&month);
	sortComFee(adm, year, month);
	Community* head0 = (Community*)malloc(sizeof(Community) * 1);
	head0->next = adm->head;
	Community* p = head0->next, * pre;
	gotoxy(xform, 527);
	printf("每月电量排序表如下：");
	for (int i = -1; i < adm->n + 1; i++)
	{
		gotoxy(xform, 530 + 2 * i);
		for (int j = 0; j < 3 * 7; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 7, 530);
		for (int j = -1; j < (adm->n+1) * 2 - 1; j++)
		{
			gotoxy(xform + i * 7, 530 + j);
			printf("|");
		}
	}
	for (int i = 1; i < adm->n + 1; i++)
	{
		gotoxy(xform + 7, 530 + 2 * i - 1);
		printf("%7s", p->comName);
		gotoxy(xform + 7 * 2, 530 + 2 * i - 1);
		int monthFee[2][12] = { 0 };
		calComMonthTotalFee(p, monthFee);
		printf("%7d", monthFee[year-2021][month-1]);
		p = p->next;
	}
	for (int i = 1; i < adm->n+1; i++)
	{
		gotoxy(xform,530 + 2 * i - 1);
		printf("  %d", i);
	}
	gotoxy(xform + 7 + 1, 530 - 1);
	printf("%小区");
	gotoxy(xform + 7 * 2 + 1, 530 - 1);
	printf("电费");
	free(head0);
}
//小区每户平均电量排序
void sortComAverageEle(Administration *adm)
{
	Community* head0 = (Community*)malloc(sizeof(Community) * 1);
	head0->next = adm->head;
	Community* p = head0->next, * pre;
	Community* r = p->next;
	p->next = NULL;
	p = r;
	while (p != NULL)
	{
		r = p->next;
		pre = adm->head;
		int preNextAverageEle = calAverageELe(pre->next);
		int pAverageEle = calAverageELe(p);
		while (pre->next != NULL && preNextAverageEle<pAverageEle)
		{
			pre = pre->next;
			int preNextAverageEle = calAverageELe(pre->next);
		}
		p->next = pre->next;
		pre->next = p;
		p = r;
	}
}
//绘制小区每户平均电量排序表
void formSortComAverageEle(Administration* adm)
{
	gotoxy(xform, 447);
	printf("该家庭的每年每月用电量表如下：");
	sortComAverageEle(adm);
	Community* head0 = (Community*)malloc(sizeof(Community) * 1);
	head0->next = adm->head;
	Community* p = head0->next, * pre;
	for (int i = -1; i < adm->n+1; i++)
	{
		gotoxy(xform, 450 + 2 * i);
		for (int j = 0; j < 3 * 10; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 10, 450);
		for (int j = -1; j < (adm->n+1) * 2 - 1; j++)
		{
			gotoxy(xform + i * 10, 450 + j);
			printf("|");
		}
	}
	for (int i = 1; i < adm->n+1; i++)
	{
		gotoxy(xform + 10, 450 + 2 * i - 1);
		printf("%7s   ", p->comName);
		gotoxy(xform + 10 * 2, 450 + 2 * i - 1);
		printf("%10lf", calAverageELe(p));
	}
	for (int i = 1; i < adm->n+1; i++)
	{
		gotoxy(xform, 450 + 2 * i - 1);
		printf("    %d", i);
	}
	gotoxy(xform + 10 + 1, 450 - 1);
	printf("  小区");
	gotoxy(xform + 10 * 2 + 1, 450 - 1);
	printf("平均电量");
	free(head0);
}
//每户平均电费排序
void sortComAverageFee(Administration *adm)
{
	Community* head0 = (Community*)malloc(sizeof(Community) * 1);
	head0->next = adm->head;
	Community* p = head0->next, * pre;
	Community* r = p->next;
	p->next = NULL;
	p = r;
	while (p != NULL)
	{
		r = p->next;
		pre = head0;
		double preNextAverageFee = calAverageFee(pre->next);
		double pAverageFee = calAverageFee(p);
		while (pre->next != NULL && preNextAverageFee<pAverageFee)
		{
			pre = pre->next;
			double preNextAverageFee = calAverageFee(pre->next);
		}
		p->next = pre->next;
		pre->next = p;
		p = r;
	}
	free(head0);
}
//绘制小区每户平均电费排序表
void formSortComAverage(Administration* adm)
{
	gotoxy(xform, 487);
	printf("该家庭的每年每月用电量表如下：");
	sortComAverageFee(adm);
	Community* head0 = (Community*)malloc(sizeof(Community) * 1);
	head0->next = adm->head;
	Community* p = head0->next, * pre;
	for (int i = -1; i < adm->n + 1; i++)
	{
		gotoxy(xform, 490 + 2 * i);
		for (int j = 0; j < 3 * 10; j++)
		{
			printf("_");
		}
	}
	for (int i = 0; i < 3 + 1; i++)
	{
		gotoxy(xform + i * 10, 490);
		for (int j = -1; j < (adm->n + 1) * 2 - 1; j++)
		{
			gotoxy(xform + i * 10, 490 + j);
			printf("|");
		}
	}
	for (int i = 1; i < adm->n + 1; i++)
	{
		gotoxy(xform + 10, 490 + 2 * i - 1);
		printf("%7s   ", p->comName);
		gotoxy(xform + 10 * 2, 490 + 2 * i - 1);
		printf("%10lf", calAverageFee(p));
	}
	for (int i = 1; i < adm->n + 1; i++)
	{
		gotoxy(xform, 490 + 2 * i - 1);
		printf("    %d", i);
	}
	gotoxy(xform + 10 + 1, 490 - 1);
	printf("  小区");
	gotoxy(xform + 10 * 2 + 1, 490 - 1);
	printf("平均电费");
	free(head0);
}
Community* findCommunity(Administration *adm)//找小区
{
	char goal[20];
	char f[20];
	int y = 0;//验证是否找到
	printf("请输入小区名：");
	scanf_s("%s", goal,20);
	Community* p = adm->head;
	for (int i = 0; i < adm->n; i++)
	{
		if (strcmp(goal,p->comName)==0)
		{
			y = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (y == 1)
	{
		return p;
	}
	else
	{
		printf("无该小区\n");
		system("puase");
		return NULL;
	}
}
Family* findFamily(Community* com)//找家庭
{
	char goal[20];
	int y = 0;//验证是否找到
	printf("请输入家庭名：");
	scanf_s("%s", goal,20);
	Family* p = com->head;
	for (int i = 0; i < com->n; i++)
	{
		if (strcmp(goal,p->famName)==0)
		{
			y = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (y == 1)
	{
		return p;
	}
	else
	{
		printf("无该家庭\n");
		return NULL;
	}
}
//计算小区两年的总用电量
int calComTotalEle(Community* com)
{
	int comYearTotalEle[2] = { 0 };
	int comMonthTotalEle[2][12] = { 0 };
	calComYearTotalEle(com, comYearTotalEle, comMonthTotalEle);
	int total = 0;
	for (int i = 0; i < 2; i++)
	{
		total += comYearTotalEle[i];
	}
	return total;
}
//列出优先扩容的小区建议名单
void FindKuoRongCommunity(Administration* adm)
{
	Community* head0 = (Community*)malloc(sizeof(Community) * 1);
	head0->next = adm->head;
	head0->n = 0;
	Community* p = head0->next, * pre;
	Community* r = p->next;
	p->next = NULL;
	p = r;
	while (p != NULL)
	{
		r = p->next;
		pre = head0;
		int preNextComTotalPeak = calComTotalEle(pre->next);
		int pComTotalPeak = calComTotalEle(p);
		while (pre->next != NULL && preNextComTotalPeak < pComTotalPeak)
		{
			pre = pre->next;
			preNextComTotalPeak = calComTotalPeak(pre->next);
		}
		p->next = pre->next;
		pre->next = p;
		p = r;
	}
	p = head0->next;
	for (int i = 0; i < adm->n - adm->kn; i++)
	{
		if (p->next != NULL)
		{
			p = p->next;
		}
	}
	printf("以下为扩容小区名单：\n");
	while (p != NULL)
	{
		printf("%s\n", p->comName);
		p = p->next;
	}
	free(head0);
}
