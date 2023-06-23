#include <stdio.h>
#include <arpa/inet.h>

/*
inet_addr
将字符串类型的IP转换为字节序，其中超过255会报错
*/
int main()
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
    {
        printf("error occured!\n");
    }
    else
    {
        printf("Network orderd integer addr :%#lx \n", conv_addr); // 0x4030201
    }

    conv_addr = inet_addr(addr2); // error occured!
    if (conv_addr == INADDR_NONE)
    {
        printf("error occured!\n");
    }
    else
    {
        printf("Network orderd integer addr :%#lx \n", conv_addr);
    }

    return 0;
}