#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in;

/*
测试函数inet_ntoa  将网络地址转成字符串IP
*/

int main()
{
    sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1 %s \n", str_ptr); // 1 1.2.3.4 

    inet_ntoa(addr2.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation2 %s \n", str_ptr); // 2 1.1.1.1 
    printf("Dotted-Decimal notation2 %s \n", str_arr); // 2 1.1.1.1 

    return 0;
}