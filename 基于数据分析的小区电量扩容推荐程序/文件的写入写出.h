#include"供电局小区家庭.h"
//文件中按顺序写入一个家庭(被comWriteIn调用，请勿单独调用)
void famWriteIn(Family* fam,int n, FILE* fp);
//文件中按顺序写入一个小区（被admWriteIn调用，请勿单独调用)
void comWriteIn(Community* com,int n, FILE* fp);
//文件中写入一个局子，只需要调用这个（使用方式：引入已经初始化完全的administration）【存储方式为：局子头->小区头1->小区1的家庭1~n->小区头2->小区1的家庭1~n->……->小区头N->小区N的家庭1~n】
void admWriteIn(Administration* adm);
//取出community里的所有family，把community里的家庭head指针和数目n放进来，用文件内数据存入（fp沿用之前的file指针继续读取，本函数使用外层函数调用请勿单独调用）
void famReadFile(Community* com, FILE* fp);			/*输入小区中的头指针和家庭个数*/
//取出administration里的所有community，把administration里的小区head指针和数目n放进来，用文件内数据存入（fp沿用之前的file指针继续读取，本函数使用外层函数调用请勿单独调用）
void comReadFile(Administration*adm,  FILE* fp);
//直接调用这个东西，就可以从文件里面拽出来全部数据库(使用方式：引入一个预设的adm的地址，不要初始化，用本函数将其初始化）【取出顺序为局子头->小区头1->小区1的家庭1~n->小区头2->小区1的家庭1~n->……->小区头N->小区N的家庭1~n】
void admReadFile(Administration* adm);
