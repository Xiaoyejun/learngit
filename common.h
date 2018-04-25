#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJ_ID 0X6666

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};

//创建信号量集
int CreateSem(int nums);
//初始化信号量集
int InitSem(int semid, int nums, int initVal);
//获取已创建好的信号量集
int GetSem(int nums);
//申请资源，相当于对信号量进行减操作
int P(int semid, int who);
//释放资源，相当于对信号量进行加操作
int V(int semid, int who);
//销毁刚创建的信号量集
int DestroySem(int semid);


