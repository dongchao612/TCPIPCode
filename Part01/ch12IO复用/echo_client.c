#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handing(char *meeeage);

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc, char *argv[])
{
    int sock;
    int write_len = 0;
    char message[BUF_SIZE];

    int str_len = 0, recv_len = 0, recv_cnt = 0;
    sockaddr_in serv_addr;

    if (argc != 3)
    {
        printf("Usage: %s  <ip> <port>\n", argv[0]);
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
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // 调用 connect函数向服务器端发送连接请求。
    {
        error_handing("connect() error");
    }
    else
    {
        puts("Connected..........");
    }

    while (1)
    {
        fputs("\nInput message(Q to quit):", stdout);
        fgets(message, BUF_SIZE, stdin);
        if ((!strcmp(message, "q\n")) || !(strcmp(message, "Q\n")))
        {
            break;
        }

        write_len = write(sock, message, strlen(message));

        recv_len = 0;
        while (recv_len < write_len)
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
            if (recv_cnt == -1)
            {
                error_handing("read() error");
            }
            recv_len += recv_cnt;
        }

        message[recv_len] = 0;
        printf("Message from server: %s", message);
    }

    close(sock);

    return 0;
}
void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}