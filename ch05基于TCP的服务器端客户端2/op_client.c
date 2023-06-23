#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4 // 待计算数字的字节数
#define OPSZ 4     // 运算结果的字节数

void error_handling(char *message);

typedef struct sockaddr_in  sockaddr_in;

int main(int argc, char *argv[])
{
    int sock;
    char opmsg[BUF_SIZE]; // 为收发数据准备的内存空间，需要数据积累到一定程度后再收发，因此通过数组创建
    int result, opnd_cnt, i;
    struct sockaddr_in serv_adr;

    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("connect() error!");
    }
    else
    {
        puts("Connected.......");
    }

    fputs("Operand count: ", stdout);
    scanf("%d", &opnd_cnt);
    opmsg[0] = (char)opnd_cnt; // 从用户输入中得到待算数个数后，保存至数组opmsg

    for (i = 0; i < opnd_cnt; i++)
    {
        printf("Operand %d: ", i + 1);
        scanf("%d", (int *)&opmsg[i * OPSZ + 1]); // 待算数是4个字节，需要转化为int指针类型
    }
    fgetc(stdin); // 删掉缓冲中的字符\n
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]); // 输入运算符信息，保存到opmsg数组
    write(sock, opmsg, opnd_cnt * OPSZ + 2);  // 一次性传输opmsg数组中的相关信息
    read(sock, &result, RLT_SIZE);            // 保存服务器端的运算结果。待接收的数据长度为4字节，调用一次read函数即可

    printf("Operation result: %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
