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
    sa_family_t sin_family              // 地址族 ->> unsigned short int 
    // AF_INET IPv4网络协议中使用的地址族
    // AF_INET6 IPv6网络协议中使用的地址族
    in_port_t sin_port;			// 16位TCP/UDP端口号   ->> uint16_t
    struct in_addr sin_addr;		// 32为IP地址  ->> uint32_t

    char sin_zero[9]                    // 不使用
};

struct in_addr
{
    In_addr_t s_addr;                   //32位IPv4地址 ->> uint32_t
};

struct sockaddr
{
    sa_family_t sin_family              // 地址族 ->> unsigned short int 
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

### ch04 基于TCP的服务器端/客户端(1)

#### 理解 TCP和UDP

> TCP 链路层 IP层 TCP层 应用层
> UDP 链路层 IP层 UDP层 应用层

##### 链路层

链路层是物理链接领域标准化的结果,也是最基本的领域专 门定义LAN 、 WAN 、 MAN等网络标准。

##### IP层

IP本身是面向消息的 、不可靠的协议。 每次传输数据时会帮我们选择路径,但并不 一致 。 如果传输中发生路径错误, 则选择其他路径;但如果发生数据丢失或错误,则无法解决。

##### TCP和UDP层
IP层只关注 1 个数据包(数据传输的基本单位)的传输过程 。 因此,即使传输多个数据包每个数据包也是由 IP层实际传输的,也就是说传输顺序及传输本身是不可靠的 。 若只利用 IP层传输数据,则有可能导致后传输的数据包B 比先传输的数据包A提早到达 。 另外,传输的数据包A、B 、 C中有可能只收到A和 C ,甚至收到的 C可能已损毁 。 反之,若添加TCP协议则按照如下对话方式进行数据交换 。

##### 应用层

TCP服务器端的默认函数调用顺序
> sockte() 创建套接字
> bind() 分配套接字地址
> listen() 等待连接请求
> accept() 允许连接
> read()/read() 数据交换
> close() 关闭连接


进入等待连接请求状态
```c
# include <sys/socket.h>
int listen (int __fd, int __n);
// 成功时返回 0 ,失败时返回 -1
// __fd 希望进入等待连接请求状态的套接字文件描述符
//  __n 接请求等待队列的长度
```
受理客户端连接请求
调用 listen 函数后,若有新的连接请求,则应按序受理 。 受理请求意味着进入可接受数据的状态
```c
 int accept (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len);
// 成功时返回创建的套接字文件描述符,失败时返回-1
// __fd 服务器套接 字的 文件描述符
// __addr 保存发起连接请求的客户端地址信息的变量地址值,调用函数后向传递来的地址变量参数值填充客户端地址信息 。
// __addr_len 第二个参数的长度 完成调用后被填充
```
TCP客户端的默认函数调用顺序
> sockte() 创建套接字
> connect() 请求连接
> read()/read() 数据交换
> close() 关闭连接

请求连接
与服务器端相 比, 区别就在于请求连接，它是创建客户端套接字后向服务器端发起的连
接请求 。 服务器端调用 listen 函数后创建连接请求等待队列,之后客户端即可请求连接 。 那如何发起连接请求呢?通过调用如下函数完成 。

```c
int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
// 成功时返回 0 ,失败时返回 -1
// __fd 客户端套接字文件描述符
//  __addr目标服务器地址信息的变量地址值
// __len 第二个参数的长度
```
客户端调用 connect函数后,发生以下情况之一才会返回(完成函数调用)。
- 服务器端接收连接请求 。
- 发生断网等异常情况而中断连接请求 。

目前有的问题
- 客户端输入字符串长度受限
- 客户端断开后 服务器端没有及时的将连接数相应的减少
- 客户端结束进程 服务器端仍在连接

### 优雅的断开套接字连接

```c
#include <sys/sockte.h>

int shutdown(int sock,int howto);
// 成功返回0 失败返回-1
//  sock 需要断开套接字的文件描述符
//  howto   传递断开方式信息
// SHUT_RD : 断开输入流 。
// SHUT_WR: 断开输出流 。
// SHUT_RDWR: 同时断开 1/0流 。
```