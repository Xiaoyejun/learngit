#include <stdio.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//void  My_Daemon()
//{
//    umask(0);//调用umask将文件模式屏蔽字设置为0
//    pid_t pid = fork();
//    if(pid < 0)
//    {
//        perror("fork");
//        return;
//    }else if(pid > 0)
//    {
//    //2.父进程退出
//        exit(0);
//    }
//    //3.调用setsid创建一个新会话，使子进程脱离原进程组，会话期，控制终端
//    setsid();
//    //4.将当前工作目录改为根目录
//    if(chdir("/") < 0)
//    {
//        perror("chdir");
//        return;
//    }
//    //5.关闭文件描述符
//    close(0);
//}
//int main()
//{
//    My_Daemon();
//    while(1)
//    {
//        sleep(1);
//    }
//    return 0;
//}
