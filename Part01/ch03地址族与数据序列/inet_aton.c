#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>

void error_handing(char *message);

typedef struct sockaddr_in sockaddr_in;

/*
测试函数  inet_aton 将字符串IP转成网络地址
*/

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
        printf("Network orderd integer addr :%#x \n", addr_inet.sin_addr.s_addr); //0x4f7ce87f 
    }
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}