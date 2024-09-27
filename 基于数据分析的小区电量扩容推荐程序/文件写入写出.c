#include"供电局小区家庭.h"
//文件中按顺序写入一个家庭(被comWriteIn调用，请勿单独调用)
void famWriteIn(Family* fam,int n, FILE* fp)
{
	if (fp == NULL)
	{
		printf("文件打开失败:fam\n");					    /*若打开失败输出提示信息*/
		exit(0);
	}
	else
	{
		printf("文件打开成功:fam\n" );
		Family* p = fam;			
		for (int i = 0; i < n; i++)
		{
			printf("开始写fam%s\n",p->famName);
			fwrite(p, sizeof(Family), 1, fp);						/*一次性向文件写入一个family记录，内涵一个family的2年、24个月的数据*/
			if (p->next != NULL)
			{
				p = p->next;
			}
			printf("写完一个fam,第%d个家庭\n", i);
		}
	}
}
//文件中按顺序写入一个小区（被admWriteIn调用，请勿单独调用)
void comWriteIn(Community* com,int n, FILE* fp)
{
	if (fp == NULL)
	{
		printf("文件打开失败:com\n");					    /*若打开失败输出提示信息*/
		exit(0);
	}
	else
	{
		printf("文件打开成功:com\n");
		Community* p = com;
		for (int i = 0; i < n; i++)
		{
			printf("开始写com：%s，有%d个fam\n", p->comName,p->n);
			fwrite(p, sizeof(Community), 1, fp);
			famWriteIn(p->head, p->n, fp);
			printf("写完com%s,第%d个小区\n",p->comName, i+1);
			if (p->next != NULL)
			{
				p = p->next;
			}
		}
	}
}
//文件中写入一个局子，只需要调用这个（使用方式：引入已经初始化完全的administration）【存储方式为：局子头->小区头1->小区1的家庭1~n->小区头2->小区1的家庭1~n->……->小区头N->小区N的家庭1~n】
void admWriteIn(Administration* adm)
{
	FILE* fp;
	errno_t err = fopen_s(&fp, filePath, "wb");					/*记得在供电局.h里面把文件路径改成自己的*/
	if (err==0)//如果打开成功
	{	
		fwrite(adm, sizeof(Administration), 1, fp);		 /*向刚申请的空间里放文件里的adm*/
		comWriteIn(adm->head, adm->n, fp);				 /*开始用fp读adm里面的所有community*/
		fclose(fp);
	}
	else
	{
		printf("文件打开失败:adm-w\n");							 /*若打开失败输出提示信息*/
		exit(0);
	}
	printf("写入结束");
}


