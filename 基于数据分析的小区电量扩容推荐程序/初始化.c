#include"供电局小区家庭.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//向已有的户内输入一组（月）数据
void addDate(Family* fam)
{
	int choose;
	do
	{
		int year, month;
		printf("请输入家庭%s该组数据的采集时间：\n年份：",fam->famName);
		scanf_s("%d", &year);
		printf("月份：");
		scanf_s("%d", &month);
		if (year < 2021 || year>2022 || month < 1 || month>12)//时间检查
		{
			printf("时间输入有误或超范（请输入在范围2021年1月-2022年12间的时间）\n请重新输入\n");
			addDate(fam);
		}
		else
		{
			printf("%d年%d月的峰时用电量为：", year, month);
			scanf_s("%d", fam->famPeak[year - 2021] + (month - 1));
			printf("%d年%d月的谷时用电量为：", year, month);
			scanf_s("%d", fam->famValley[year - 2021] + (month - 1));
			printf("是否继续向该家庭中输入？\n");//退出bug
			printf("######## 1. 是   ########\n");
			printf("######## 0. 否   ########\n");
			scanf_s("%d", &choose);
		}
	} while (choose);
}

//自动生成数据，一个家庭的所有数据
void autoAddDate(Family* fam)
{
	srand((unsigned long)time(0));
	for(int year=2021;year<2023;year++)
		for (int month = 1; month <= 12; month++)
		{
			*(fam->famPeak[year - 2021] + (month - 1) )= rand() % (150) + 50;
			*(fam->famValley[year - 2021] + (month - 1)) = rand() % (50) + 50;
		}
}
//新建一个空户
Family* buildFamily(Community* com,char* name)
{
	Family* f = (com->head);
	Family* p;
	for (int i = 0; i < com->n-1; i++)
		f = f->next;
	p = (Family*)malloc(sizeof(Family) * 1);
	if (p == NULL)
	{
		printf("内存申请失败");
		return NULL;
	}
	else
	{
		int i, j;//初始化户的所有用电量为0
		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 12; j++)
			{
				p->famPeak[i][j] = 0;
				p->famValley[i][j] = 0;
			}
		}
		printf("%s", name);
		strcpy_s(p->famName ,21, name);
		p->num = com->n+1;
		p->famName;
		p->next = NULL;
		if (com->n == 0)
			com->head = p;
		else
			f->next = p;
		printf("%s是%s的第%d户 ！！！\n", p->famName, com->comName,com->n+1);//用完删掉
		return f;
	}
}

//自动生成至com。n个家庭,在外层初始化先，不然是0个，没有数据
void autoBuildFamily(Community* com)
{
	for(int k=0;k<com->n;k++)					//循环com.n次，做n次加数据
	{
		Family* f = (com->head);
		Family* p;							//向p里面建设一个完整节点，思路同初始化，name用num，next为空，用autoadd加电，每个k一次
		for (int i = 0; i < k - 1; i++)
			f = f->next;
		p = (Family*)malloc(sizeof(Family) * 1);
		if (p == NULL)
		{
			printf("内存申请失败");
			return NULL;
		}
		else
		{
			p->num = k + 1;
			autoAddDate(p);
			int a = p->num % 10, c = p->num / 100, b = (p->num - 100 * c) / 10;
			p->famName[0] = 0x30 + c;
			p->famName[1] = 0x30 + b;
			p->famName[2] = 0x30 + a;
			p->next = NULL;
			if (k == 0)
				com->head = p;
			else
				f->next = p;
			//printf("%s是%s的第%d户 ！！！\n", p->famName, com->comName, k+ 1);//用完删掉
		}
	}
}

