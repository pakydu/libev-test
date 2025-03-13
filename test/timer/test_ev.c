#define EV_MULTIPLICITY 1
#include<stdio.h>
#include <ev.h>
#include <stdio.h>

// 定时器回调函数
static void timer_callback(EV_P_ ev_timer *w, int revents) {
    printf("Timer ticked!\n");
    // 重新启动定时器
    ev_timer_again(EV_A_ w);
}

int main() {
    // 初始化libev事件循环
    EV_DEFAULT;

    // 创建一个定时器watcher
    ev_timer my_timer;
    // 设置定时器的回调函数和超时时间（1秒）
    ev_timer_init(&my_timer, timer_callback, 1.0, 0.0);
    // 启动定时器watcher
    ev_timer_start(EV_DEFAULT_ &my_timer);

    // 进入事件循环
    ev_run(EV_DEFAULT,0);

    return 0;
}
