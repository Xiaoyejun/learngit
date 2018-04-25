#include "common.h"
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int semid = CreateSem(1);
    InitSem(semid, 0 ,1);
    pid_t pid = fork();
    int i = 20;
    if(pid < 0)
    {
        perror("fork");
        return 0;
    }else if(pid == 0)
    {
        //子进程
        int _semid = GetSem(0);
        //通过P,V操作实现两个进程的互斥
        //在屏幕上打印成对出现的AB
        while(i--)
        {
//            P(_semid, 0);
            printf("A");
            fflush(stdout);
            usleep(123456);
            printf("A ");
            fflush(stdout);
            usleep(321456);
//            V(_semid,0);
        }
    }
    else{
            //父进程
        while(i--)
        {
//            P(semid,0);
            printf("B");
            fflush(stdout);
            usleep(223456);
            printf("B ");
            fflush(stdout);
            usleep(121456);
//            V(semid,0);
        }
        wait(NULL);
    }
    DestroySem(semid);
    return 0;
}
