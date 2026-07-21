#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>

#define BUF_SIZE 1024
#define PORT 9096



//回收僵尸进程
void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}


int main(int argc, char const *argv[])
{
    int listen_fd, client_fd;
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];
    //创建监听客户端连接请求的,配置泰山派连接的信息
    /*
    extern int socket (int __domain, int __type, int __protocol) __THROW;
    int __domain：指定地址族/协议族，AF_INET 表示使用 IPv4（最通用）
    int __type：传输层协议，SOCK_STREAM是tcp协议(可靠，不丢包)，SOCK_DGRAM是udp协议(会丢包，但延迟低)
    int __protocol：默认0即可
    */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    //清空泰山派本地接收时候的地址信息
    memset(&addr, 0 ,sizeof(addr));
    addr.sin_family      = AF_INET;       // 使用 IPv4
    addr.sin_port        = htons(PORT);   // 监听 9096 端口
    // 监听本机所有 IP 地址,庐山派可以通过IP，WIFI等方式进行连接，选择监听所有的IP地址可以保证只要是端口正确无论何种方式的传输都可以接收
    addr.sin_addr.s_addr = INADDR_ANY;   

    //类比：socket() 是装了一部电话，bind() 是去电信公司给这部电话申请了一个固定的电话号码（端口号）。现在别人才能打这个号码找到你。
    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    //设置最多一次性可以连接的外部设备数
    listen(listen_fd, 6);
    
    



    return 0;
}
