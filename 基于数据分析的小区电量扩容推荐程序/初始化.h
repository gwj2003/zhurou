#include"供电局小区家庭.h"
#pragma once
void addDate(Family *fam);//向已有的户内输入一组（月）数据
Family* buildFamily(Community* com,char*name);//新建一个户
Community* buildCommunity(Administration* adm);//新建一个小区
Administration* buildAdministration();
void initCommunity(Community* com);//向小区里面加家庭
void initAdministration(Administration* adm);//向局子里面加小区

void autoAddDate(Family* fam);//自动生成数据
void autoBuildFamily(Community* com);//自动生成家庭
void autoBuildCommunity(Administration* adm, char* name);//自动附加建一个满小区，家庭数据随机,名字自己命名
void autoBuildAdministration(int num);//直接新建满adm,外部输入小区数





