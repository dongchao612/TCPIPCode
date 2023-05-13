# TCPIPCode
《TCP&IP网络编程》图书信息：
作者：尹圣雨


## Part01 开始网络编程
### ch01 理解网络编程和套接字
```c
//  hello_server.c
int socket (int __domain, int __type, int __protocol);
int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
int listen (int __fd, int __n) ;
int accept (int __fd, __SOCKADDR_ARG __addr,socklen_t *__restrict __addr_len);
ssize_t write (int __fd, const void *__buf, size_t __n);
```

```c
//  hello_clent.c
int socket (int __domain, int __type, int __protocol);
int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
ssize_t read (int __fd, void *__buf, size_t __nbytes)
```