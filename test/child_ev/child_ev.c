#define EV_MULTIPLICITY 1
#include <stdio.h>
#include <ev.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void child_cb(EV_P_ ev_child *w, int revents) {
	printf("Got SIGCHLD\n");
	ev_break(loop, EVBREAK_ALL);
}

int main() {
    // 初始化libev事件循环
    struct ev_loop *loop = ev_default_loop(0);

	ev_child child_watcher;


	pid_t pid = fork();
	if (pid == 0) {
		//child process.
		sleep(5);
		exit(100);
	} else {
		//parent process.
		ev_child_init(&child_watcher, child_cb, pid, 0);
		ev_child_start(loop, &child_watcher);
		
		// 进入事件循环
		ev_run(loop, 0);
	}

    return 0;
}