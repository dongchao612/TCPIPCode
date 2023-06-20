#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc, char const *argv[])
{
    int serv_sock; // 服务器套接字
    char message[BUF_SIZE];

    int str_len = 0;

    sockaddr_in serv_adr, clent_adr;
    socklen_t clent_adr_sz;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1)
    {
        error_handling("UDP socket creation error");
    }
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind() error");
    }
    while (1)
    {
        clent_adr_sz = sizeof(clent_adr);
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (sockaddr *)&clent_adr, &clent_adr_sz);
        sendto(serv_sock, message, str_len, 0, (sockaddr *)&clent_adr, clent_adr_sz);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}