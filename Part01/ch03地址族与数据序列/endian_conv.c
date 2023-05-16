#include <stdio.h>
#include <arpa/inet.h>

/*

测试字节序转换函数:htons htonl

大端cpu
*/
int main()
{
    uint16_t host_port = 0x1234; //  unsigned short int 【unsigned short 】
    uint16_t net_port;

    uint32_t host_addr = 0x12345678; // unsigned int【unsigned short 】
    uint32_t net_addr;

    net_port = htons(host_port);                       // 把short型数据从主机字节序转化为网络字节序
    printf("host ordered port : %#x \n", host_port);   // 0x1234
    printf("Network ordered port : %#x \n", net_port); // 0x3412

    net_addr = htonl(host_addr);                           // 把long型数据从主机字节序转化为网络字节序
    printf("host ordered address : %#lx \n", host_addr);   // 0x12345678
    printf("Network ordered address : %#lx \n", net_addr); // 0x78563412

    return 0;
}
