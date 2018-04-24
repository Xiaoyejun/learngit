#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define FOR_MAZE
#include "bin_tree.h"
//#define TESTHEAD printf("======================[%s]======================\n",__FUNCTION__);
//#ifdef FOR_MAZE;
struct TreeNode;

typedef struct Point{
    int row;
    int col;
}Point;

struct TreeNode;
//typedef  Point SeqStackType;
typedef TreeNode* SeqStackType;
//typedef char SeqStackType;
typedef struct SeqStack{
     SeqStackType* data;//长度到了最大值时就malloc一段新的内存，所以用指针指向的内存来存储顺序表中的数据
    size_t size;//有效长度
    size_t capacity;//原有的内存可容纳的最大长度
}SeqStack;


void SeqStackInit(SeqStack* seq);

void SeqStackDestroy(SeqStack* seq);

SeqStackType* SeqStackExpand(SeqStack* seq);

void SeqStackPush(SeqStack* seq,SeqStackType value);

void SeqStackPop(SeqStack* seq);

int SeqStackFindTop(SeqStack* Seq,SeqStackType* value);
//将 cur_path 中的值赋值到 short_path 中
void SeqStackAssgin(SeqStack* cur_path,SeqStack* short_path);


//通常栈是不允许进行遍历的
//但是如果是进行调试或者测试，这个是例外
//因此在这里的函数虽然进行了遍历，但是仅用于调试
void SeqStackDebugPrint(SeqStack* stack,const char* msg);

