# TCPIPCode

《TCP&IP网络编程》图书信息：
作者：尹圣雨


## Part01 开始网络编程

### ch01 理解网络编程和套接字
```c
// 打开文件

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *path,int flag);
// 成功时返回文件描述符, 失败时返回-1
// path 文件名的字符串地址 。
// flag 文件打开模式信息。

```

```c
// 关闭文件

#include <unistd.h>
int close(int fd);
// 成功时返回0, 失败时返回-1
// fd 需要关闭的文件或套接字的文件描述符
```

```c
// 写入文件

#include <unistd.h>
ssize_t write (int __fd, const void *__buf, size_t __n);
// 成功时返回写入字节数, 失败时返回-1
// fd 显示数据传输对象的文件描述符
// buf 保存要传输数据的缓冲地址值
// n 要传输数据的字节数
```

```c
// 读取文件

#include <unistd.h>
ssize_t read (int __fd, void *__buf, size_t __nbytes)
// 成功时返回写入字节数, 失败时返回-1
// fd 显示数据传输对象的文件描述符
// buf 保存要传输数据的缓冲地址值
// nbytes要传输数据的字节数
```

### ch02 套接字类型与协议设置

```c
//创建套接字

#include <sys/socket.h>
int socket (int __domain, int __type, int __protocol);
// 成功时返回文件描述符,失败时返回-1
// domain 套接字中使用的协议族信息
// - PF_INET4 IPV4互联网协议族
// - PF_INET6 IPV6互联网协议族
// - PF_LOCAL 本地通信的UNIX协议族
// - PF_PACKET 底层套接字的协议族
// - PF_IPX IPX Novell协议族
// type 套接字数据传输类型信息
// - 面向连接的套接字(SOCK_STREAM)
//    传输过程中数据不会消失
//    按序传输数据
//    传输过程中不存在数据边界
// - 面向消息的套接字(SOCK_DGRAM)
//    强调快速传输而非传输顺序
//    传输的数据可能丢失也可能损毁 。
//    传输的数据有数据边界
//    限制每次传输 的数据大小 。
// protocol 计算机间通信中使用的协议
```

### ch03 地址族与数据序列
#### 网络地址
IPv4标准的4字节F地址分为网络地址和主机(指计算机)地址, 且分为A 、B 、 C 、 D 、 E等类型

- A类地址的首字节范围: 0--127【A类地址的首位以 0开始】
- B类地址的首字节范围: 128--191【B类地址的前2位以 10开始】
- C类地址的首字节范围: 192--223【C类地址的前3位以 110开始】

#### 端口号
端口号就是在同一操作系统内为区分不同套接字而设置的,因此无法将 1 个端口号分配给不同套接字 。 另外,端口号由 16位构成,可分配的端口号范围是 0-65535 。 但 0-1023 是知名端口( Well-known PORT ) , 一般分配给特定应用程序,所以应当分配此范围之外的值 。 另外,虽然端口号不能重复,但TCP套接字和 UDP套接字不会共用端口号,所以允许重复 。 例如:如果某TCP套接字使用 9190号端口,则其他TCP套接字就无法使用该端口号,但UDP套接字可以使用 。
#### 地址信息的表示
```c
struct sockaddr_in
{
    sa_family_t sin_family              // 地址族
    // AF_INET IPv4网络协议中使用的地址族
    // AF_INET6 IPv6网络协议中使用的地址族
    uint16_t sin_port;			// 16位TCP/UDP端口号 
    struct in_addr sin_addr;		// 32为IP地址  

    char sin_zero[9]                    // 不使用
};

struct in_addr
{
    In_addr_t s_addr;                   //32位IPv4地址
};

struct sockaddr
{
    sa_family_t sin_family              // 地址族
    char sa_data[14];		        // 地址信息
};
````
#### 网络字节序与地址变换
- 大端序 ( Big Endian ) : 高位字节存放到低位地址 。
- 端序 ( Little Endian ) :高位字节存放到高位地址 。

字节序转换

```c
unsigned short htons(unsigned short);
unsigned short ntohs(unsîgned short);

unsigned long htonl (unsigned long);
unsigned long ntohl(unsigned long);

// h 代表主机(host)字节序, n代表网络(network )字节序
// s 指的是short, l指的是Iong
```

#### 网络地址的初始化与分配

```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string);
// 成功时返回32位大端序整数型值, 失败时返回INADDR_NONE

int inet_aton(const char * string,struct in_addr * addr);
// 成功时返回1(true) ,失败时返回0(false) 
// string 含有需转换的IP地址信息的字符串地址信息
// addr 将保存转换结果的in_addr结构体变量的地址值

char *inet_ntoa(struct in_addr adr) ;
// 成功时返回 字符串地址值,失败时返回-1
```

#### 网络地址初始化
结合前面所学 的内容,现在介绍套接字创建过程中常见的网络地址信息初始化方法
```c
struct sockaddr_in addr;

char *serv_ip = "211.117.168.13"; // 声明 IP地址字符串
char *serv_port = "9190";         // 声明端口号字符串
memset(&addr, 0, sizeof(addr));   // 结构体变量addr 的所有成员初始化为0

addr.sin_family = AF_INET;                 // 指定地址族
addr.sin_addr.s_addr = inet_addr(serv_ip); // 基于字符串的IP地址初始化
addr.sin_port = htons(atoi(serv_port));    // 基于字符串的端口号初始化
```
每次创建服务器端套接字都要输入E地址会有些繁琐,此时可如下初始化地址信息 。
```c
struct sockaddr_in addr;

char *serv_port = "9190";         // 声明端口号字符串
memset(&addr, 0, sizeof(addr));

addr.sin_family = AF_INET;                
addr.sin_addr.s_addr = htonl(INADDR_ANY); // 用常数lNADDR ANY分配服务器端的回地址
addr.sin_port = htons(atoi(serv_port));   
```

#### 向套接字分配网络地址
既然已讨论了sockaddr_in结构体的初始化方法,接下来就把初始化的地址信息分配给套接字 。 bind函数负责这项操作 。
```c
#include <sys/socket.h>
int bind(int sockfd ,struct sockaddr *myaddr,socklen_t addrlen);
// 成功时返回 0 ,失败时返回-1 
// sockfd 要分配地址信息的套接字文件描述符
// myaddr 存有地址信息的结构体变量地址值 。
// addrlen 第二个结构体变量的长度
```

下面给出 服务器端常见套接字初始化过程
```c

int serv_sock;
struct sockaddr_in serv_addr;
char *serv_port = "9190";
/* 创建服务器端套接字(监听套接字) */
serv_sock = socket(PF_INET, SOCK_STREAM, 0);
/* 地址信息初始化 */

memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(atoi(serv_port));

/* 分配地址信息 */
bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

/*******/
```