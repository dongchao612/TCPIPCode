#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

void error_handing(char *message);

int main(void)
{
    int fd;
    char buf[] = "Let us go!\n"; // 13个字节, 12个可见字符

    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        error_handing("open() error!");
    }
    printf("file descriptor : %d\n", fd);
    

    if ((write(fd, buf, sizeof(buf)) )== -1) //写入13个字节
    {
        error_handing("write() error!");
    }

    close(fd);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}