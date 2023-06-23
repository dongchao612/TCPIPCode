#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <arpa/inet.h>

#define BUF_SIZE 30

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void error_handing(char *meeeage);

int main(int argc, char const *argv[])
{
    int acpt_sock, recv_sock;
    sockaddr_in acpt_adr, recv_adr;
    int str_len, state;
    socklen_t serv_adr_sz;
    char buf[BUF_SIZE];

    if (argc != 2)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (acpt_sock == -1)
    {
        error_handing("socket() error");
    }

    memset(&acpt_adr, 0, sizeof(acpt_adr));
    acpt_adr.sin_family = AF_INET;
    acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    acpt_adr.sin_port = htons(atoi(argv[1]));

    if (bind(acpt_sock, (sockaddr *)&acpt_adr, sizeof(acpt_adr)) == -1) // 调用 bind 函数分配IP地址和端口号。
    {
        error_handing("bind() error");
    }

    if (listen(acpt_sock, 5) == -1) // 调用 listen 函数将套接字转为可接收连接状态。
    {
        error_handing("listen() error");
    }

    serv_adr_sz = sizeof(recv_adr);

    recv_sock = accept(acpt_sock, (sockaddr *)&recv_adr, &serv_adr_sz);
    if (recv_sock == -1)
    {
        error_handing("accept() error");
    }

    while (1)
    {
        str_len = recv(recv_sock, buf, sizeof(buf) - 1, MSG_PEEK | MSG_DONTWAIT);
        if (str_len > 0)
        {
            break;
        }
    }

    buf[str_len] = 0;
    printf("Buffering %d bytes:%s \n", str_len, buf);

    str_len = recv(recv_sock, buf, sizeof(buf) - 1, 0);
    printf("Read again : %s \n", buf);

    close(acpt_sock);
    close(recv_sock);

    return 0;
}

void error_handing(char *meeage)
{
    fputs(meeage, stderr);
    fputc('\n', stderr);
    exit(1);
}