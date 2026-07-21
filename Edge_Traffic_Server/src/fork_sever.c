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

    signal(SIGCHLD, sigchld_handler);  // 防止僵尸进程

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
    
    printf("多进程服务器，端口 %d\n", PORT);

    
    while(1)
    {
    //循环等待庐山派和前段发送的请求
    /*
    extern int accept(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict __addr_len);
    int __fd：总机号码（listen_fd），就是前面 socket/bind/listen 配置好的那个
    struct sockaddr *__addr：用来装客户端 IP 和端口的信封，accept 会自动填好
    socklen_t *__addr_len：告诉内核这个信封有多大，防止地址写越界 
    总结：接听客户端连接，返回一个新的分机号（client_fd）专门和这个客户端通信
    */
    client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
    if(client_fd < 0)   continue;

    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        continue;
    }else if(pid == 0){
        //子进程专门处理来自前端和庐山派的请求，因此不需要监听的功能
        close(listen_fd);
        while(1)
        {   
            /*
            extern ssize_t recv(int __fd, void *__buf, size_t __n, int __flags);
            int __fd：从 accept 拿到的，指定从哪个客户端收数据
            void *__buf：收到的数据放这里
            size_t __n：容量（sizeof(buf)），最多装多少字节，防止溢出
            int __flags：默认填 0 即可
            
            总结：从指定客户端接收数据，返回实际收到的字节数
                返回 0 表示客户端断开，返回 -1 表示出错
            */
            int flag = recv(client_fd, buf, sizeof(buf), 0);//可修改为int flag = recv(client_fd, buf, sizeof(buf)-1, 0);给0留出一位
            if (flag < 0) 
            {
                perror("recv");  // 打印出错原因，方便调试
                close(client_fd);
                break;
            } else if(flag == 0){
                close(client_fd);
                break;
            }else{
                //此处未作判断，可能会出现越界情况
                buf[flag] = '\0';
                send(client_fd, buf, flag, 0);

            }
            
        }

        exit(0);

    }else{

        close(client_fd);

    }

    }

    close(listen_fd);
    return 0;
}
