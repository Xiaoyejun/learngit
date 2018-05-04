#pragma once
#include <stdio.h>
typedef char ThreadTreeType;

typedef enum Thread{
    CHILD,
    THREAD
}Thread;

typedef struct ThreadTree{
    struct ThreadTree* lchild;
    struct ThreadTree* rchild;
    Thread left;
    Thread right;
    ThreadTreeType data;
}ThreadTree;


ThreadTree* CreateNode(ThreadTreeType value);
//@brief               根据先序遍历结果(带有空字符标记)
//                     构造一棵树
//@param array[]       先序遍历的结果，加上空字符标记
//@param size          数组的大小
//@param null_node     空字符标记
ThreadTree* ThreadTreeCreate(ThreadTreeType array[], size_t size, ThreadTreeType null_node);


void PreOrderThreading(ThreadTree* root);

void PreOrderByThreading(ThreadTree* root);

void InOrderThreading(ThreadTree* root);

void InOrderByThreading(ThreadTree* root);

void PostOrderThreading(ThreadTree* root);

//后序线索化遍历太麻烦，很鸡肋
void PostOrderByThreading(ThreadTree* root);


