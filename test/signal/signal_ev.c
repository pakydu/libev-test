#define EV_MULTIPLICITY 1
#include <stdio.h>
#include <ev.h>
#include <unistd.h>
#include <signal.h>

static void signal_cb(EV_P_ ev_signal *w, int revents) {
	printf("Got signal %d\n", w->signum);
	ev_break(loop, EVBREAK_ALL);
}

int main() {
    // 初始化libev事件循环
    struct ev_loop *loop = ev_default_loop(0);

	ev_signal signal_watcher;
	ev_signal_init(&signal_watcher, signal_cb, SIGINT);
	//printf("signal->fd:%d\n", loop->sigfd);
	ev_signal_start(loop, &signal_watcher);

    // 添加对SIGTERM信号的处理
    ev_signal signal_watcher_term;
    ev_signal_init(&signal_watcher_term, signal_cb, SIGTERM);
    ev_signal_start(loop, &signal_watcher_term);

    // 进入事件循环
    ev_run(loop, 0);

    return 0;
}