//取出community里的所有family，把community里的家庭head指针和数目n放进来，用文件内数据存入（fp沿用之前的file指针继续读取，本函数使用外层函数调用请勿单独调用）
void famReadFile(Community* com, FILE* fp)			/*输入小区中的头指针和家庭个数*/
{
	if (fp == NULL)
	{
		printf("文件打开失败:fam\n");						/*若打开失败输出提示信息*/
		exit(0);
	}
	else
	{
		printf("文件打开成功:fam\n");						/*若打开失败输出提示信息*/
		for (int i = 0; i < com->n; i++)
		{
			Family* p1 = com->head;							//p->next永远指向空
			Family* q1;
			for (int j = 0; j < i - 1; j++)		p1 = (p1)->next;
			q1 = (Family*)malloc(sizeof(Family) * 1);
			if (q1 == NULL)
			{
				printf("内存申请失败");
			}
			else
			{
				fread(q1, sizeof(Family), 1, fp);
				if (i == 0)
					com->head = q1;
				else
					p1->next = q1;
			}
			printf("读完一个fam，是第%d户，叫%s\n", i+1,q1->famName);
		}
	}
}
//取出administration里的所有community，把administration里的小区head指针和数目n放进来，用文件内数据存入（fp沿用之前的file指针继续读取，本函数使用外层函数调用请勿单独调用）
void comReadFile(Administration * adm, FILE* fp)
{
	if (fp == NULL)
	{
		printf("文件打开失败:com\n");					    /*若打开失败输出提示信息*/
		exit(0);
	}
	else
	{
		printf("文件打开成功:com\n");
		for ( int i = 0; i < adm->n; i++)
		{
			Community* p = adm->head;							//p->next永远指向空
			Community* q;
			for (int j = 0; j < i - 1; j++) { p = (p)->next; }
			q = (Community*)malloc(sizeof(Community) * 1);
			if (q == NULL)
			{
				printf("内存申请失败");
			}
			else
			{
				printf("开始读com\n");
				fread(q, sizeof(Community), 1, fp);	
				printf("小区%s有%d个家庭\n", q->comName,q->n);
				famReadFile(q,fp);
				if (i == 0)
					adm->head = q;
				else
					p->next = q;
			}
			printf("读完一个com,第%d个小区\n",i+1);

		}
	}
}
//直接调用这个东西，就可以从文件里面拽出来全部数据库(使用方式：引入一个预设的adm的地址，不要初始化，用本函数将其初始化）【取出顺序为局子头->小区头1->小区1的家庭1~n->小区头2->小区1的家庭1~n->……->小区头N->小区N的家庭1~n】
void admReadFile(Administration* adm)
{
	FILE* fp;
	errno_t err = fopen_s(&fp, filePath, "rb");					/*记得在供电局.h里面把文件路径改成自己的*/	
	if (err!=0)
	{
		printf("文件打开失败:adm-r\n");							 /*若打开失败输出提示信息*/
		exit(0);
	}
	else
	{
		printf("开始读adm");
		//adm = (Administration*)malloc(sizeof(Administration) * 1);
		fread(adm, sizeof(Administration), 1, fp);		 /*向刚申请的空间里放文件里的adm*/
		printf("有%d个小区\n", adm->n);
		//comReadFile(adm->head, adm->n, fp);				 /*开始用fp读adm里面的所有community*/
		if (fp == NULL)
		{
			printf("文件打开失败:com\n");					    /*若打开失败输出提示信息*/
			exit(0);
		}
		else
		{
			printf("文件打开成功:com\n");
			for (int i = 0; i < adm->n; i++)
			{
				Community* p = adm->head;							//p->next永远指向空
				Community* q;
				for (int j = 0; j < i - 1; j++) { p = (p)->next; }
				q = (Community*)malloc(sizeof(Community) * 1);
				if (q == NULL)
				{
					printf("内存申请失败");
				}
				else
				{
					printf("开始读com\n");
					fread(q, sizeof(Community), 1, fp);
					printf("小区%s有%d个家庭\n", q->comName, q->n);
					//famReadFile(q, fp);
					if (fp == NULL)
					{
						printf("文件打开失败:fam\n");						/*若打开失败输出提示信息*/
						exit(0);
					}
					else
					{
						printf("文件打开成功:fam\n");						/*若打开失败输出提示信息*/
						for (int i = 0; i < q->n; i++)
						{
							Family* p1 = q->head;							//p->next永远指向空
							Family* q1;
							for (int j = 0; j < i - 1; j++)		p1 = (p1)->next;
							q1 = (Family*)malloc(sizeof(Family) * 1);
							if (q1 == NULL)
							{
								printf("内存申请失败");
							}
							else
							{
								fread(q1, sizeof(Family), 1, fp);
								if (i == 0)
									q->head = q1;
								else
									p1->next = q1;
							}
							printf("读完一个fam，是第%d户，叫%s\n", i + 1, q1->famName);
						}
					}

					if (i == 0)
						adm->head = q;
					else
						p->next = q;
				}
				printf("读完一个com,第%d个小区\n", i + 1);

			}
		}

		fclose(fp);
	}
}
