#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#define BUF_SIZE 100

void error_handing(char *message);

int main(void)
{
    int fd;
    char buf[BUF_SIZE]; // 100个字节, 0个可见字符
    printf("%d\t%d\n", sizeof(buf), strlen(buf));

    fd = open("data.txt", O_RDONLY);
    if (fd == -1)
    {
        error_handing("open() error!");
    }
    printf("file descriptor : %d\n", fd);


        int read_cnt=0;
    if ((read_cnt=  (fd, buf, sizeof(buf)) )== -1) // 一次性读100字节到buf里面，但是只有13个字节
    {
        error_handing("read() error!");
    }
    puts(buf);
    printf("%d\n",read_cnt);
    printf("%d\t%d\n", sizeof(buf), strlen(buf)); // 100个字节, 12个可见字符

    close(fd);
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}