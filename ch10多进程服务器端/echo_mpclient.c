#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/wait.h>
#include <sys/socket.h>

#include <signal.h>

#include <arpa/inet.h>

#define BUF_SIZE 30

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void error_handling(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char const *argv[])
{
    int sock;
    pid_t pid;
    char buf[BUF_SIZE];
    sockaddr_in serv_adr;
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(0);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (sockaddr *)&serv_adr, sizeof(serv_adr)) != -1)
    {
        error_handling("connect() error");
    }

    pid = fork();
    if (pid == 0) /*子进程运行区域*/
    {
        write_routine(sock, buf);
    }
    else
    {
        read_routine(sock, buf);
    }
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
void read_routine(int sock, char *buf)
{
    while (1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if (str_len == 1)
        {
            return;
        }
        buf[str_len] = 0;
        printf("Message from server : %s \n", buf);
    }
}
void write_routine(int sock, char *buf)
{
    while (1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            shutdown(sock, SHUT_WR);
            return;
        }

        write(sock, buf, strlen(buf));
    }
}