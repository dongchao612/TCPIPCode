#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

void error_handling(char *message);

int main(int argc, char const *argv[])
{
    int recv_sock;
    int str_len;
    char buf[BUF_SIZE];
    sockaddr_in adr;

    if (argc != 2)
    {
        printf("Usage: %s <PORT> \n", argv[0]);
        exit(1);
    }
    recv_sock = socket(PF_INET, SOCK_DGRAM, 0);

    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[1]));

    if ((bind(recv_sock, (sockaddr *)&adr, sizeof(adr))) == -1)
    {
        error_handling("bind() error");
    }


    setsockopt(recv_sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&adr,sizeof(adr));

    while (1)
    {
        str_len=recvfrom(recv_sock,buf,BUF_SIZE-1,0,NULL,0);
        if(str_len<0)
        {
            break;
        }
        buf[BUF_SIZE]=0;
        fputs(buf,stdout);
    }
    
    close(recv_sock);

    return 0;
}

void error_handling(char *message)
{
    perror(message);
    exit(1);
}
