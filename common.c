#include "common.h"
static int CommonSemSet(int nums, int flags)
{
    key_t key = ftok(PATHNAME,PROJ_ID);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
    int semid = semget(key,nums,flags);
    if(semid < 0)
    {
        perror("semget");
        return -2;
    }
    return semid;
}

int CreateSem(int nums)
{
    return CommonSemSet(nums,IPC_CREAT|IPC_EXCL|0666);
}
int InitSem(int semid, int nums, int initVal)
{
    union semun un;
    un.val = initVal;
    if(semctl(semid,nums,SETVAL,un) < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}
int GetSem(int nums)
{
    return CommonSemSet(nums,IPC_CREAT);
}
static int CommPV(int semid, int who, int op)
{
    struct sembuf sf;
    sf.sem_flg = 0;
    sf.sem_op = op;
    sf.sem_num = who;
    if(semop(semid,&sf,1)<0)
    {
        perror("semop");
        return -1;
    }
    return 0;
}
int P(int semid, int who)
{
    return CommPV(semid,who,-1);
}
int V(int semid, int who)
{
    return CommPV(semid,who,1);
}
int DestroySem(int semid)
{
    if(semctl(semid, 0 ,IPC_RMID) < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}
