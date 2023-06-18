#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>

typedef struct hostent hostent;
typedef struct in_addr in_addr;

void error_handing(char *meeeage);

int main(int argc, char const *argv[])
{
    int i;
    hostent *host;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
    if (host == NULL)
    {
        error_handing("gethostbyname() error");
    }

    printf("Official name : %s \n", host->h_name);
    for (i = 0; host->h_addr_list[i]; i++)
    {
        printf("Aliases %d : %s \n", i + 1, host->h_addr_list[i]);
    }
    printf("Address type: %s \n", (host->h_addrtype == AF_INET) ? " A.F_INET" : " A.F_INET6");

        for (i = 0; host->h_addr_list[i]; i++)
    {
        printf("IP addr %d :%s \n", i + 1, inet_ntoa(*(in_addr*)host->h_addr_list[i]));
    }

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}