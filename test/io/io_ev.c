#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#define EV_MULTIPLICITY 1
#include <stdio.h>
#include <ev.h>
#include <unistd.h>

// Idle watcher回调函数
static void idle_callback(EV_P_ ev_idle *w, int revents) {
    // 什么都不做，仅保持事件循环运行
}

static void stdin_cb(EV_P_ ev_io *w, int revents) {
	char buf[256] = {0};
	ssize_t n = read(w->fd, buf, sizeof(buf));
	if (n > 0)
		printf("read buf:%s, len:%d, fd:%d\n", buf, n, w->fd);
}

// 新增：TCP socket 读事件回调函数
static void tcp_read_callback(EV_P_ ev_io *w, int revents) {
    char buf[1024];
    ssize_t n = recv(w->fd, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("TCP read: %s\n", buf);
		//sprintf(buf, "echo: %s", buf);
		send(w->fd, buf, strlen(buf), 0);
    } else if (n == 0) {
        printf("TCP connection closed by peer\n");
        ev_io_stop(EV_A_ w);
        close(w->fd);
    } else {
        perror("recv error");
        ev_io_stop(EV_A_ w);
        close(w->fd);
    }
}

// 新增：设置 TCP socket 并连接到指定端口
static int setup_tcp_socket(struct ev_loop *loop) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5505);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("invalid address");
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sockfd);
        return -1;
    }

    // 创建并启动 ev_io watcher
    ev_io *tcp_watcher = malloc(sizeof(ev_io));
    ev_io_init(tcp_watcher, tcp_read_callback, sockfd, EV_READ);
    ev_io_start(loop, tcp_watcher);

    return sockfd;
}

int main() {
    // 初始化libev事件循环
    struct ev_loop *loop = ev_default_loop(0);

    // 创建并启动一个idle watcher
    ev_idle idle_watcher;
    ev_idle_init(&idle_watcher, idle_callback);
    // ev_idle_start(loop, &idle_watcher);

    // for io event
    ev_io stdin_watcher = {.fd = -1, .events = 0};
    ev_io_init(&stdin_watcher, stdin_cb, STDIN_FILENO, EV_READ);
    ev_io_start(loop, &stdin_watcher);

    // 新增：设置 TCP socket
    int tcp_sockfd = setup_tcp_socket(loop);
    if (tcp_sockfd < 0) {
        fprintf(stderr, "Failed to setup TCP socket\n");
    }

    // 进入事件循环
    ev_run(loop, 0);

    return 0;
}