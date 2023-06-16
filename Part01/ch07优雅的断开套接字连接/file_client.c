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

    int sd;
    FILE *fp;

    char buf[BUF_SIZE];
    int read_cnt;

    sockaddr_in serv_adr;
    if (argc != 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("receive.dat", "wb");
    if (fp == NULL)
    {
        error_handing("fopen() error");
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);

    if (sd == -1)
    {
        error_handing("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[0]));

    if (connect(sd, (sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) // 调用 connect函数向服务器端发送连接请求。
    {
        error_handing("connect() error");
    }
    
    while ((read_cnt = read(sd, buf, BUF_SIZE)) != 0)
    {
        fwrite((void *)buf, 1, read_cnt, fp);
    }

    puts("Received file data");
    write(sd, "Thank you", 10);

    fclose(fp);
    close(sd);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
