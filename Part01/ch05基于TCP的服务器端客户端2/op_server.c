#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

int calculate(int opnum, int opnds[], char oprator);

void error_handing(char *meeeage);

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc, char const *argv[])
{
    int serv_sock, clnt_sock;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt, i;
    int recv_cnt, recv_len;

    sockaddr_in serv_adr, clnt_adr;

    socklen_t clnt_adr_sz;

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
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family - AF_INET;
    serv_adr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_adr.sin_port = (atoi(argv[1]));

    if (bind(serv_sock, (sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) // 调用 bind 函数分配IP地址和端口号。
    {
        error_handing("bind() error");
    }

    if (listen(serv_sock, 5) == -1) // 调用 listen 函数将套接字转为可接收连接状态。
    {
        error_handing("listen() error");
    }

    clnt_adr_sz = sizeof(clnt_adr);
    for (i = 0; i < 5; i++)
    {
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (sockaddr *)&clnt_adr, &clnt_adr_sz);
        read(clnt_sock, &opnd_cnt, 1); // 首先接收待算数个数 

        recv_len = 0;
        while ((opnd_cnt * OPSZ + 1) > recv_len)
        {
            recv_len = read(clnt_sock, &opinfo[recv_len], opinfo[recv_len - 1]);
            recv_len += recv_cnt;
        }

        result = calculate(opnd_cnt, (int *)opinfo, opinfo[recv_len - 1]);

        write(clnt_sock, (char *)&result, sizeof(result));
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

int calculate(int opnum, int opnds[], char oprator)
{
    int result = opnds[0], i;
    switch (oprator)
    {
    case '+':
        for (i = 0; i < opnum; i++)
        {
            result += opnds[i];
        }

        break;
    case '-':
        for (i = 0; i < opnum; i++)
        {
            result -= opnds[i];
        }
        break;
    case '*':
        for (i = 0; i < opnum; i++)
        {
            result *= opnds[i];
        }
        break;
    }

    return result;
}