//新建一个空小区,返回头之指针
Community* buildCommunity(Administration *adm,char* name)
{
	Community* p = (adm)->head;							//p永远指向空
	Community* q;
	for (int i = 0; i < (adm)->n-1; i++)		p = (p)->next;
	q = (Community*)malloc(sizeof(Community) * 1);
	if (q == NULL)
	{
		printf("内存申请失败");
		return NULL;
	}
	else
	{
		(q)->head = NULL;
		strcpy_s((q)->comName,21 , name);
		(q)->n = 0;
		(q)->next = NULL;
		if (adm->n == 0)
			adm->head = q;
		else
			p->next = q;
		return q;
	}
}

//自动附加建一个满小区，家庭数据个数随机,名字自己命名，无循环
void autoBuildCommunity(Administration* adm, char* name)
{
	srand((unsigned int)time(0));					
	Community* p = (adm)->head;							
	Community* q;
	for (int i = 0; i < adm->n - 1; i++)		p = (p)->next;
	q = (Community*)malloc(sizeof(Community) * 1);
	if (q == NULL)
		{
			printf("内存申请失败");
			return NULL;
		}
	else
		{
		q->head = NULL;
		q->n = 50;//(rand() % 1 + 50);						//生成50-100个，个数随机的家庭，如注释先初始化它
		strcpy_s((q)->comName, 21, name);
		(q)->next = NULL;
		autoBuildFamily(q);								//本函数生成的已经是满小区了，循环几次出几个
			if (adm->n == 0)
				adm->head = q;
			else
				p->next = q;
		}
	adm->n++;
}

//新建一个空adm,并返回
Administration* buildAdministration()
{
	Administration* adm;
	adm = (Administration*)malloc(sizeof(Administration) * 1);
	if (adm == NULL)
	{
		printf("内存申请失败");
		return NULL;
	}
	else
	{
		adm->head=NULL;
		adm->n = 0;
		adm->kn = 0;
		return adm;
	}
}

//直接新建满adm,外部输入小区数num
void autoBuildAdministration(int num)
{
	Administration* adm = (Administration*)malloc(sizeof(Administration) * 1);
	if (adm == NULL)
	{
		printf("内存申请失败");
		return NULL;
	}
	else
	{
		adm->n = num;
		adm->kn = 0;
		adm->head = NULL;
		for (int i = 1; i <= num; i++)					//循环num次，附加num个满小区进去，小区名以次序号命名
		{
			char name[20];
			int a = i % 10, c = i / 100, b = (i- 100 * c) / 10;
			name[0] = 0x30 + c;
			name[1] = 0x30 + b;
			name[2] = 0x30 + a;
			autoBuildCommunity(adm, name);					//每次都加一个整小区进去
			adm->n++;
		}
	}

}
//向adm里加小区
void initAdministration(Administration* adm)
{
	while (1)
	{
		char name[20];
		int check = 0;
		Community* p = adm->head;
		printf("请输入新录入小区的名字：");
		scanf_s("%s", name, 20);
		for (int i = 0; i < adm->n; i++)
		{
			if (strcmp(name, p->comName)==0)
			{
				printf("该小区名已被占用，请重新输入！\n");
				check++;
			}
			else
				p = p->next;
		}
		if (check == 0)
		{
			buildCommunity(adm, name);
			adm->n++;
			printf("小区%s新建成功\n现有小区%d个\n",name,adm->n);
			system("pause");
			break;
		}
	}		
}

//向com内加家庭
void initCommunity(Community* com)//向com内加家庭
{
	
	while (1)
	{
		char name[20];
		int check = 0;
		Family* p = com->head;
		printf("请输入新录入家庭的名字：");
		scanf_s("%s", name, 20);
		for (int i = 0; i < com->n; i++)
		{
			if (strcmp(name, p->famName) == 0)
			{
				printf("该户名已被占用，请重新输入！\n");
				check++;
				printf("%d", check);
			}
			else
				p = p->next;
		}
		if (check == 0)
		{
			buildFamily(com, name);
			com->n++;
			printf("现有家庭%d个\n", com->n);
			break;
		}
	}
}


