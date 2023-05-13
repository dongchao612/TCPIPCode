#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in;

int main()
{
    sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1 %s \n", str_ptr);

    inet_ntoa(addr2.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation2 %s \n", str_ptr);
    printf("Dotted-Decimal notation2 %s \n", str_arr);

    return 0;
}