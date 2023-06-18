#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void error_handing(char *meeeage);

int main(int argc, char const *argv[])
{
    int serv_sd, clnt_sd;
    FILE *fp = NULL;
    char buf[BUF_SIZE];
    int read_cnt = 0;

    sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz = 0;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c", "rb");
    if (fp == NULL)
    {
        error_handing("fopen() error");
    }

    serv_sd = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sd == -1)
    {
        error_handing("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sd, (sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) // 调用 bind 函数分配IP地址和端口号。
    {
        error_handing("bind() error");
    }

    if (listen(serv_sd, 5) == -1) // 调用 listen 函数将套接字转为可接收连接状态。
    {
        error_handing("listen() error");
    }

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (sockaddr *)&clnt_adr, &clnt_adr_sz);
    if (clnt_sd == -1)
    {
        error_handing("accept() error");
    }

    while (1)
    {
        read_cnt = fread((void *)buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE)
        {
            write(clnt_sd, buf, read_cnt);
            break;
        }

        write(clnt_sd, buf, BUF_SIZE);
    }

    shutdown(clnt_sd, SHUT_WR);

    read(clnt_sd, buf, BUF_SIZE);
    printf("Message form client:%s\n", buf);

    fclose(fp);
    close(clnt_sd);
    close(serv_sd);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
