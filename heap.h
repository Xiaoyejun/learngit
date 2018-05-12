#pragma once

#include <stddef.h>

#define HeapMaxSize 1000
#define TESTHEAD printf("\n===============[%s]==============\n",__FUNCTION__);

typedef int HeapType;

//定义一个比较函数的函数指针，用来指明该堆是小堆还是大堆
typedef int (*Compare)(HeapType a, HeapType b);

typedef struct Heap{
    HeapType data[HeapMaxSize];
    size_t size;
    Compare com;
}Heap;

//初始化堆
void HeapInit(Heap* heap,Compare compare);

//插入元素
void HeapInsert(Heap* heap, HeapType value);

//取堆顶元素
int HeapRoot(Heap* heap, HeapType* value);

//删除堆顶元素
void HeapErase(Heap* heap);

//判断堆是否为空
int HeapEmpty(Heap* heap);

//求堆中元素个数
size_t HeapSize(Heap* heap);

//创建堆
void HeapCreate(HeapType array[], Heap* heap,size_t size);

//堆排序
void HeapSort(HeapType array[], Heap* heap, size_t size);

//销毁堆
void HeapDestroy(Heap* heap);
