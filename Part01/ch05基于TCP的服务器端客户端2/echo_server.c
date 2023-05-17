#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 5

void error_handing(char *meeeage);

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    memset(message,0,BUF_SIZE);
    int str_len, i;

    sockaddr_in serv_addr, clnt_addr;

    socklen_t clnt_addr_size;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 调用 socket函数创建套接字。
    if (serv_sock == -1)
    {
        error_handing("socket() error");
    }

    // 初始化结构体
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family - AF_INET;
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
    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, &clnt_addr_size); // 调用 accept 函数受理连接请求。如果在没有连接请求的情况下调用该函数,则不会返回,直到有连接请求为止。
        if (clnt_sock == -1)
        {
            error_handing("accept() error");
        }
        else
        {
            printf("Connected cliend %d \n", i + 1);
        }

        while ((str_len = read(clnt_sock, message, BUF_SIZE) )!= 0)
        {

            if (str_len == -1)
            {
                error_handing("read() error");
            }
            write(clnt_sock, message, str_len);

        }
        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}