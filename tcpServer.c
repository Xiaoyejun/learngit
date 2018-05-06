#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 128 

void server(int client_socket, struct sockaddr_in* client)
{
    char buf[128];
    while(1)
    {
        buf[0] = 0;
        ssize_t s = read(client_socket,buf,sizeof(buf));
        if(s < 0)
        {
            perror("read");
            continue;
        }else if(s == 0)
        {
            printf("client[%s] quit!\n",inet_ntoa(client->sin_addr));
            close(client_socket);
            break;
        } 
        buf[s-1] = 0;
        printf("client[%s] says:%s\n",inet_ntoa(client->sin_addr),buf);
        write(client_socket,buf,strlen(buf));
    }
    return;
}


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: [ip] [port]\n");
        exit(1);
    }

    int sock = socket(AF_INET,SOCK_DGRAM,0);//socket处于创建状态
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    
    if(bind(sock,(const struct sockaddr*)&server,sizeof(server)) < 0)
    {
        perror("bind");
        exit(3);
    }

    int listen_socket = listen(sock,5);
    if(listen_socket < 0)//此时处于监听状态
    {
        perror("listen");
        exit(4);
    }
    
    for(;;)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int client_socket = accept(listen_socket,(struct sockaddr*)&client,&len);
        if(client_socket < 0)
        {
            perror("accept");
            continue;
        }
        server(client_socket,&client);
    }
    return 0;
}
