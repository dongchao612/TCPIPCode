#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM)
    {
        puts("TIme out!");
    }
    alarm(2);
}

void keycontral(int sig)
{
    if (sig == SIGINT)
    {
        puts("CTRL+c predded");
    }
}

int main(int argc, char const *argv[])
{
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontral);

    alarm(2);

    for (i = 0; i < 3; i++)
    {
        puts("wait...");
        sleep(30);
    }
    return 0;
}
