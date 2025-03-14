#define EV_MULTIPLICITY 1
#include <stdio.h>
#include <ev.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <ev.h>
#include <pthread.h>

ev_async async_watcher;

static void tiemr_cb(EV_P_ ev_timer *w, int revents) {
	printf("time out!\n");
	ev_async_send(EV_DEFAULT, &async_watcher);  // 异步通知主循环
	//ev_timer_start(EV_A_ w);
}

// 子线程发送异步事件
void* thread_func(void *arg) {
	ev_loop *loop = ev_loop_new(0);

	ev_timer timer_watcher;
	ev_timer_init(&timer_watcher, tiemr_cb, 5.0, 5);
	ev_timer_start(loop, &timer_watcher);
	
	ev_run(loop, 0);
    return NULL;
}

// 主线程处理异步事件
static void async_cb(EV_P_ ev_async *w, int revents) {
    printf("收到子线程通知!\n");
    // 停止异步 watcher
    ev_async_stop(loop, &async_watcher);
    // 重新启动异步 watcher
    ev_async_start(loop, &async_watcher);
}

int main() {
    struct ev_loop *loop = ev_default_loop(0);
    ev_async_init(&async_watcher, async_cb);
    ev_async_start(loop, &async_watcher);

    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    ev_run(loop, 0);
    return 0;
}