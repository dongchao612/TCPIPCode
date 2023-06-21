#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

typedef struct timeval timeval;

int main(int argc, char const *argv[])
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    timeval timeout;
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
    while (1)
    {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        result = select(1, &temps, 0, 0, &timeout);
        if (result == -1)
        {
            puts("selelct() error");
            break;
        }
        else if (result == 0)
        {
            puts("Time-out");
        }
        else
        {
            if (FD_ISSET(0, &temps))
            {
                str_len = read(0, buf, BUF_SIZE);
                buf[BUF_SIZE] = 0;
                printf("message from console : %s", buf);
            }
        }
    }

    return 0;
}
