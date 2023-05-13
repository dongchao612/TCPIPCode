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
    int sock;
    sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if (argc != 3)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0); // 创 建套接字,但此时套接字并不马上分为服务器端和客户端。
    if (sock == -1)
    {
        error_handing("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = (atoi(argv[2]));

    if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // 调用 connect函数向服务器端发送连接请求。
    {
        error_handing("connect() error");
    }

    str_len = read(sock, message, sizeof(message) - 1);

    if (str_len == -1)
    {
        error_handing("read() error");
    }

    printf("Message from server : %s \n", message);
    close(sock);

    return 0;
}
void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}