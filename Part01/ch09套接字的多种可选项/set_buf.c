#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

void error_handing(char *meeeage);

int main(int argc, char const *argv[])
{
    int sock;
    int snd_buf = 1024 * 3, rcv_buf = 1024 * 3;
    int state;
    socklen_t len;
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handing("socket() error");
    }

    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&snd_buf, sizeof(rcv_buf));
    if (state != 0)
    {
        error_handing("SO_SNDBUF setsockopt() error");
    }

    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, sizeof(snd_buf));
    if (state != 0)
    {
        error_handing("SO_SNDBUF setsockopt() error");
    }

    len = sizeof(snd_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, &len);
    if (state != 0)
    {
        error_handing("SO_SNDBUF getsockopt() error");
    }

    len = sizeof(rcv_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, &len);
    if (state != 0)
    {
        error_handing("SO_RCVBUF getsockopt() error");
    }

    printf(" Input buffer size %d\n", rcv_buf);  // 6144
    printf(" Output buffer size %d\n", snd_buf); // 6144

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}