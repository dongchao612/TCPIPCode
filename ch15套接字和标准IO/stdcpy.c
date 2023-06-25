#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>

#define BUF_SIZE 3

int main(int argc, char const *argv[])
{
    FILE *fp1;
    FILE *fp2;

    char buf[BUF_SIZE];

    fp1 = fopen("news.txt", "r");
    fp2 = fopen("cpy_std.txt", "w");

    while (fgets(buf, BUF_SIZE, fp1) != NULL)
    {
        fputs(buf, fp2);
    }

    return 0;
}
