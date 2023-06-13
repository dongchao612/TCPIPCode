#include <stdio.h>
#include <arpa/inet.h>

/*

测试字节序转换函数:htons htonl

大端cpu
*/
int main()
{
    unsigned short host_port = 0x1234; 
    unsigned short  net_port;

    unsigned int host_addr = 0x12345678; 
    unsigned int net_addr;

    net_port = htons(host_port);                       // 把short型数据从主机字节序转化为网络字节序
    printf("host ordered port : %#x \n", host_port);   // 0x1234
    printf("Network ordered port : %#x \n", net_port); // 0x3412

    net_addr = htonl(host_addr);                           // 把long型数据从主机字节序转化为网络字节序
    printf("host ordered address : %#lx \n", host_addr);   // 0x12345678
    printf("Network ordered address : %#lx \n", net_addr); // 0x78563412

    return 0;
}
