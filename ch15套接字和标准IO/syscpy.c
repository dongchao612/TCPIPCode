#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>

#define BUF_SIZE 3

int main(int argc, char const *argv[])
{
    int fd1, fd2;
    int len = 0;
    char buf[BUF_SIZE];

    fd1 = open("news.txt", O_RDONLY);
    fd2 = open("cpy_sys.txt", O_WRONLY | O_CREAT | O_TRUNC);

    while ((len = read(fd1, buf, sizeof(buf))) > 0)
    {
        write(fd2, buf, len);
    }

    return 0;
}
