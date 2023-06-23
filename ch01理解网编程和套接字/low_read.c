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

    fd = open("data.txt", O_RDONLY);
    if (fd == -1)
    {
        error_handing("open() error!");
    }
    printf("file descriptor : %d\n", fd);

    if (read(fd, buf, sizeof(buf)) == -1) // 一次性读100字节到buf里面，但是只有13个字节
    {
        error_handing("read() error!");
    }
    printf("file data:%s", buf);

    close(fd);
    
    return 0;
}

void error_handing(char *message)
{
    perror(message);
    exit(1);
}