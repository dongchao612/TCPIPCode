#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <signal.h>
#include <fcntl.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

#define BUF_SIZE 30

void error_handing(char *meeage);
void urg_handler(int signo);

int acpt_sock, recv_sock;

int main(int argc, char const *argv[])
{

    sockaddr_in recv_adr, serv_adr;
    int str_len, state;
    socklen_t serv_adr_sz;
    struct sigaction act;
    char buf[BUF_SIZE];

    if (argc != 2)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (acpt_sock == -1)
    {
        error_handing("socket() error");
    }

    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(acpt_sock, (sockaddr *)&recv_adr, sizeof(recv_adr)) == -1) // 调用 bind 函数分配IP地址和端口号。
    {
        error_handing("bind() error");
    }

    if (listen(acpt_sock, 5) == -1) // 调用 listen 函数将套接字转为可接收连接状态。
    {
        error_handing("listen() error");
    }

    serv_adr_sz = sizeof(serv_adr);
    recv_sock = accept(acpt_sock, (sockaddr *)&serv_adr, &serv_adr_sz);
    if (recv_sock == -1)
    {
        error_handing("accept() error");
    }

    fcntl(recv_sock, F_SETOWN, getpid());
    state = sigaction(SIGURG, &act, 0);

    while ((str_len = recv(recv_sock, buf, sizeof(buf), 0)) != 0)
    {
        if (str_len == -1)
        {
            continue;
        }
        buf[str_len] = 0;
        puts(buf);
    }

    close(recv_sock);
    close(acpt_sock);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void urg_handler(int signo)
{
    int str_len;
    char buf[BUF_SIZE];
    str_len = recv(recv_sock, buf, sizeof(buf) - 1, MSG_OOB);
    buf[str_len] = 0;
    printf("Urgent  mesage : %s \n", buf);
}