#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handing(char *meeeage);

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc, char *argv[])
{

    int serv_sock; // 服务器套接字
    int clnt_sock; // 客户端套接字

    sockaddr_in serv_addr; // 服务器地址
    sockaddr_in clnt_addr; // 客户端地址
    socklen_t clnt_addr_size;

    char message[] = "hello world!";

    if (argc != 2)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 调用socket函数创建套接字。
    if (serv_sock == -1)
    {
        error_handing("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = (atoi(argv[1]));

    if (bind(serv_sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // 调用 bind 函数分配IP地址和端口号。
    {
        error_handing("bind() error");
    }

    if (listen(serv_sock, 5) == -1) // 调用 listen 函数将套接字转为可接收连接状态。
    {
        error_handing("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);

    clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, &clnt_addr_size); // 调用 accept 函数受理连接请求。如果在没有连接请求的情况下调用该函数,则不会返回,直到有连接请求为止。
    if (clnt_sock == -1)
    {
        error_handing("accept() error");
    }

    write(clnt_sock, message, sizeof(message)); // 稍后将要介绍的 write 函数用 于传输数据
    
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}