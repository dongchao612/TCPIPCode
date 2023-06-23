#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#define BUF_SIZE 30

void error_handing(char *meeeage);

int main(int argc, char const *argv[])
{
    int sock;
    sockaddr_in recv_adr;

    if (argc != 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handing("socket() error");
    }

    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (sockaddr *)&recv_adr, sizeof(recv_adr)) == -1) // 调用 connect函数向服务器端发送连接请求。
    {
        error_handing("connect() error");
    }

    write(sock, "123", strlen("123"));
    send(sock, "4", strlen("4"), MSG_OOB); // 紧急传输数据
    write(sock, "567", strlen("567"));
    send(sock, "890", strlen("890"), MSG_OOB); // 紧急传输数据

    close(sock);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}