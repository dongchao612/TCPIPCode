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
    printf("pid = %d\n", pid); // 0 ->>子进程

    if (pid == 0)
    {
        printf("%d\t%d\t%d\n",__LINE__,getpid(),getppid());
        gval += 2;
        lval += 2;
    }
    else
    {
        printf("%d\t%d\t%d\n",__LINE__,getpid(),getppid());
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0)
    {
        printf("%d\t%d\t%d\n",__LINE__,getpid(),getppid());
        printf("Child Proc:[%d, %d] \n", gval, lval);
    }
    else
    {
        printf("%d\t%d\t%d\n",__LINE__,getpid(),getppid());
        printf("Parent Proc:[%d, %d] \n", gval, lval);
    }

    return 0;
}
