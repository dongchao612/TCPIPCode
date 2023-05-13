#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>

void error_handing(char *message);

typedef struct sockaddr_in sockaddr_in;

int main()
{
    char *addr = "127.232.124.79";
    sockaddr_in addr_inet;

    if (!inet_aton(addr, &addr_inet.sin_addr))
    {
        error_handing("inet_aton() error");
    }
    else
    {
        printf("Network orderd integer addr :%#x \n", addr_inet.sin_addr.s_addr);
    }
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}