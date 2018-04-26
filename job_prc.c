#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    int i = 5;
    if(pid < 0)
    {
        perror("fork");
        return -1;
    }else if(pid == 0)
    {//子进程
        while(1)
        {
            //子进程一直打印该语句
            printf("I am Running,I am child %d \n",getpid());
            sleep(1);
        }
    }else{
        //父进程打印完五秒后退出
        while(i)
        {
            printf("I am father, %d \n",i--);
            sleep(1);
        }
    }
    return 0;
}
