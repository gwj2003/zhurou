#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define filePath "用户数据.dat"			//一定记得加引号！！！！！！！~！
#define startyear 2021
#pragma once
#define peakFee 0.54
#define valleyFee 0.36
typedef struct family		//家庭类
{
	char famName[20];		//家庭名
	int famPeak[2][12];		//家庭每月峰时用电量
	int famValley[2][12];	//家庭每月谷时用电量
	int num;//第几户人家，可理解为地址，从1开始到最后
	struct family* next;	//链表指针
}Family;

typedef struct community	//小区类(节点)
{
	Family* head;           //家庭之指针
	char comName[20];		//小区名
	int n;					//家庭数
	struct community* next;	//链表指针
}Community;

typedef struct administration
{
	Community* head;//供电局管辖的小区之指针
	int n;//小区数目
	int kn;//扩容小区数目（默认0，通过选择BB输入）
}Administration;


//取值函数
//初始化50户家庭
//void inputFamMonth(Family fam, int year, int month);//取得某家庭某月峰时、谷时用电量
//计算函数
//家庭数据计算
void calFamMonthEle(Family *fam, int* famMonthEle);//计算某家庭每年每月用电量
void calFamMonthFee(Family *fam, double* famMonthFee);//计算某家庭每年每月电费
void calFamYearTotalEle(Family* fam, int* famYearTotalEle, int* famMonthEle);//计算某家庭每年总用电量
void calFamYearTotalFee(Family* fam, double* famYearTotalFee, double* famMonthFee);//计算某家庭每年总电费
//小区数据计算
void calComPeak(Community *com, int* comPeak);//计算某小区每月峰时用电量
void calComValley(Community *com, int* comValley);//计算某小区每月谷时用电量
void calComMonthTotalEle(Community *com, int* comMonthTotalEle);//计算某小区每月总用电量
void calComMonthTotalFee(Community *com, int* comMonthTotalFee);//计算某小区每月总电费
void calComYearTotalEle(Community *com, int* comYearTotalEle, int* comMonthTotalEle);//计算某小区每年总用电量
void calComYearTotalFee(Community *com, double* comYearTotalFee, double* comMonthTotalFee);//计算某小区每年总电费
double calAverageELe(Community *com);//计算某小区每户平均用电量
double calAverageFee(Community *com);//计算某小区每户平均电费
int calComTotalPeak(Community *com);//计算某小区两年内的峰时用电总量
int calComTotalValley(Community *com);//计算某小区两年内的谷时用电总量
//Community FindCommunity(Administration adm);
//制表函数
//家庭数据表格
void formFamMonthEle(Family* fam);//计算某家庭每年每月用电量
void formFamMonthFee(Family* fam);//计算某家庭每年每月电费
void formFamYearTotalEle(Family* fam);//计算某家庭每年总用电量
void formFamYearTotalFee(Family* fam);//计算某家庭每年总电费
//小区数据表格
void formComPeak(Community* com);//计算某小区每月峰时用电量
void formComValley(Community* com);//计算某小区每月谷时用电量
void formComMonthTotalEle(Community* com);//计算某小区每月总用电量
void formComMonthTotalFee(Community* com);//计算某小区每月总电费
void formComYearTotalEle(Community* com);//计算某小区每年总用电量
void formComYearTotalFee(Community* com);//计算某小区每年总电费
//排序函数
void sortComPeak(Administration* adm);//峰时用电量排序
void formSortComPeak(Administration* adm);//绘制峰时用电量排序表
void sortComFee(Administration* adm, int year, int month);//每月电费总量排序
void formSortComFee(Administration* adm);//绘制每月电费总量排序表
void sortComAverageEle(Administration* adm);//小区每户平均电量排序
void formSortComAverageEle(Administration* adm);//绘制小区每户平均电量排序表
void sortComAverageFee(Administration *adm);//每户平均电费排序
void formSortComAverage(Administration* adm);//绘制小区每户平均电费排序表
Community* findCommunity(Administration *adm);//找小区
Family* findFamily(Community*com);//找家庭

//查找扩容函数
void FindKuoRongCommunity(Administration* adm);

