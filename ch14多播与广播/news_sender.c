#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define TTL 64
#define BUF_SIZE 30

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void error_handling(char *message);

int main(int argc, char const *argv[])
{
    int send_sock;
    sockaddr_in mul_adr;
    int time_live = TTL;
    FILE *fp;
    char buf[BUF_SIZE];
    if (argc != 3)
    {
        printf("Usage: %s <GroupIP> <PORT> \n", argv[0]);
        exit(1);
    }
    send_sock = socket(PF_INET, SOCK_DGRAM, 0);

    memset(&mul_adr, 0, sizeof(mul_adr));
    mul_adr.sin_family = AF_INET;
    mul_adr.sin_addr.s_addr = inet_addr(argv[1]);
    mul_adr.sin_port = htons(atoi(argv[2]));
    setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&time_live, sizeof(time_live));

    if ((fp = fopen("news.txt", "r")) == NULL)
    {
        error_handling("fopen() error");
    }

    while (!feof(fp))
    {
        fgets(buf, BUF_SIZE, fp);
        sendto(send_sock, buf, strlen(buf), 0, (sockaddr *)&mul_adr, sizeof(mul_adr));
    }
    fclose(fp);
    close(send_sock);

    return 0;
}

void error_handling(char *message)
{
    perror(message);
    exit(1);
}
