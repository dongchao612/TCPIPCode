#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int gval = 10;
int main(int argc, char const *argv[])
{
    pid_t pid;
    int lval = 20;
    gval++;
    lval += 5;
    // printf("[%d, %d] \n", gval, lval);// [11, 25]

    pid = fork();
    // printf("pid = %d\n", pid); // 0 ->>子进程

    if (pid == 0)
    {
        gval += 2;
        lval += 2;
    }
    else
    {
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0)
    {
        printf("Child Proc:[%d, %d] \n", gval, lval);
    }
    else
    {
        printf("Parent Proc:[%d, %d] \n", gval, lval);
    }

    return 0;
}
