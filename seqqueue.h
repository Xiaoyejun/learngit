#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include "bin_tree.h"

#define SeqQueueMaxSize 1000

#if 1
typedef struct TreeNode* SeqQueueType;
#else
typedef char SeqQueueType;
#endif

//head作为队首，tail作为队尾
//插入数据时，tail向后移，从队列里删除数据时，head往后移
//数据出队列时其实并没有真实的被删除，而是随着head的后移，之前的队首元素不在有效范围内了
//tail到了数组末尾时，检查一下head是否表示的是数组(不是队列)头部，如果不是的话说明数组的头部还可以插入数据
//作为队列的尾部。直到size等于数组的最大容量时，才说明队列已经满了
typedef struct SeqQueue{
    SeqQueueType data[SeqQueueMaxSize];
    size_t head;
    size_t tail;
    size_t size;
}SeqQueue;



void SeqQueueInit(SeqQueue* seq);

void SeqQueuePush(SeqQueue* seq,SeqQueueType value);

void SeqQueuePop(SeqQueue* seq);

int SeqQueueGetTop(SeqQueue* seq,SeqQueueType* value);

